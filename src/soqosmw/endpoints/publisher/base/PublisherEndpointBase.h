//
// c Timo Haeckel for HAW Hamburg
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

#ifndef __SOQOSMW_PUBLISHERENDPOINTBASE_H_
#define __SOQOSMW_PUBLISHERENDPOINTBASE_H_

#include "soqosmw/endpoints/base/EndpointBase.h"

namespace SOQoSMW {

/**
 * @brief The PublisherEndpointBase implements the common interface for all endpoint modules (@see~EndpointBase).
 * Publishers are created by the QoSNegotiationProtocol module (@see~QoSNegotiationProtocol)
 * during runtime to connect realise a publishing endpoint for a service.
 * Publishers are connected to a specific transport and a publisher connector module (@see~PublisherConnector)
 * which loosely couples the publisher endpoint with a publisher application (@see~PublisherAppBase).
 *
 * @ingroup soqosmw/endpoints
 *
 * @author Timo Haeckel and Mehmet Cakir for HAW Hamburg
 */
class PublisherEndpointBase : public EndpointBase
{
public:
    bool isIsConnected() const {
        return _isConnected;
    }

    void setIsConnected(bool isConnected = false) {
        _isConnected = isConnected;
    }

protected:
    virtual void initialize() override;

    /**
     * Handles messages incoming from transport gate and
     * forwards them to the connector if they are for applications.
     *
     * @param msg   the message to handle.
     */
    virtual void handleTransportIn(cMessage *msg) override;

    /**
     * Handles messages incoming from the connector gate and
     * forwards them to the transport if needed.
     *
     * @param msg   the message to handle.
     */
    virtual void handleConnectorIn(cMessage *msg) override;

    /**
     * Publish a payload to all subscribers. This needs to be implemented by all subclasses.
     * The message will be deleted by the caller afterwards.
     *
     * @param payload   the payload to be published.
     */
    virtual void publish(cPacket* msg) = 0;



    /**
     * Is this publisher connected?
     */
    bool _isConnected = false;

    /**
     * Signal to capture statistics for connected remotes
     */
    simsignal_t _remotesSignal;

private:
    /**
     * Signal to capture statistics for sent messages
     */
    simsignal_t _msgSent;

    /**
     * Signal to capture statistics for dropped messages
     */
    simsignal_t _msgDrop;

};

} /*end namespace SOQoSMW*/

#endif
