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

#include "QoSBroker.h"

#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace soqosmw {

Define_Module(QoSBroker);

QoSBroker::QoSBroker() {
}

QoSBroker::~QoSBroker() {
}

void QoSBroker::initialize() {
    cout << "QoSBorker::initialize";
    handleParameterChange(nullptr);
    if (_isClient) {
        //Client Starts the Operation so create selfmsg for startsignal
        cMessage* startSignal = new cMessage("startSignal");
        scheduleAt(simTime() + 1, startSignal);
        _state = CLIENT_STARTUP;
        cout << "is Client so setup start message.";
    } else {
        _state = SERVER_NO_SESSION;
    }
    cout << endl;
}

void QoSBroker::handleMessage(cMessage *msg) {
    if (_parametersInitialized) {
        if (_isClient) {
            clientHandleMessage(msg);
        } else {
            serverHandleMessage(msg);
        }
    }

}

void QoSBroker::serverHandleMessage(cMessage *msg) {
    cout << "QoSBroker::" << getStateAsName() << " --> message received";

    switch (_state) {
    case SERVER_NO_SESSION:
        try {
            cPacket* incomingPayload = extractMessage(msg);
            //check incoming message class
            QoSNegotiationRequest* incoming =
                    dynamic_cast<QoSNegotiationRequest*>(incomingPayload);

            if (incoming == 0) {
                //not a QoS Negotiation class.
                cout << " --> Message not of type QoS Negotiation";

            } else {

                //request received --> check requirements
                cout << " --> received request";
                bool requestAcceptables = serverProcessQoSRequestIsAcceptable(
                        incoming);

                //create response
                QoSNegotiationResponse* response = new QoSNegotiationResponse();
                //TODO set other data ..

                if (requestAcceptables) {
                    // successfull negotiation
                    cout << " --> request acceptable";

                    //create accept payload
                    response->getPayload().setResposeStatus(
                            QoSNegotiationResponseStatus::QoS_ResponseStatusSuccess);

                    //switch state to pending accept
                    _state = SERVER_PENDING_ACCEPT;
                } else {
                    // negotiation failed. QUIT
                    cout << " --> request unacceptable";

                    //create accept payload
                    response->getPayload().setResposeStatus(
                            QoSNegotiationResponseStatus::QoS_ResponseStatusFailure);

                    //switch state to no session
                    _state = SERVER_NO_SESSION;
                }

                //send response
                sendMessage(response);
                cout << " --> send response";
            }
        } catch (exception& e) {
            cout << "Exception: " << e.what();
        }
        break;
    case SERVER_PENDING_ACCEPT:
        break;
    case SERVER_SESSION_ESTABLISHED:
        break;
    default:
        //nothing to do here...
        break;
    }

    cout << endl;
    delete msg;
}

bool QoSBroker::serverProcessQoSRequestIsAcceptable(QoSNegotiation* request) {
    //get payload
    return true;
}

void QoSBroker::clientHandleMessage(cMessage *msg) {
    cout << "QoSBroker::" << getStateAsName() << " --> message received";

    //switch threw states:
    switch (_state) {

    case CLIENT_STARTUP:
        //only reakt on selfmsg for start signal
        if (msg->isSelfMessage()) {

            //--> start the negotiation!
            cout << " --> start signal received";

            //create QoS Request Message
            QoSNegotiationRequest* request = new QoSNegotiationRequest();
            //TODO set other data ..

            //send QoS Request
            sendMessage(request);
            cout << " --> send negotiation request";

            //set state to pending
            _state = CLIENT_PENDING_REQUEST;
        }
        break;

    case CLIENT_PENDING_REQUEST:
        try {
            cPacket* incomingPayload = extractMessage(msg);
            //check if msg is correct class
            QoSNegotiationResponse *incoming =
                    dynamic_cast<QoSNegotiationResponse*>(incomingPayload);

            if (incoming == 0) {
                //not a QoS Negotiation class.
                cout << " --> Message not of type QoS Negotiation";

            } else {

                //response received --> check contract
                cout << " --> received response";
                bool negotiationSuccessful = clientProcessQoSResponseIsSuccess(
                        incoming);

                if (negotiationSuccessful) {
                    // successfull negotiation
                    cout << " --> negotiation successful";

                    //create Connection request
                    QoSConnectionEstablish* establish =
                            new QoSConnectionEstablish();
                    establish->setType(
                            QoSConnectionEstablishMsgType::Establish_Request);
                    //TODO set other data ..

                    //send connection request

                    sendMessage(establish);
                    cout << " --> send establish request";

                    //switch state to pending connection
                    _state = CLIENT_PENDING_CONNECTION;
                } else {
                    // negotiation failed. QUIT
                    cout << " --> negotiation Failed";
                    _state = CLIENT_FAILURE;
                }
            }
        } catch (exception& e) {
            cout << "Exception: " << e.what();
        }
        break;

    case CLIENT_PENDING_CONNECTION:
        break;

    default:
        //nothing to do we already finsihed our job..
        break;
    }

    //cleanup
    cout << endl;
    delete msg;
}

