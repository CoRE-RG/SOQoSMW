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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_QOSBROKER_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_QOSBROKER_H_

#include <omnetpp.h>
#include <string>
#include "soqosmw/qosmanagement/negotiation/messages/QoSNegotiationMessages_m.h"

using namespace omnetpp;

namespace soqosmw {

/**
 * Statemachine for Broker.
 */
typedef enum QoSBrokerStates {
    NO_SESSION = 0,
    PENDING_ACCEPT = 1,
    SESSION_ESTABLISHED = 2,
}QoSBrokerStates_t;

/**
 * TODO - Generated class
 */
class QoSBroker : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    bool processQoSRequestIsAcceptable(QoSNegotiation* response);

    std::string getStateAsName();
    QoSBrokerStates_t _state;
};

} /* namespace soqosmw */

#endif
