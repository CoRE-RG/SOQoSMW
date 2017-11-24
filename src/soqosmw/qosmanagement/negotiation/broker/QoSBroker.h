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

#include <soqosmw/messages/Envelope_m.h>
#include <soqosmw/messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.h>
#include <soqosmw/base/EndpointDescription.h>

//INET
#include "inet/transportlayer/contract/udp/UDPSocket.h"

using namespace omnetpp;

namespace soqosmw {

/**
 * TODO - Generated class
 */
class QoSBroker
{
  public:
    QoSBroker(UDPSocket* socket, EndpointDescription local, EndpointDescription remote, bool isClient);
    virtual ~QoSBroker();

    virtual void handleMessage(QoSNegotiationProtocolMsg *msg);
    void handleStartSignal();

  protected:

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

  private:
    void handleRequest(QoSNegotiationRequest* request);
    void handleResponse(QoSNegotiationResponse* response);
    void handleEstablish(QoSNegotiationEstablish* establish);
    void handleFinalise(QoSNegotiationFinalise* finalise);

    bool isRequestAcceptable(QoSNegotiationRequest* request);
    bool isEstablishAcceptable(QoSNegotiationEstablish* establish);

    void fillEnvelope(soqosmw::Envelope* envelope);
    void sendMessage(QoSNegotiationProtocolMsg* msg);

    std::string getStateAsName();
    QoSBrokerStates_t _state;


    UDPSocket* _socket;

    EndpointDescription _me;
    EndpointDescription _you;
    bool _isClient;

    bool _parametersInitialized; //first initialization of parameters finished?
};

} /* namespace soqosmw */

#endif
