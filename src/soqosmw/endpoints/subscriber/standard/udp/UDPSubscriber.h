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

#ifndef SOQOSMW_ENDPOINTS_SUBSCRIBER_STANDARD_UDP_UDPSUBSCRIBER_H_
#define SOQOSMW_ENDPOINTS_SUBSCRIBER_STANDARD_UDP_UDPSUBSCRIBER_H_

#include <endpoints/subscriber/standard/base/ISTDSubscriber.h>
#include <omnetpp/csimplemodule.h>
#include <string>

#include <inet/transportlayer/contract/udp/UDPControlInfo_m.h>
#include <inet/transportlayer/contract/udp/UDPSocket.h>

namespace soqosmw {
class ConnectionSpecificInformation;
} /* namespace soqosmw */

namespace soqosmw {

class UDPSubscriber: public soqosmw::ISTDSubscriber, public omnetpp::cSimpleModule {
public:
    UDPSubscriber(std::string publisherPath, SubscriptionReader* reader, ConnectionSpecificInformation* info);
    virtual ~UDPSubscriber();

    virtual void notify(omnetpp::cMessage* notification) override;

protected:

    /**
     * Should be redefined to contain the module's message handling function.
     * This default implementation issues an error message (throws cRuntimeError).
     */
    virtual void handleMessage(cMessage *msg);

private:
    /* Utility functions */
    virtual void connect();
    virtual void close();
    virtual void sendPacket(cPacket *pkt);
    virtual void handleTimer(cMessage *msg);

private:
    omnetpp::cGate* _udpOut;
//    omnetpp::cGate* _tcpIn;
    inet::UDPSocket socket;
    std::string _localAddress;
    int _localPort;
    std::string _remoteAddress;
    int _remotePort;
    bool _isConnected; // TODO really necessary?

    // statistics
    int numSessions;
    int numBroken;
    int packetsSent;
    int packetsRcvd;
    int bytesSent;
    int bytesRcvd;

};

} /*end namespace soqosmw*/


#endif /* SOQOSMW_ENDPOINTS_SUBSCRIBER_STANDARD_UDP_UDPSUBSCRIBER_H_ */
