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
#include <connector/pubsub/reader/SubscriptionReader.h>
#include <endpoints/subscriber/base/ISubscriber.h>
#include <endpoints/subscriber/standard/tcp/TCPSubscriber.h>
#include <messages/QoSNegotiationProtocol/ConnectionSpecificInformation_m.h>
#include <omnetpp/cexception.h>
#include <omnetpp/cgate.h>
#include <omnetpp/clog.h>
#include <omnetpp/cpacket.h>
#include <omnetpp/simutil.h>
#include <qospolicy/base/types/IntQoSPolicy.h>
#include <qospolicy/base/types/StringQoSPolicy.h>
#include <qospolicy/tcp/LocalAddressQoSPolicy.h>
#include <qospolicy/tcp/LocalPortQoSPolicy.h>
#include <iostream>

#include <inet/networklayer/common/L3Address.h>
#include <inet/networklayer/common/L3AddressResolver.h>

using namespace std;
using namespace inet;
using namespace omnetpp;

namespace soqosmw {

TCPSubscriber::TCPSubscriber(string publisherPath, SubscriptionReader* reader, ConnectionSpecificInformation* info) :
        ISTDSubscriber(publisherPath, reader) {
    Enter_Method("TCPSubscriber::TCPSubscriber()");
    if(info->getConnectionType() == ConnectionType::ct_tcp){
        CSI_TCP* connection = dynamic_cast<CSI_TCP*>(info);

        //set output gate for tcp connection.
        _tcpOut = this->addGate("tcpOut", cGate::Type::OUTPUT);
        cGate* gateOut = getReader()->getExecutingApplication()->gate("std_tcpOut")->getNextGate();
        getReader()->getExecutingApplication()->gate("std_tcpOut")->disconnect();
        _tcpOut->connectTo(gateOut);

        //set input gate for tcp connection
        //_tcpIn = this->addGate("tcpIn", cGate::Type::INPUT);
        //getReader()->getExecutingApplication()->gate("std_tcpIn")->connectTo(_tcpIn);

        numSessions = numBroken = packetsSent = packetsRcvd = bytesSent = bytesRcvd = 0;
        _isConnected = false;
        //get address
        _localAddress = (dynamic_cast<LocalAddressQoSPolicy*>(getReader()->getQoSValueFor(QoSPolicyNames::LocalAddress)))->getValue();
        //get port
        _localPort = (dynamic_cast<LocalPortQoSPolicy*>(getReader()->getQoSValueFor(QoSPolicyNames::LocalPort)))->getValue();

        _remoteAddress = connection->getAddress();
        _remotePort = connection->getPort();

        socket.setCallbackObject(this);
        socket.setOutputGate(_tcpOut);

        connect();

    } else{
        throw cRuntimeError("No AVB Connection information available");
    }
}

TCPSubscriber::~TCPSubscriber() {
    // TODO Auto-generated destructor stub
}

void TCPSubscriber::connect() {
    Enter_Method("TCPSubscriber::connect()");

    // we need a new connId if this is not the first connection
    //socket.renewSocket();

    socket.renewSocket();
    socket.setDataTransferMode(TCPDataTransferMode::TCP_TRANSFER_OBJECT);
    socket.bind(*_localAddress.c_str() ? L3AddressResolver().resolve(_localAddress.c_str()) : L3Address(), _localPort);


    L3Address destination;
    L3AddressResolver().tryResolve(_remoteAddress.c_str(), destination);
    if (destination.isUnspecified()) {
        //EV_ERROR << "Connecting to " << _remoteAddress << " port=" << _remotePort << ": cannot resolve destination address\n";
    }
    else {
        //EV_INFO << "Connecting to " << _remoteAddress << "(" << destination << ") port=" << _remotePort << endl;

        socket.connect(destination, _remotePort);

        numSessions++;
    }
}

void TCPSubscriber::close() {
    Enter_Method("TCPSubscriber::close()");
    EV_INFO << "issuing CLOSE command\n";
    _isConnected = false;
    socket.close();
    //shouldnt we clean up an delete this subscriber?!
}

void TCPSubscriber::sendPacket(cPacket* pkt) {
    Enter_Method("TCPSubscriber::sendPacket()");
    int numBytes = pkt->getByteLength();
    socket.send(pkt);

    packetsSent++;
    bytesSent += numBytes;
}

void TCPSubscriber::socketEstablished(int connId, void* yourPtr) {
    Enter_Method("TCPSubscriber::socketEstablished()");
    // *redefine* to perform or schedule first sending
    //EV_INFO << "connected\n";
    _isConnected = true;
}

void TCPSubscriber::socketDataArrived(int connId, void* yourPtr, cPacket* msg,
        bool urgent) {
    Enter_Method("TCPSubscriber::socketDataArrived()");
    getReader()->put(msg);
    // *redefine* to perform or schedule next sending
    packetsRcvd++;
    bytesRcvd += msg->getByteLength();
}

void TCPSubscriber::socketPeerClosed(int connId, void* yourPtr) {
    Enter_Method("TCPSubscriber::socketPeerClosed()");
    // close the connection (if not already closed)
    if (socket.getState() == TCPSocket::PEER_CLOSED) {
        EV_INFO << "remote TCP closed, closing here as well\n";
        close();
        _isConnected = false;
    }
}

void TCPSubscriber::socketClosed(int connId, void* yourPtr) {
    Enter_Method("TCPSubscriber::socketClosed()");
    // *redefine* to start another session etc.
    EV_INFO << "connection closed\n";
    _isConnected = false;
}

void TCPSubscriber::handleTimer(cMessage* msg) {
    Enter_Method("TCPSubscriber::handleTimer()");
    delete msg;
}

void TCPSubscriber::handleMessage(cMessage* msg) {
    Enter_Method("TCPSubscriber::handleMessage()");
    if (socket.belongsToSocket(msg)) {// match message and socket
        socket.processMessage(msg); // invoke callback interface
    } else {
        delete msg;
    }
}

void TCPSubscriber::notify(omnetpp::cMessage* notification) {
    Enter_Method("TCPSubscriber::notify()");



        if (socket.belongsToSocket(notification)) {// match message and socket
            socket.processMessage(notification); // invoke callback interface
        } else {
            TCPCommand* ctrlInfo = dynamic_cast<TCPCommand *>(notification->getControlInfo());
            if(ctrlInfo) {
                ctrlInfo->setConnId(socket.getConnectionId());
            }
    //        delete notification;
        }
}

void TCPSubscriber::socketFailure(int connId, void* yourPtr, int code) {
    Enter_Method("TCPSubscriber::socketFailure()");
    // subclasses may override this function, and add code try to reconnect after a delay.
    EV_WARN << "connection broken\n";
    numBroken++;
}

} /*end namespace soqosmw*/

