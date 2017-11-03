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

namespace soqosmw {

Define_Module(QoSBroker);

void QoSBroker::initialize() {
    _state = NO_SESSION;
}

void QoSBroker::handleMessage(cMessage *msg) {
    cout << "QoSBroker::" << getStateAsName() << " --> message received";

    switch (_state) {
    case NO_SESSION:
        try {
            //check incoming message class
            QoSNegotiationRequest* incoming = dynamic_cast<QoSNegotiationRequest*>(msg);

            if (incoming == 0) {
                //not a QoS Negotiation class.
                cout << " --> Message not of type QoS Negotiation";

            } else {

                //request received --> check requirements
                cout << " --> received request";
                bool requestAcceptables = processQoSRequestIsAcceptable(
                        incoming);

                //create response
                QoSNegotiationResponse* response = new QoSNegotiationResponse();
                //TODO set other data ..

                if (requestAcceptables) {
                    // successfull negotiation
                    cout << " --> request acceptable";

                    //create accept payload
                    response->getPayload().setResposeStatus(QoSNegotiationResponseStatus::QoS_ResponseStatusSuccess);

                    //switch state to pending accept
                    _state = PENDING_ACCEPT;
                } else {
                    // negotiation failed. QUIT
                    cout << " --> request unacceptable";

                    //create accept payload
                    response->getPayload().setResposeStatus(QoSNegotiationResponseStatus::QoS_ResponseStatusFailure);

                    //switch state to no session
                    _state = NO_SESSION;
                }

                //send response
                send(response, "avbChannel$o");
                cout << " --> send response";
            }
        } catch (exception& e) {
            cout << "Exception: " << e.what();
        }
        break;
    case PENDING_ACCEPT:
        break;
    case SESSION_ESTABLISHED:
        break;
    default:
        //nothing to do here...
        break;
    }

    cout << endl;
    delete msg;
}

string QoSBroker::getStateAsName() {
    switch (_state) {
    case NO_SESSION:
        return "NO_SESSION";
    case PENDING_ACCEPT:
        return "PENDING_ACCEPT";
    case SESSION_ESTABLISHED:
        return "SESSION_ESTABLISHED";
    default:
        return "-.-";
    }
}

bool QoSBroker::processQoSRequestIsAcceptable(QoSNegotiation* request) {
    //get payload
    return true;
}
} /* namespace soqosmw */
