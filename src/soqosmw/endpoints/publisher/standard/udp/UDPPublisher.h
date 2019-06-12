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

#ifndef SOQOSMW_ENDPOINTS_PUBLISHER_STANDARD_UDP_UDPPUBLISHER_H_
#define SOQOSMW_ENDPOINTS_PUBLISHER_STANDARD_UDP_UDPPUBLISHER_H_

#include <endpoints/publisher/standard/base/ISTDPublisher.h>
#include <omnetpp/csimplemodule.h>
#include <string>

#include <inet/transportlayer/contract/udp/UDPControlInfo_m.h>
#include <inet/transportlayer/contract/udp/UDPControlInfo.h>
#include <inet/transportlayer/contract/udp/UDPSocket.h>


#include <inet/networklayer/common/L3Address.h>
#include <inet/networklayer/common/L3AddressResolver.h>

namespace soqosmw {

class UDPPublisher: public soqosmw::ISTDPublisher, public omnetpp::cSimpleModule {
private:
    class UDPSocketProcessor {

    public:
        UDPSocketProcessor(inet::UDPSocket* socket, const char * remoteAddress, int remotePort){
            _socket = socket;
            _remoteAddress = inet::L3AddressResolver().resolve(remoteAddress);
            _remotePort = remotePort;
        }
        virtual ~UDPSocketProcessor(){

        }

        void deliver(omnetpp::cPacket* payload, const char *message = ""){
            omnetpp::cPacket* deliver = new cPacket();
            deliver->setTimestamp();
            deliver->setByteLength(payload->getByteLength());
            deliver->setName(message);
            _socket->sendTo(deliver, _remoteAddress, _remotePort);
        }

    private:
        inet::UDPSocket* _socket;
        inet::L3Address _remoteAddress;
        int _remotePort;
    };

public:
    UDPPublisher(std::string path, PublisherWriter* writer);
    virtual ~UDPPublisher();

    virtual void publish(omnetpp::cPacket* payload) override;

    virtual ConnectionSpecificInformation* getConnectionSpecificInformation() override;

    virtual void notify(omnetpp::cMessage* notification) override;

    void addConnection(ConnectionSpecificInformation* csi);

    /**
     * Get the qos class for this publisher
     */
    virtual QoSGroups getQoSClass() override {
        return QoSGroups::STD_UDP;
    }

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
    omnetpp::cGate* _udpIn;
    inet::UDPSocket _serverSocket;
    // inet::UDPSocketMap _socketMap;
    std::vector<UDPSocketProcessor*> _processors;
    std::string _localAddress;
    int _localPort;
    bool isConnected;

    // statistics
    int numSessions;
    int numBroken;
    int packetsSent;
    int packetsRcvd;
    int bytesSent;
    int bytesRcvd;


};

}// end namespace soqosmw
#endif /* SOQOSMW_ENDPOINTS_PUBLISHER_STANDARD_UDP_UDPPUBLISHER_H_ */
