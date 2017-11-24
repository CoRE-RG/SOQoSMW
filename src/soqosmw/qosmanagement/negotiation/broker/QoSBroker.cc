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

#include <soqosmw/qosmanagement/negotiation/broker/QoSBroker.h>

namespace soqosmw {

QoSBroker::QoSBroker(UDPSocket* socket, EndpointDescription local,
        EndpointDescription remote, bool isClient) :
        _socket(socket), _me(local), _you(remote), _isClient(isClient) {
    // is there anything todo?
}

QoSBroker::~QoSBroker() {
}

void QoSBroker::handleMessage(QoSNegotiationProtocolMsg *msg) {
    cout << " QoSBroker:" << " --> message received";

    if(!(msg->getReceiver().getPath() == _me.getPath())) {
        //i am not responsible do nothing...
        cout << " --> I am not the receiver";
    }
    else if (auto as_envelope = dynamic_cast<soqosmw::Envelope*>(msg)) {
        cout << " --> I am the receiver";
        //is in soqosmw::Envelope --> check other types
        if (auto as_negotiation =
                dynamic_cast<soqosmw::QoSNegotiationProtocolMsg*>(as_envelope)) {
            //is negotiation type
            switch (as_negotiation->getMessageType()) {
            case QoSNegotiationMsgType::QoS_Request:
                handleRequest(
                        dynamic_cast<soqosmw::QoSNegotiationRequest*>(as_negotiation));
                break;
            case QoSNegotiationMsgType::QoS_Response:
                handleResponse(
                        dynamic_cast<soqosmw::QoSNegotiationResponse*>(as_negotiation));
                break;
            case QoSNegotiationMsgType::QoS_Establish:
                handleEstablish(
                        dynamic_cast<soqosmw::QoSNegotiationEstablish*>(as_negotiation));
                break;
            case QoSNegotiationMsgType::QoS_Finalise:
                handleFinalise(
                        dynamic_cast<soqosmw::QoSNegotiationFinalise*>(as_negotiation));
                break;
            default:
                cout
                        << " --> Message type not set, this should not happen --> ignore it!";
                break;
            }
        } else {
            cout
                    << " --> not of type soqosmw::QoSNegotiationProtocolMsg --> ignore it!";
        }
    } else {
        cout << " --> not in soqosmw::Envelope --> ignore it!";
    }

    //cleanup
    delete msg;
}

void QoSBroker::handleStartSignal() {
    //--> start the negotiation!
    cout << " QoSBroker:" << " --> start signal received";

    //create QoS Request Message
    QoSNegotiationRequest* request = new QoSNegotiationRequest();
    //fill envelope
    fillEnvelope(request);
    request->setQosClass(QoSGroups::RT);

    //send QoS Request
    sendMessage(request);
    cout << " --> send negotiation request";
}

void QoSBroker::handleRequest(QoSNegotiationRequest* request) {
    if (request) {
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
    }
}

void QoSBroker::handleResponse(QoSNegotiationResponse* response) {
    if (response) {
        //response received --> check contract
        cout << " --> received response";

        if (response->getResponseStatus() == QoSNegotiationStatus::Success) {
            // successfull negotiation
            cout << " --> negotiation successful";

            //create Connection request
            QoSNegotiationEstablish* establish = new QoSNegotiationEstablish();
            fillEnvelope(establish);
            establish->setQosClass(response->getQosClass());

            //send connection request
            sendMessage(establish);
            cout << " --> send establish request";
        } else {
            // negotiation failed. QUIT
            cout << " --> negotiation Failed";
        }
    }
}

void QoSBroker::handleEstablish(QoSNegotiationEstablish* establish) {
    if (establish) {
        //create response
        QoSNegotiationFinalise* finalise = new QoSNegotiationFinalise();
        fillEnvelope(finalise);
        finalise->setQosClass(establish->getQosClass());

        if (isEstablishAcceptable(establish)) {
            // successfull negotiation
            cout << " --> finalise success";
        } else {
            // negotiation failed. QUIT
            cout << " --> finalise failed";
        }

        //send response
        sendMessage(finalise);
        cout << " --> send response";
    }
}

void QoSBroker::handleFinalise(QoSNegotiationFinalise* finalise) {
    if (finalise) {
        cout << " --> full cycle successfull";
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
    EndpointDescription receiver (_you);
    envelope->setReceiver(receiver);
    //set sender
    EndpointDescription sender (_me);
    envelope->setSender(sender);
}

void QoSBroker::sendMessage(QoSNegotiationProtocolMsg* payload_packet) {
    //payload_packet->setByteLength(sizeof(*payload_packet));
    _socket->sendTo(payload_packet, _you.getNetworkAddr(), _you.getNetworkPort());
}

string QoSBroker::getStateAsName() {
    switch (_state) {
    case SERVER_NO_SESSION:
        return "SERVER_NO_SESSION";
    case SERVER_PENDING_ACCEPT:
        return "SERVER_PENDING_ACCEPT";
    case SERVER_SESSION_ESTABLISHED:
        return "SERVER_SESSION_ESTABLISHED";

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
