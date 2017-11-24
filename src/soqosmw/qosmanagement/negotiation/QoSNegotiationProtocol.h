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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_QoSNegotiationProtocol_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_QoSNegotiationProtocol_H_

#include <omnetpp.h>
#include <string>

#include <soqosmw/messages/Envelope_m.h>
#include <soqosmw/messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.h>

//INET
#include "inet/networklayer/common/L3Address.h"
#include "inet/transportlayer/contract/udp/UDPSocket.h"

using namespace omnetpp;

namespace soqosmw {

/**
 * Statemachine for Broker.
 */
typedef enum QoSNegotiationProtocolStates {
    SERVER_NO_SESSION,
    SERVER_PENDING_ACCEPT,
    SERVER_SESSION_ESTABLISHED,

    CLIENT_STARTUP,
    CLIENT_PENDING_REQUEST,
    CLIENT_PENDING_CONNECTION,
    CLIENT_FAILURE,
    CLIENT_SUCCESS
}QoSNegotiationProtocolStates_t;

#define NO_OF_INIT_STAGES 15
#define MY_INIT_STAGE 13

/**
 * TODO - Generated class
 */
class QoSNegotiationProtocol : public cSimpleModule
{
  public:
    QoSNegotiationProtocol();
    virtual ~QoSNegotiationProtocol();

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override {
        return NO_OF_INIT_STAGES;
    }
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleParameterChange(const char* parname);

  private:

    void handleStartSignal();
    void handleRequest(QoSNegotiationRequest* request);
    void handleResponse(QoSNegotiationResponse* response);
    void handleEstablish(QoSNegotiationEstablish* establish);
    void handleFinalise(QoSNegotiationFinalise* finalise);

    bool isRequestAcceptable(QoSNegotiationRequest* request);
    bool isEstablishAcceptable(QoSNegotiationEstablish* establish);

    void fillEnvelope(soqosmw::Envelope* envelope);
    void sendMessage(cPacket* msg);

    std::string getStateAsName();
    QoSNegotiationProtocolStates_t _state;

    //udp specific
    void socketSetup();
    bool isSocketBound();
    void socketClose();

    bool _isClient; //is client or server? TODO remove...

    L3Address _localAddress;
    L3Address _destAddress;
    int _protocolPort;

    bool _parametersInitialized; //first initialization of parameters finished?

    UDPSocket _socket;
    bool _socketBound;
};

} /* namespace soqosmw */

#endif
