//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <endpoints/publisher/base/IPublisher.h>
#include <endpoints/subscriber/base/ISubscriber.h>
#include <factory/ServiceEndpointFactory.h>
#include <messages/QoSNegotiationProtocol/ConnectionSpecificInformation_m.h>
#include <messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.h>
#include <omnetpp/clog.h>
#include <qosmanagement/negotiation/broker/QoSBroker.h>
#include <qosmanagement/negotiation/datatypes/Request.h>
#include <qospolicy/management/QoSGroup.h>
#include <servicemanager/LocalServiceManager.h>
#include <iostream>
#include <unordered_map>

#include <inet/networklayer/common/L3Address.h>
#include <inet/transportlayer/contract/udp/UDPSocket.h>

namespace soqosmw {
using namespace inet;
using namespace std;

QoSBroker::QoSBroker(UDPSocket* socket, LocalServiceManager* lsm, EndpointDescription local,
        EndpointDescription remote, Request* request) :
        _socket(socket), _lsm(lsm), _local(local), _remote(remote), _request(request) {
    _negotiationFinished = false;
    if (request != nullptr) {
        _state = QoSBrokerStates_t::CLIENT_STARTUP;
    } else {
        _state = QoSBrokerStates_t::SERVER_NO_SESSION;
    }
}

QoSBroker::~QoSBroker() {
    if (_request) {
        delete _request;
    }
}

bool QoSBroker::handleMessage(QoSNegotiationProtocolMsg *msg) {
    bool handled = false;

    if (msg) {
        if (this->isResponsibleFor(msg->getReceiver(), msg->getSender())) {
            EV_DEBUG << "QoSBroker:" << " --> message received"
                            << " --> I am the receiver" << endl;

            switch (msg->getMessageType()) {
            case QoSNegotiationMsgType::QoS_Request:
                handled = handleRequest(
                        dynamic_cast<soqosmw::QoSNegotiationRequest*>(msg));
                break;
            case QoSNegotiationMsgType::QoS_Response:
                handled = handleResponse(
                        dynamic_cast<soqosmw::QoSNegotiationResponse*>(msg));
                break;
            case QoSNegotiationMsgType::QoS_Establish:
                handled = handleEstablish(
                        dynamic_cast<soqosmw::QoSNegotiationEstablish*>(msg));
                break;
            case QoSNegotiationMsgType::QoS_Finalise:
                handled = handleFinalise(
                        dynamic_cast<soqosmw::QoSNegotiationFinalise*>(msg));
                break;
            default:
                EV_ERROR << "QoSBroker:" << " --> message received"
                                << " --> ERROR: Message type not set correctly! --> ignore it!"
                                << endl;
                break;
            }
        } else {
            //i am not responsible do nothing...
            EV_ERROR << "QoSBroker:" << " --> message received"
                            << " --> I am not responsible." << endl;
        }
    }
    return handled;
}

bool QoSBroker::startNegotiation() {
    bool handled = false;
    if (_state == QoSBrokerStates_t::CLIENT_STARTUP) {
        //create QoS Request Message
        QoSNegotiationRequest* request = new QoSNegotiationRequest("QoSNegotiationRequest");
        //fill envelope
        fillEnvelope(request);
        std::unordered_map<std::string, IQoSPolicy*> qosPolicies =
                _request->getQosPolicies();
        switch ((dynamic_cast<QoSGroup*>(qosPolicies[QoSPolicyNames::QoSGroup]))->getValue()) {
        case QoSGroup::WEB:
            request->setQosClass(QoSGroups::WEB);
            break;
        case QoSGroup::STD:
            request->setQosClass(QoSGroups::STD);
            break;
        case QoSGroup::RT:
            request->setQosClass(QoSGroups::RT);
            break;
        default:
            _request->setStatus(RequestStatus::INVALID);
            finishNegotiation();
            EV_ERROR
                            << "QoSBroker: starting negotiation --> no valid QoSProperties set.";
            return false;
        }

        //send QoS Request
        sendMessage(request);
        EV_DEBUG << "QoSBroker: starting negotiation"
                        << " --> send negotiation request.";
        _state = QoSBrokerStates_t::CLIENT_PENDING_REQUEST;

        _request->setStatus(RequestStatus::REQUEST_SEND);

        handled = true;
    } else {
        _request->setStatus(RequestStatus::INVALID);
        finishNegotiation();
        EV_ERROR << "QoSBroker: starting negotiation"
                        << " --> Broker not in correct state to handle start signal. State is: "
                        << getStateAsName() << endl;
    }
    return handled;
}

bool QoSBroker::handleRequest(QoSNegotiationRequest* request) {
    bool handled = false;
    if (request) {
        if (_state == QoSBrokerStates_t::SERVER_NO_SESSION) {

            //request received --> check requirements
            bool requestAcceptables = isRequestAcceptable(request);

            //create response
            QoSNegotiationResponse* response = new QoSNegotiationResponse("QoSNegotiationResponse");
            fillEnvelope(response);
            response->setQosClass(request->getQosClass());

            if (requestAcceptables) {
                // successfull negotiation
                EV_DEBUG << "QoSBroker: received request"
                                << " --> request acceptable"
                                << " --> send response." << endl;

                response->setResponseStatus(QoSNegotiationStatus::Success);

                _state = QoSBrokerStates_t::SERVER_PENDING_ACCEPT;
            } else {
                // negotiation failed. QUIT
                EV_DEBUG << "QoSBroker: received request"
                                << " --> request unacceptable"
                                << " --> send response." << endl;
                finishNegotiation();

                //create accept payload
                response->setResponseStatus(QoSNegotiationStatus::Failure);
            }

            //send response
            sendMessage(response);
            _state = QoSBrokerStates_t::SERVER_PENDING_ACCEPT;
            handled = true;
        } else {
            EV_ERROR
                            << "QoSBroker: not in correct state to handle new request. State is: "
                            << getStateAsName() << endl;
        }
    } else {
        EV_ERROR << "QoSBroker: received invalid request." << endl;
    }
    return handled;
}

bool QoSBroker::handleResponse(QoSNegotiationResponse* response) {
    bool handled = false;
    if (response) {
        if (_state == QoSBrokerStates_t::CLIENT_PENDING_REQUEST) {
            //response received --> check contract
            EV_DEBUG << "QoSBroker: received response";

            if (response->getResponseStatus()
                    == QoSNegotiationStatus::Success) {
                // successfull negotiation
                EV_DEBUG << " --> negotiation successful";

                //create Connection request
                QoSNegotiationEstablish* establish =
                        new QoSNegotiationEstablish("QoSNegotiationEstablish");
                fillEnvelope(establish);
                establish->setQosClass(response->getQosClass());

                //send connection request
                sendMessage(establish);
                EV_DEBUG << " --> send establish request" << endl;
                _request->setStatus(RequestStatus::ESTABLISH_SEND);
                _state = QoSBrokerStates_t::CLIENT_PENDING_CONNECTION;
            } else {
                // negotiation failed. QUIT
                EV_DEBUG << " --> negotiation Failed";
                _request->setStatus(RequestStatus::ACKKNOWLEDGED_FAILURE);
                finishNegotiation();
            }
            handled = true;
        } else {
            EV_ERROR
                            << "QoSBroker: not in correct state to handle new request. State is: "
                            << getStateAsName() << endl;
        }
    } else {
        EV_ERROR << "QoSBroker: received invalid request." << endl;
    }
    return handled;
}

bool QoSBroker::handleEstablish(QoSNegotiationEstablish* establish) {
    bool handled = false;
    if (establish) {
        if (_state == QoSBrokerStates_t::SERVER_PENDING_ACCEPT) {
            EV_DEBUG << "QoSBroker: received establish";
            //create response
            QoSNegotiationFinalise* finalise = new QoSNegotiationFinalise("QoSNegotiationFinalise");
            fillEnvelope(finalise);
            finalise->setQosClass(establish->getQosClass());

            if (isEstablishAcceptable(establish)) {
                ConnectionSpecificInformation* connection = nullptr;

                //get path
                string& path = _local.getPath();
                //get responsible writer
                PublisherWriter* writer = _lsm->getPublisherWriterForName(path);

                //create publisher
                IPublisher* publisher = ServiceEndpointFactory::getInstance().createPublisher(path, establish->getQosClass(), writer);
                if(publisher){
                    //get endpoint details
                    connection = publisher->getConnectionSpecificInformation();
                }

                if(connection){
                    //pack details to message
                    finalise->encapsulate(connection);

                    // successfull negotiation
                    finalise->setFinalStatus(QoSNegotiationStatus::Success);
                    EV_DEBUG << " --> finalise success" << endl;
                    _state = QoSBrokerStates_t::SERVER_SESSION_ESTABLISHED;

                } else {
                    // negotiation failed. QUIT
                    finalise->setFinalStatus(QoSNegotiationStatus::Failure);
                    EV_DEBUG << " --> finalise failed" << endl;
                    _state = QoSBrokerStates_t::SERVER_FAILURE;
                }

            } else {
                // negotiation failed. QUIT
                finalise->setFinalStatus(QoSNegotiationStatus::Failure);
                EV_DEBUG << " --> finalise failed" << endl;
                _state = QoSBrokerStates_t::SERVER_FAILURE;
            }
            finishNegotiation();
            sendMessage(finalise);
            handled = true;
        } else {
            EV_ERROR
                            << "QoSBroker: not in correct state to handle new request. State is: "
                            << getStateAsName() << endl;
        }
    } else {
        EV_ERROR << "QoSBroker: received invalid request." << endl;
    }
    return handled;
}

bool QoSBroker::handleFinalise(QoSNegotiationFinalise* finalise) {
    bool handled = false;
    if (finalise) {
        if (_state == QoSBrokerStates_t::CLIENT_PENDING_CONNECTION) {
            cout << "QoSBroker: full cycle successfull" << endl;

            if(finalise->getFinalStatus() == QoSNegotiationStatus::Success){
                _state = QoSBrokerStates_t::CLIENT_SUCCESS;
                _request->setStatus(RequestStatus::FINALISED_SUCCESS);

                //get connection specific information
                cPacket* enc = finalise->decapsulate();
                if(enc){
                    ConnectionSpecificInformation* info = dynamic_cast<soqosmw::ConnectionSpecificInformation*>(enc);


                    //get path
                    string& path = _remote.getPath();
                    //get responsible writer
                    SubscriptionReader* reader = _lsm->getSubscriptionReaderForName(path);

                    //create subscriber
                    ServiceEndpointFactory::getInstance().createSubscriber(path, info, reader);
                }


            }else{
                _state = QoSBrokerStates_t::CLIENT_FAILURE;
                _request->setStatus(RequestStatus::FINALISED_FAILURE);
            }
            finishNegotiation();
            handled = true;
        } else {
            EV_ERROR
                            << "QoSBroker: not in correct state to handle new request. State is: "
                            << getStateAsName() << endl;
        }
    } else {
        EV_ERROR << "QoSBroker: received invalid request." << endl;
    }
    return handled;
}

bool QoSBroker::isRequestAcceptable(QoSNegotiationRequest* request) {
    //get payload

    //check if service exists on this node and get a reference

    //ask service if it can handle the request

    return true;
}

bool QoSBroker::isEstablishAcceptable(QoSNegotiationEstablish* establish) {
    return true;
}

void QoSBroker::fillEnvelope(soqosmw::Envelope* envelope) {
    //set receiver
    EndpointDescription receiver(_remote);
    envelope->setReceiver(receiver);
    //set sender
    EndpointDescription sender(_local);
    envelope->setSender(sender);
}

void QoSBroker::sendMessage(QoSNegotiationProtocolMsg* payload_packet) {
    //payload_packet->setByteLength(sizeof(*payload_packet));
    _socket->sendTo(payload_packet, _remote.getNetworkAddr(),
            _remote.getNetworkPort());
}

string QoSBroker::getStateAsName() {
    switch (_state) {
    case SERVER_NO_SESSION:
        return "SERVER_NO_SESSION";
    case SERVER_PENDING_ACCEPT:
        return "SERVER_PENDING_ACCEPT";
    case SERVER_SESSION_ESTABLISHED:
        return "SERVER_SESSION_ESTABLISHED";
    case SERVER_FAILURE:
        return "SERVER_FAILURE";

    case CLIENT_STARTUP:
        return "CLIENT_STARTUP";
    case CLIENT_PENDING_REQUEST:
        return "CLIENT_PENDING_REQUEST";
    case CLIENT_PENDING_CONNECTION:
        return "CLIENT_PENDING_CONNECTION";
    case CLIENT_FAILURE:
        return "CLIENT_FAILURE";
    case CLIENT_SUCCESS:
        return "SUCCESS";
    default:
        return "-.-";
    }
}

bool QoSBroker::isResponsibleFor(EndpointDescription& local,
        EndpointDescription& remote) {
    return local == _local && remote == _remote;
}

void QoSBroker::finishNegotiation() {
    _negotiationFinished = true;
}

} /* namespace soqosmw */
