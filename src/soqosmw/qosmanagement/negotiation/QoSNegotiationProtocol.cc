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

#include <soqosmw/qosmanagement/negotiation/QoSNegotiationProtocol.h>

#include "inet/networklayer/common/L3AddressResolver.h"

namespace soqosmw {

Define_Module(QoSNegotiationProtocol);

QoSNegotiationProtocol::QoSNegotiationProtocol() {
}

QoSNegotiationProtocol::~QoSNegotiationProtocol() {
    socketClose();
}

void QoSNegotiationProtocol::initialize(int stage) {
    cout << "QoSNegotiationProtocol::initialize stage " << stage;
    if(stage == MY_INIT_STAGE) {
        handleParameterChange(nullptr);
        if (_isClient) {
            //Client Starts the Operation so create selfmsg for startsignal
            cMessage* startSignal = new cMessage("startSignal");

            scheduleAt(simTime(), startSignal);
            cout << "is Client so setup start message.";
        } else {
            //nothing to do
        }
        if(!isSocketBound()){
            socketSetup();
        }
    }


    cout << endl;
}

void QoSNegotiationProtocol::handleMessage(cMessage *msg) {
    cout << "QoSNegotiationProtocol:" << " --> message received";

    if(msg->isSelfMessage()) {
        handleStartSignal();
    } else if (auto as_envelope = dynamic_cast<soqosmw::Envelope*>(msg)) {
        //is in soqosmw::Envelope --> check other types
        if (auto as_negotiation = dynamic_cast<soqosmw::QoSNegotiationProtocolMsg*>(as_envelope)) {
            //is negotiation type
            switch(as_negotiation->getMessageType()){
            case QoSNegotiationMsgType::QoS_Request:
                handleRequest(dynamic_cast<soqosmw::QoSNegotiationRequest*>(as_negotiation));
                break;
            case QoSNegotiationMsgType::QoS_Response:
                handleResponse(dynamic_cast<soqosmw::QoSNegotiationResponse*>(as_negotiation));
                break;
            case QoSNegotiationMsgType::QoS_Establish:
                handleEstablish(dynamic_cast<soqosmw::QoSNegotiationEstablish*>(as_negotiation));
                break;
            case QoSNegotiationMsgType::QoS_Finalise:
                handleFinalise(dynamic_cast<soqosmw::QoSNegotiationFinalise*>(as_negotiation));
                break;
            default:
                cout << " --> Message type not set, this should not happen --> ignore it!";
                break;
            }
        } else {
            cout << " --> not of type soqosmw::QoSNegotiationProtocolMsg --> ignore it!";
        }
    } else {
        cout << " --> not in soqosmw::Envelope --> ignore it!";
    }

    //cleanup
    cout << endl;
    delete msg;
}

void QoSNegotiationProtocol::handleStartSignal(){
    //--> start the negotiation!
    cout << " --> start signal received";

    //create QoS Request Message
    QoSNegotiationRequest* request = new QoSNegotiationRequest();
    //fill envelope
    fillEnvelope(request);
    request->setQosClass(QoSGroups::RT);

    //send QoS Request
    sendMessage(request);
    cout << " --> send negotiation request";
}

void QoSNegotiationProtocol::handleRequest(QoSNegotiationRequest* request){
    if(request){
        //request received --> check requirements
        cout << " --> received request";
        bool requestAcceptables = isRequestAcceptable(
                request);

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

void QoSNegotiationProtocol::handleResponse(QoSNegotiationResponse* response){
    if(response){
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

void QoSNegotiationProtocol::handleEstablish(QoSNegotiationEstablish* establish){
    if(establish) {
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

void QoSNegotiationProtocol::handleFinalise(QoSNegotiationFinalise* finalise){
    if(finalise){
        cout << " --> full cycle successfull";
    }
}

bool QoSNegotiationProtocol::isRequestAcceptable(QoSNegotiationRequest* request) {
    //get payload
    return true;
}

bool QoSNegotiationProtocol::isEstablishAcceptable(QoSNegotiationEstablish* establish){
    return true;
}

void QoSNegotiationProtocol::handleParameterChange(const char* parname) {

    //read UDP Common Parameters
    if(!parname || !strcmp(parname, "protocolPort")){
        _protocolPort = par("protocolPort");
    }
    if(!parname || !strcmp(parname, "destAddress")){
        const char* destAddr = par("destAddress");
        _destAddress = L3AddressResolver().resolve(destAddr);
    }
    if(!parname || !strcmp(parname, "localAddress")){
        const char* localAddr = par("localAddress");
        _localAddress = L3AddressResolver().resolve(localAddr);
    }

    //update parameters if nullptr or parameter specified.
    if (!parname || !strcmp(parname, "isClient")) { //is this a client?
        _isClient = this->par("isClient").boolValue();
    }

    //first initialization before startup finished?
    if (!parname && !_parametersInitialized) {
        _parametersInitialized = true;
    }

}

void QoSNegotiationProtocol::fillEnvelope(soqosmw::Envelope* envelope){
    //set receiver
    EndpointDescription receiver;
    receiver.setNetworkAddr(_destAddress);
    receiver.setNetworkPort(_protocolPort);
    envelope->setReceiver(receiver);
    //set sender
    EndpointDescription sender;
    sender.setNetworkAddr(_localAddress);
    sender.setNetworkPort(_protocolPort);
    envelope->setSender(sender);
}

void QoSNegotiationProtocol::sendMessage(cPacket* payload_packet) {
    if(!isSocketBound()){
        socketSetup();
    }
    //payload_packet->setByteLength(sizeof(*payload_packet));
    _socket.sendTo(payload_packet, _destAddress, _protocolPort);
}

string QoSNegotiationProtocol::getStateAsName() {
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

void QoSNegotiationProtocol::socketSetup() {
    _socket.setOutputGate(gate("udpOut"));
    _socket.bind(_localAddress, _protocolPort);
    _socketBound = true;
}

bool QoSNegotiationProtocol::isSocketBound(){
    return _socketBound;
}

void QoSNegotiationProtocol::socketClose() {
    _socket.close();
    _socketBound = false;
}

} /* namespace soqosmw */
