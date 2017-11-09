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

//INET
#include "inet/linklayer/common/MACAddress.h"

using namespace omnetpp;

namespace soqosmw {

/**
 * Statemachine for Broker.
 */
typedef enum QoSBrokerStates {
    SERVER_NO_SESSION,
    SERVER_PENDING_ACCEPT,
    SERVER_SESSION_ESTABLISHED,

    CLIENT_STARTUP,
    CLIENT_PENDING_REQUEST,
    CLIENT_PENDING_CONNECTION,
    CLIENT_FAILURE,
    CLIENT_SUCCESS
}QoSBrokerStates_t;

/**
 * TODO - Generated class
 */
class QoSBroker : public cSimpleModule
{
  public:
    QoSBroker();
    virtual ~QoSBroker();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleParameterChange(const char* parname);

  private:
    void serverHandleMessage(cMessage *msg);
    bool serverProcessQoSRequestIsAcceptable(QoSNegotiation* response);

    void clientHandleMessage(cMessage *msg);
    bool clientProcessQoSResponseIsSuccess(QoSNegotiationResponse* response);

    cPacket* extractMessage(cMessage *msg);
    void sendMessage(cPacket* msg);

    std::string getStateAsName();
    QoSBrokerStates_t _state;

    bool _useTargetGate;
    bool _useNetworkLayerOut;
    cModule* _targetModule; //targetModule object
    cGate* _targetGate; //targetGate object

    bool _isClient; //is client or server? TODO remove...

    inet::MACAddress destAddress; //destination address

    bool _parametersInitialized; //first initialization of parameters finished?
};

} /* namespace soqosmw */

#endif
