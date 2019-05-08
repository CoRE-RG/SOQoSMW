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

#include <applications/base/SOQoSMWApplicationBase.h>
#include <connector/base/IConnector.h>
#include <connector/pubsub/writer/PublisherWriter.h>
#include <endpoints/base/IEndpoint.h>
#include <endpoints/publisher/base/IPublisher.h>
#include <endpoints/publisher/standard/tcp/TCPPublisher.h>
#include <messages/QoSNegotiationProtocol/ConnectionSpecificInformation_m.h>
#include <omnetpp/cgate.h>
#include <omnetpp/clog.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cpacket.h>
#include <omnetpp/simutil.h>
#include <qospolicy/base/qospolicy.h>
#include <iostream>


#include <inet/networklayer/common/L3Address.h>
#include <inet/networklayer/common/L3AddressResolver.h>

namespace soqosmw {
class ConnectionSpecificInformation;
} /* namespace soqosmw */

using namespace omnetpp;
using namespace inet;
using namespace std;

namespace soqosmw {


TCPPublisher::TCPPublisher(string path, PublisherWriter* writer) : ISTDPublisher(path, writer) {
    Enter_Method("TCPPublisher::TCPPublisher()");

    //set output gate for tcp connection
    _tcpOut = this->addGate("tcpOut", cGate::Type::OUTPUT);
    cGate* gateOut = getWriter()->getExecutingApplication()->gate("std_tcpOut")->getNextGate();
    getWriter()->getExecutingApplication()->gate("std_tcpOut")->disconnect();
    _tcpOut->connectTo(gateOut);

    //set input gate for tcp connection
    //_tcpIn = this->addGate("tcpIn", cGate::Type::INPUT);
    //getWriter()->getExecutingApplication()->gate("std_tcpIn")->connectTo(_tcpIn);

    numSessions = numBroken = packetsSent = packetsRcvd = bytesSent = bytesRcvd = 0;
    isConnected = false;
    //get address
    _localAddress = (dynamic_cast<LocalAddressQoSPolicy*>(getWriter()->getQoSValueFor(QoSPolicyNames::LocalAddress)))->getValue();
    //get port
    _localPort = (dynamic_cast<LocalPortQoSPolicy*>(getWriter()->getQoSValueFor(QoSPolicyNames::LocalPort)))->getValue();

    _serverSocket.renewSocket();
    _serverSocket.setDataTransferMode(TCPDataTransferMode::TCP_TRANSFER_OBJECT);
    _serverSocket.bind(*_localAddress.c_str() ? L3AddressResolver().resolve(_localAddress.c_str()) : L3Address(), _localPort);

    _serverSocket.setCallbackObject(this);//?
    _serverSocket.setOutputGate(_tcpOut);

    _serverSocket.listen();

}

TCPPublisher::~TCPPublisher() {
    // TODO Auto-generated destructor stub
}

void TCPPublisher::publish(omnetpp::cPacket* payload) {
    Enter_Method("TCPPublisher::publish()");
    //maybe pack package?!
    if(isConnected){
        sendPacket(payload);
    } else {
        delete payload;
    }
}

void TCPPublisher::handleMessage(cMessage* msg) {
    Enter_Method("TCPPublisher::handleMessage()");

    if (_serverSocket.belongsToSocket(msg)) {// match message and socket
        _serverSocket.processMessage(msg); // invoke callback interface
    } else {
        delete msg;
    }
}

ConnectionSpecificInformation* TCPPublisher::getConnectionSpecificInformation() {
    CSI_TCP* connection = new CSI_TCP();
    connection->setAddress(_localAddress.c_str());
    connection->setPort(_localPort);
    return connection;
}

void TCPPublisher::connect() {
    Enter_Method("TCPPublisher::connect()");
    // we need a new connId if this is not the first connection
    //socket.renewSocket();

    L3Address destination;
    L3AddressResolver().tryResolve(_localAddress.c_str(), destination);
    if (destination.isUnspecified()) {
        EV_ERROR << "Connecting to " << _localAddress << " port=" << _localPort << ": cannot resolve destination address\n";
    }
    else {
        EV_INFO << "Connecting to " << _localAddress << "(" << destination << ") port=" << _localPort << endl;

        _serverSocket.connect(destination, _localPort);
    }
}

void TCPPublisher::close() {
    Enter_Method("TCPPublisher::close()");
    EV_INFO << "issuing CLOSE command\n";
    isConnected = false;
    _serverSocket.close();
    //shouldnt we clean up an delete this publisher?!
}

void TCPPublisher::sendPacket(cPacket* pkt) {
    Enter_Method("TCPPublisher::sendPacket()");
    int numBytes = pkt->getByteLength();

    for (auto processor : _processors){
        processor->deliver(pkt, "PubMessage");
    }

    delete pkt;
    packetsSent++;
    bytesSent += numBytes;
}

void TCPPublisher::socketEstablished(int connId, void* yourPtr) {
    Enter_Method("TCPPublisher::socketEstablished()");
    // *redefine* to perform or schedule first sending
    //EV_INFO << "connected\n";
    numSessions++;
    isConnected = true;
}

void TCPPublisher::socketDataArrived(int connId, void* yourPtr, cPacket* msg,
        bool urgent) {
    Enter_Method("TCPPublisher::socketDataArrived()");
    // *redefine* to perform or schedule next sending
    packetsRcvd++;
    bytesRcvd += msg->getByteLength();
    delete msg;
}

void TCPPublisher::socketPeerClosed(int connId, void* yourPtr) {
    Enter_Method("TCPPublisher::socketPeerClosed()");
    TCPSocket* socket = (TCPSocket*)(yourPtr);
    // close the connection (if not already closed)
    if (socket && socket->getState() == TCPSocket::PEER_CLOSED) {
        EV_INFO << "remote TCP closed, closing here as well\n";
        socket->close();
        numSessions--;
        if(numSessions == 0){
            isConnected = false;
        }
    }
}

void TCPPublisher::socketClosed(int connId, void* yourPtr) {
    Enter_Method("TCPPublisher::socketClosed()");
    // *redefine* to start another session etc.
    EV_INFO << "connection closed\n";
    // close the connection (if not already closed)
}

void TCPPublisher::handleTimer(cMessage* msg) {
    Enter_Method("TCPPublisher::handleTimer()");
    delete msg;
}

void TCPPublisher::notify(omnetpp::cMessage* notification) {
    Enter_Method("TCPPublisher::notify()");
    TCPCommand *ind = dynamic_cast<TCPCommand *>(notification->getControlInfo());
    if (!ind) {
        delete notification;
        return;
    }
    //check if for server
    if (_serverSocket.belongsToSocket(notification)) {// match message and socket
        _serverSocket.processMessage(notification);
    } else {
        //check if it belongs to a socket in the map
        TCPSocket *socket = _socketMap.findSocketFor(notification);

        //if not open a new one!
        if (!socket) {
            // new connection -- create new socket object and server process
            socket = new TCPSocket(notification);
            socket->setOutputGate(gate("tcpOut"));

            socket->setCallbackObject(this, socket);

            _socketMap.addSocket(socket);
            _processors.push_back(new TCPSocketProcessor(socket));
        }
        socket->processMessage(notification); // invoke callback interface
    }
}

void TCPPublisher::socketFailure(int connId, void* yourPtr, int code) {
    Enter_Method("TCPPublisher::socketFailure()");
    // subclasses may override this function, and add code try to reconnect after a delay.
    EV_WARN << "connection broken\n";
    numBroken++;
}

}// end namespace soqosmw
