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

#ifndef SOQOSMW_ENDPOINTS_SUBSCRIBER_STANDARD_TCP_TCPSUBSCRIBER_H_
#define SOQOSMW_ENDPOINTS_SUBSCRIBER_STANDARD_TCP_TCPSUBSCRIBER_H_




#include <endpoints/subscriber/standard/base/ISTDSubscriber.h>
#include <omnetpp/csimplemodule.h>
#include <string>

#include <inet/transportlayer/contract/tcp/TCPCommand_m.h>
#include <inet/transportlayer/contract/tcp/TCPSocket.h>

namespace soqosmw {
class ConnectionSpecificInformation;
} /* namespace soqosmw */

namespace soqosmw {

class TCPSubscriber: public soqosmw::ISTDSubscriber, public inet::TCPSocket::CallbackInterface, public omnetpp::cSimpleModule {
public:
    TCPSubscriber(std::string publisherPath, SubscriptionReader* reader, ConnectionSpecificInformation* info);
    virtual ~TCPSubscriber();

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

    /* TCPSocket::CallbackInterface callback methods */
    virtual void handleTimer(cMessage *msg);
    virtual void socketEstablished(int connId, void *yourPtr) override;
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent) override;
    virtual void socketPeerClosed(int connId, void *yourPtr) override;
    virtual void socketClosed(int connId, void *yourPtr) override;
    virtual void socketFailure(int connId, void *yourPtr, int code) override;
    virtual void socketStatusArrived(int connId, void *yourPtr, inet::TCPStatusInfo *status) override { delete status; }

private:
    omnetpp::cGate* _tcpOut;
    omnetpp::cGate* _tcpIn;
    inet::TCPSocket socket;
    std::string _localAddress;
    int _localPort;
    std::string _remoteAddress;
    int _remotePort;
    bool _isConnected;

    // statistics
    int numSessions;
    int numBroken;
    int packetsSent;
    int packetsRcvd;
    int bytesSent;
    int bytesRcvd;


};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_SUBSCRIBER_STANDARD_TCP_TCPSUBSCRIBER_H_ */