bool QoSBroker::clientProcessQoSResponseIsSuccess(
        QoSNegotiationResponse* response) {
    //get payload
    QoSNegotiationResponsePayload payload = response->getPayload();

    switch (payload.getResposeStatus()) {
    case QoSNegotiationResponseStatus::QoS_ResponseStatusSuccess:
        return true;
        break;
    case QoSNegotiationResponseStatus::QoS_ResponseStatusFailure:
        return false;
        break;
    default:
        break;
    }
    return false;
}

void QoSBroker::handleParameterChange(const char* parname) {
    bool updateGate = false; //true if the module or gate parameter has been updated.
    const char* targetModulePar;
    const char* targetGatePar;


    //update parameters if nullptr or parameter specified.
    if (!parname || !strcmp(parname, "isClient")) { //is this a client?
        _isClient = this->par("isClient").boolValue();
    }
    if (!parname || !strcmp(parname, "useNetworkLayerOut")) { //is this a client?
        _useNetworkLayerOut = this->par("useNetworkLayerOut").boolValue();
    }
    if (!parname || !strcmp(parname, "useTargetGate")) { //is this a client?
        _useTargetGate = this->par("useTargetGate").boolValue();
    }

    if (!parname || !strcmp(parname, "destAddress")) { //update destination address
        if (par("destAddress").stdstringValue() == "auto") {
            // assign automatic address
            this->destAddress = inet::MACAddress::generateAutoAddress();

            // change module parameter from "auto" to concrete address
            par("destAddress").setStringValue(this->destAddress.str());
        } else {
            this->destAddress.setAddress(par("destAddress").stringValue());
        }
    }

    if(_useTargetGate) {
        if (!parname || !strcmp(parname, "targetModule")) { //set target module
            targetModulePar = this->par("targetModule").stringValue();
            if (!strcmp(targetModulePar,"")) {
                _targetModule = getParentModule()->getSubmodule(targetModulePar);
                if (_targetModule) {
                    updateGate = true;
                } else {
                    throw cRuntimeError(
                            "Parent module does not contain the specified target Module: %s.",
                            targetModulePar);
                }
            } else {
                //no module specified!
                throw cRuntimeError("Please specify a targetModule.");
            }

        }
        if (!parname || !strcmp(parname, "targetGate")) { //set target gate
            targetGatePar = this->par("targetGate").stringValue();
            updateGate = true;
        }

        //check if gate or module has been updated.
        if (updateGate) {
            if (_targetModule && !strcmp(targetGatePar,"")) {
                _targetGate = _targetModule->gate(targetGatePar);
                if (!_targetGate) {
                    //target Module has no gate with that name
                    throw cRuntimeError(
                            "Module does not contain the specified gate: %s.",
                            targetGatePar);
                }
            } else {
                throw cRuntimeError("Gate should update but no module set. This should never happen!");
            }
        }
    }


    //first initialization before startup finished?
    if (!parname && !_parametersInitialized) {
        _parametersInitialized = true;
    }

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

void QoSBroker::sendMessage(cPacket* payload_packet) {
    inet::EthernetIIFrame *frame = new inet::EthernetIIFrame(
            "Best-Effort Traffic", 7); //kind 7 = black

    frame->setDest(this->destAddress);

    //payload_packet->setByteLength(static_cast<int64_t>(getPayloadBytes()));
    frame->setByteLength(ETHER_MAC_FRAME_BYTES);
    frame->encapsulate(payload_packet);
    //Padding
    if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
        frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }
    if (gate("networkLayerOut")->isConnected() && _useNetworkLayerOut)
    {
        send(frame->dup(), "networkLayerOut");
    }
    if (_useTargetGate){
        sendDirect(frame->dup(), _targetGate);
    }
}

cPacket* QoSBroker::extractMessage(cMessage *msg){
    inet::EthernetIIFrame *frame = dynamic_cast<inet::EthernetIIFrame*>(msg);
    return frame->decapsulate();
}

} /* namespace soqosmw */
