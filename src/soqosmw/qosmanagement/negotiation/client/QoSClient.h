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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_QOSCLIENT_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_QOSCLIENT_H_

#include <omnetpp.h>
#include <string>
#include "soqosmw/qosmanagement/negotiation/messages/QoSNegotiationMessages_m.h"

using namespace omnetpp;

namespace soqosmw {

/**
 * Statemachine for client.
 */
typedef enum QoSClientStates {
    STARTUP = 0,
    PENDING_REQUEST = 1,
    PENDING_CONNECTION = 2,
    FAILURE = 3,
    SUCCESS = 4
}QoSClientStates_t;

/**
 * TODO - Generated class
 */
class QoSClient : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:

    bool processQoSResponseIsSuccess(QoSNegotiationResponse* response);
    std::string getStateAsName();
    QoSClientStates_t _state;
};

} /* namespace soqosmw */

#endif
