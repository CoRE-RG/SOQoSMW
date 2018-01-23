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

#include <omnetpp/csimplemodule.h>
#include <string>
#include <vector>

#include <inet/networklayer/common/L3Address.h>
#include <inet/transportlayer/contract/udp/UDPSocket.h>

namespace soqosmw {
class Request;
class Envelope;
class QoSBroker;
class QoSNegotiationEstablish;
class QoSNegotiationFinalise;
class QoSNegotiationRequest;
class QoSNegotiationResponse;
} /* namespace soqosmw */

using namespace omnetpp;

namespace soqosmw {

#define NO_OF_INIT_STAGES 15
#define MY_INIT_STAGE 13

/**
 * @brief QoSNegotiationProtocol provides all functionality to negotiatiate the QoS Policies for a connection of to @class{IEndpoints}.
 *
 * @ingroup soqosmw/qosmanagement
 *
 * @author Timo Haeckel
 */
class QoSNegotiationProtocol: public cSimpleModule {
    friend class LocalServiceManager;
    friend class QoSBroker;
public:
    QoSNegotiationProtocol();
    virtual ~QoSNegotiationProtocol();

protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override {
        return NO_OF_INIT_STAGES;
    }
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleParameterChange(const char* parname) override;

private:

    int getProtocolPort();

    void createQoSBroker(Request* request);

    /**
     * Fills the soqosmw message envelope with endpoint descriptions.
     * @param envelope
     */
    void fillEnvelope(Envelope* envelope);

    /**
     * Sends a message via UDP.
     * @param msg the message to send.
     */
    void sendMessage(cPacket* msg);

    /**
     * Sets up the UDP socket.
     */
    void socketSetup();

    /**
     * Checks if a socket is bound.
     * @return true if the socket is bound, otherwise false.
     */
    bool isSocketBound();

    /**
     * Closes the UDP connection.
     */
    void socketClose();

    /**
     * Caches the localAddress parameter.
     */
    inet::L3Address _localAddress;

    /**
     * Caches the protocolPort parameter.
     */
    int _protocolPort;

    /**
     * The UDP Socket for sending and receiving messages.
     */
    inet::UDPSocket _socket;

    /**
     * Check if the socket is bound.
     */
    bool _socketBound;

    /**
     * A QoS Broker that handles the negotiation.
     */
    std::vector<QoSBroker*> _brokers;
};

} /* namespace soqosmw */

#endif
