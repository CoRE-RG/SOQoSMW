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

#include <messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.h>
#include <omnetpp/clog.h>
#include <qosmanagement/negotiation/broker/QoSBroker.h>
#include <iostream>

#include <inet/networklayer/common/L3Address.h>
#include <inet/transportlayer/contract/udp/UDPSocket.h>

namespace soqosmw {
class Request;
} /* namespace soqosmw */

namespace soqosmw {
using namespace inet;
using namespace std;

QoSBroker::QoSBroker(UDPSocket* socket, EndpointDescription local,
        EndpointDescription remote, Request* request) :
        _socket(socket), _local(local), _remote(remote){
    // is there anything todo?
    if (request != nullptr) {
        _state = QoSBrokerStates_t::CLIENT_STARTUP;
    } else {
        _state = QoSBrokerStates_t::SERVER_NO_SESSION;
    }
}

QoSBroker::~QoSBroker() {
}

void QoSBroker::handleMessage(QoSNegotiationProtocolMsg *msg) {

    if (!(msg->getReceiver().getPath() == _local.getPath())) {
        //i am not responsible do nothing...
        EV_WARN << "QoSBroker:" << " --> message received" << " --> I am not the receiver" << endl;
    } else {
        EV_DEBUG << "QoSBroker:" << " --> message received"  << " --> I am the receiver" << endl;

        switch (msg->getMessageType()) {
        case QoSNegotiationMsgType::QoS_Request:
            handleRequest(
                    dynamic_cast<soqosmw::QoSNegotiationRequest*>(msg));
            break;
        case QoSNegotiationMsgType::QoS_Response:
            handleResponse(
                    dynamic_cast<soqosmw::QoSNegotiationResponse*>(msg));
            break;
        case QoSNegotiationMsgType::QoS_Establish:
            handleEstablish(
                    dynamic_cast<soqosmw::QoSNegotiationEstablish*>(msg));
            break;
        case QoSNegotiationMsgType::QoS_Finalise:
            handleFinalise(
                    dynamic_cast<soqosmw::QoSNegotiationFinalise*>(msg));
            break;
        default:
            EV_ERROR << "QoSBroker:" << " --> message received" << " --> ERROR: Message type not set! --> ignore it!" << endl;
            break;
        }
    }

    //cleanup
    delete msg;
}

void QoSBroker::handleStartSignal() {
    //--> start the negotiation!
    cout << " QoSBroker:" << " --> start signal received";

    if (_state == QoSBrokerStates_t::CLIENT_STARTUP) {
        //create QoS Request Message
        QoSNegotiationRequest* request = new QoSNegotiationRequest();
        //fill envelope
        fillEnvelope(request);
        request->setQosClass(QoSGroups::RT);

        //send QoS Request
        sendMessage(request);
        cout << " --> send negotiation request";
        _state = QoSBrokerStates_t::CLIENT_PENDING_REQUEST;
    } else {
        cout
                << " --> Broker not in correct state to handle start signal. State is: "
                << getStateAsName();
    }
}

void QoSBroker::handleRequest(QoSNegotiationRequest* request) {
    if (request) {
        if (_state == QoSBrokerStates_t::SERVER_NO_SESSION) {
            //request received --> check requirements
            cout << " --> received request";
            bool requestAcceptables = isRequestAcceptable(request);

            //create response
            QoSNegotiationResponse* response = new QoSNegotiationResponse();
            fillEnvelope(response);
            response->setQosClass(request->getQosClass());

            if (requestAcceptables) {
                // successfull negotiation
                cout << " --> request acceptable";

                response->setResponseStatus(QoSNegotiationStatus::Success);
            } else {
                // negotiation failed. QUIT
                cout << " --> request unacceptable";

                //create accept payload
                response->setResponseStatus(QoSNegotiationStatus::Failure);
            }

            //send response
            sendMessage(response);
            cout << " --> send response";
            _state = QoSBrokerStates_t::SERVER_PENDING_ACCEPT;
        } else {
            cout
                    << " --> Broker not in correct state to handle new request. State is: "
                    << getStateAsName();
        }
    } else {
        cout << " --> request invalid";
    }
}

void QoSBroker::handleResponse(QoSNegotiationResponse* response) {
    if (response) {
        if (_state == QoSBrokerStates_t::CLIENT_PENDING_REQUEST) {
            //response received --> check contract
            cout << " --> received response";

            if (response->getResponseStatus()
                    == QoSNegotiationStatus::Success) {
                // successfull negotiation
                cout << " --> negotiation successful";

                //create Connection request
                QoSNegotiationEstablish* establish =
                        new QoSNegotiationEstablish();
                fillEnvelope(establish);
                establish->setQosClass(response->getQosClass());

                //send connection request
                sendMessage(establish);
                cout << " --> send establish request";
                _state = QoSBrokerStates_t::CLIENT_PENDING_CONNECTION;
            } else {
                // negotiation failed. QUIT
                cout << " --> negotiation Failed";
            }
        } else {
            cout
                    << " --> Broker not in correct state to handle a response. State is: "
                    << getStateAsName();
        }
    } else {
        cout << " --> response invalid";
    }
}

void QoSBroker::handleEstablish(QoSNegotiationEstablish* establish) {
    if (establish) {
        if (_state == QoSBrokerStates_t::SERVER_PENDING_ACCEPT) {
            cout << " --> received establish";
            //create response
            QoSNegotiationFinalise* finalise = new QoSNegotiationFinalise();
            fillEnvelope(finalise);
            finalise->setQosClass(establish->getQosClass());

            if (isEstablishAcceptable(establish)) {
                // successfull negotiation
                cout << " --> finalise success";

                //send response
                sendMessage(finalise);
                cout << " --> send response";
                _state = QoSBrokerStates_t::SERVER_SESSION_ESTABLISHED;
            } else {
                // negotiation failed. QUIT
                cout << " --> finalise failed";
                _state = QoSBrokerStates_t::SERVER_FAILURE;
            }
        } else {
            cout
                    << " --> Broker not in correct state to handle a establish request. State is: "
                    << getStateAsName();
        }
    } else {
        cout << " --> establish invalid";
    }
}

void QoSBroker::handleFinalise(QoSNegotiationFinalise* finalise) {
    if (finalise) {
        if (_state == QoSBrokerStates_t::CLIENT_PENDING_CONNECTION) {
            cout << " --> full cycle successfull";
            _state = QoSBrokerStates_t::CLIENT_SUCCESS;
        } else {
            cout
                    << " --> Broker not in correct state to handle finalise. State is: "
                    << getStateAsName();
        }
    }
}

bool QoSBroker::isRequestAcceptable(QoSNegotiationRequest* request) {
    //get payload
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

} /* namespace soqosmw */
