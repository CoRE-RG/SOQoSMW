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

#include <base/EndpointDescription.h>
#include <string>

namespace soqosmw {
class LocalServiceManager;
} /* namespace soqosmw */

namespace soqosmw {
class Request;
} /* namespace soqosmw */

namespace inet {
class UDPSocket;
} /* namespace inet */

namespace soqosmw {
class Envelope;
class QoSNegotiationEstablish;
class QoSNegotiationFinalise;
class QoSNegotiationProtocolMsg;
class QoSNegotiationRequest;
class QoSNegotiationResponse;
} /* namespace soqosmw */

using namespace omnetpp;

namespace soqosmw {

/**
 * @brief QoSBroker handles the negotiation for a connection.
 *
 * @ingroup soqosmw/qosmanagement
 *
 * @author Timo Haeckel
 */
class QoSBroker {
public:
    /**
     * Constructor.
     * @param socket The UDP socket for outgoing messages.
     * @param local The local endpoint description.
     * @param remote The remote endpoint description.
     * @param isClient Is this the client?
     */
    QoSBroker(inet::UDPSocket* socket, LocalServiceManager* lsm, EndpointDescription local,
            EndpointDescription remote, Request* request);
    virtual ~QoSBroker();

    /**
     * Handle a QoSNegotiationProtocol Message.
     * @param msg The message to handle.
     */
    virtual bool handleMessage(QoSNegotiationProtocolMsg *msg);

    /**
     * handle the start signal, only if client!
     */
    bool startNegotiation();

    /**
     * Checks whether this Broker is responsible for the negotiation between local and remote Endpoint.
     * @return true if Broker is responsible.
     */
    bool isResponsibleFor(EndpointDescription& local, EndpointDescription& remote);

    /**
     * Checks whether the Negotiation has been finished and the broker can be removed.
     */
    bool isNegotiationFinished() {
        return _negotiationFinished;
    }

    simtime_t getTimeStamp();

protected:

    /**
     * Statemachine for Broker.
     */
    typedef enum QoSBrokerStates {
        SERVER_NO_SESSION,
        SERVER_PENDING_ACCEPT,
        SERVER_SESSION_ESTABLISHED,
        SERVER_FAILURE,

        CLIENT_STARTUP,
        CLIENT_PENDING_REQUEST,
        CLIENT_PENDING_CONNECTION,
        CLIENT_FAILURE,
        CLIENT_SUCCESS
    } QoSBrokerStates_t;

private:
    /**
     * Handle the request, emits a response.
     * @param request The request to handle.
     */
    bool handleRequest(QoSNegotiationRequest* request);

    /**
     * Handle the response, emits a establish if successful.
     * @param response The response to handle.
     */
    bool handleResponse(QoSNegotiationResponse* response);

    /**
     * Handle the establish, emits a finalise if successful.
     * @param establish The establish to handle.
     */
    bool handleEstablish(QoSNegotiationEstablish* establish);

    /**
     * Handle the finalise, returns to the application with negotiation status.
     * @param finalise The finalise to handle.
     */
    bool handleFinalise(QoSNegotiationFinalise* finalise);

    /**
     * Check if a request is acceptable.
     * @param request The request to check.
     * @return true if acceptable, otherwise false.
     */
    bool isRequestAcceptable(QoSNegotiationRequest* request);

    /**
     * Check if an establish is acceptable.
     * @param establish The establish to check.
     * @return true if acceptable, otherwise false.
     */
    bool isEstablishAcceptable(QoSNegotiationEstablish* establish);

    /**
     * Fill the soqosmw envelope with the endpoint descriptions.
     * @param envelope The envelope to fill.
     */
    void fillEnvelope(Envelope* envelope);

    /**
     * Send a QoSNegotiationProtocolMsg via UDP.
     * @param msg The message to send.
     */
    void sendMessage(QoSNegotiationProtocolMsg* msg);

    /**
     * finish negotiation and allow this QoSBroker to be deleted.
     */
    void finishNegotiation();

    /**
     * Getter for the state.
     * @return the name of the current state.
     */
    std::string getStateAsName();

    /**
     * Holds the current state.
     */
    QoSBrokerStates_t _state;

    /**
     * Holds a pointer to the UDPSocket.
     */
    inet::UDPSocket* _socket;

    /**
     * Reference to the local service manager.
     */
    LocalServiceManager* _lsm;

    /**
     * My Endpoint.
     */
    EndpointDescription _local;

    /**
     * Your Endpoint.
     */
    EndpointDescription _remote;

    /**
     * The Request reference.
     */
    Request* _request;

    /**
     * True if negotiation has finished and broker is no longer needed.
     */
    bool _negotiationFinished;

    /**
     * Time stamp
     */
    simtime_t _timeStamp;
};

} /* namespace soqosmw */

#endif
