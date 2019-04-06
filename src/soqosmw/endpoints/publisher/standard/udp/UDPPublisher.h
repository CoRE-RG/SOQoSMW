/*
 * UDPPublisher.h
 *
 *  Created on: Apr 6, 2019
 *      Author: mehkir
 */

#ifndef SOQOSMW_ENDPOINTS_PUBLISHER_STANDARD_UDP_UDPPUBLISHER_H_
#define SOQOSMW_ENDPOINTS_PUBLISHER_STANDARD_UDP_UDPPUBLISHER_H_

#include <endpoints/publisher/standard/base/ISTDPublisher.h>
#include <omnetpp/csimplemodule.h>
#include <string>

#include <inet/transportlayer/contract/udp/UDPControlInfo_m.h>
#include <inet/transportlayer/contract/udp/UDPControlInfo.h>
#include <inet/transportlayer/contract/udp/UDPSocket.h>

namespace soqosmw {

class UDPPublisher: public soqosmw::ISTDPublisher, public omnetpp::cSimpleModule {
private:
    class UDPSocketProcessor {

    public:
        UDPSocketProcessor(inet::UDPSocket* socket){
            _socket = socket;
        }
        virtual ~UDPSocketProcessor(){

        }

        void deliver(omnetpp::cPacket* payload, const char *message = ""){
            omnetpp::cPacket* deliver = new cPacket();
            deliver->setTimestamp();
            deliver->setByteLength(payload->getByteLength());
            deliver->setName(message);
            _socket->send(deliver);
        }

    private:
        inet::UDPSocket* _socket;
    };

public:
    UDPPublisher(std::string path, PublisherWriter* writer);
    virtual ~UDPPublisher();

    virtual void publish(omnetpp::cPacket* payload) override;

    virtual ConnectionSpecificInformation* getConnectionSpecificInformation() override;

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
