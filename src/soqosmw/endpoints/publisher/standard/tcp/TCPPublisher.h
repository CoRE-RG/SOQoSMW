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

#ifndef SOQOSMW_ENDPOINTS_PUBLISHER_STANDARD_TCP_TCPPUBLISHER_H_
#define SOQOSMW_ENDPOINTS_PUBLISHER_STANDARD_TCP_TCPPUBLISHER_H_



#include <endpoints/publisher/standard/base/ISTDPublisher.h>
#include <omnetpp/csimplemodule.h>
#include <string>

#include <inet/transportlayer/contract/tcp/TCPCommand_m.h>
#include <inet/transportlayer/contract/tcp/TCPSocket.h>
#include <inet/transportlayer/contract/tcp/TCPSocketMap.h>

namespace soqosmw {

class TCPPublisher: public soqosmw::ISTDPublisher, public inet::TCPSocket::CallbackInterface, public omnetpp::cSimpleModule {
private:
    class TCPSocketProcessor{

    public:
        TCPSocketProcessor(inet::TCPSocket* socket){
            _socket = socket;
        }
        virtual ~TCPSocketProcessor(){

        }

        void deliver(omnetpp::cPacket* payload, const char *message = "" ){
            omnetpp::cPacket* deliver = new cPacket();
            deliver->setTimestamp();
            deliver->setByteLength(payload->getByteLength());
            deliver->setName(message);
            _socket->send(deliver);
        }


    private:
        inet::TCPSocket* _socket;
    };

public:
    TCPPublisher(std::string path, PublisherWriter* writer);
    virtual ~TCPPublisher();

    virtual void publish(omnetpp::cPacket* payload) override;

    virtual ConnectionSpecificInformation* getConnectionSpecificInformation() override;

    virtual void notify(omnetpp::cMessage* notification) override;

    /**
     * Get the qos class for this publisher
     */
    virtual QoSGroups getQoSClass() override {
        return QoSGroups::STD_TCP;
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
    inet::TCPSocket _serverSocket;
    inet::TCPSocketMap _socketMap;
    std::vector<TCPSocketProcessor*> _processors;
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
#endif /* SOQOSMW_ENDPOINTS_PUBLISHER_STANDARD_TCP_TCPPUBLISHER_H_ */
