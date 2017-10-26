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

#include "QoSClient.h"
namespace soqosmw {

Define_Module(QoSClient);

void QoSClient::initialize() {
    //set state to startup
    _state = STARTUP;
    //Client Starts the Operation so create selfmsg for startsignal
    cMessage* startSignal = new cMessage("startSignal");
    scheduleAt(simTime() + 10, startSignal);
}

void QoSClient::handleMessage(cMessage *msg) {
    cout << "QoSClient::" << getStateAsName() << " --> message received";

    //switch threw states:
    switch (_state) {

    case STARTUP:
        //only reakt on selfmsg for start signal
        if (msg->isSelfMessage()) {

            //--> start the negotiation!
            cout << " --> start signal received";

            //create QoS Request Message
            QoSNegotiationRequest* request = new QoSNegotiationRequest();
            //TODO set other data ..

            //send QoS Request
            send(request, "out");
            cout << " --> send negotiation request";

            //set state to pending
            _state = PENDING_REQUEST;
        }
        break;

    case PENDING_REQUEST:
        try {
            //check if msg is correct class
            QoSNegotiationResponse *incoming = dynamic_cast<QoSNegotiationResponse*>(msg);

            if (incoming == 0) {
                //not a QoS Negotiation class.
                cout << " --> Message not of type QoS Negotiation";

            } else {

                //response received --> check contract
                cout << " --> received response";
                bool negotiationSuccessful = processQoSResponseIsSuccess(
                        incoming);

                if (negotiationSuccessful) {
                    // successfull negotiation
                    cout << " --> negotiation successful";

                    //create Connection request
                    QoSConnectionEstablish* establish = new QoSConnectionEstablish ();
                    establish->setType(
                            QoSConnectionEstablishMsgType::Establish_Request);
                    //TODO set other data ..

                    //send connection request
                    send(establish, "out");
                    cout << " --> send establish request";

                    //switch state to pending connection
                    _state = PENDING_CONNECTION;
                } else {
                    // negotiation failed. QUIT
                    cout << " --> negotiation Failed";
                    _state = FAILURE;
                }
            }
        } catch (exception& e) {
            cout << "Exception: " << e.what();
        }
        break;

    case PENDING_CONNECTION:
        break;

    default:
        //nothing to do we already finsihed our job..
        break;
    }

    //cleanup
    cout << endl;
    delete msg;
}

bool QoSClient::processQoSResponseIsSuccess(QoSNegotiationResponse* response) {
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

string QoSClient::getStateAsName() {
    switch (_state) {
    case STARTUP:
        return "STARTUP";
    case PENDING_REQUEST:
        return "PENDING_REQUEST";
    case PENDING_CONNECTION:
        return "PENDING_CONNECTION";
    case FAILURE:
        return "FAILURE";
    case SUCCESS:
        return "SUCCESS";
    default:
        return "-.-";
    }
}

} /* namespace soqosmw */
