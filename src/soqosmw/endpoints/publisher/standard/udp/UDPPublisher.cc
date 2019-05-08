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
#include <endpoints/publisher/standard/udp/UDPPublisher.h>
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

UDPPublisher::UDPPublisher(string path, PublisherWriter* writer) : ISTDPublisher(path, writer) {
    Enter_Method("UDPPublisher::UDPPublisher()");

    //set output gate for udp connection
    _udpOut = this->addGate("udpOut", cGate::Type::OUTPUT);
    cGate* gateOut = getWriter()->getExecutingApplication()->gate("std_udpOut")->getNextGate();
    getWriter()->getExecutingApplication()->gate("std_udpOut")->disconnect();
    _udpOut->connectTo(gateOut);

    numSessions = numBroken = packetsSent = packetsRcvd = bytesSent = bytesRcvd = 0;
    isConnected = false;
    //get address
    _localAddress = (dynamic_cast<LocalAddressQoSPolicy*>(getWriter()->getQoSValueFor(QoSPolicyNames::LocalAddress)))->getValue();
    //get port
    _localPort = (dynamic_cast<LocalPortQoSPolicy*>(getWriter()->getQoSValueFor(QoSPolicyNames::LocalPort)))->getValue();

    _serverSocket.setOutputGate(_udpOut);
    _serverSocket.setReuseAddress(true);
    _serverSocket.bind(*_localAddress.c_str() ? L3AddressResolver().resolve(_localAddress.c_str()) : L3Address(), _localPort);
    isConnected = true;
}

UDPPublisher::~UDPPublisher() {
    // TODO Auto-generated destructor stub
}

void UDPPublisher::publish(omnetpp::cPacket* payload) {
    Enter_Method("UDPPublisher::publish()");
    //maybe pack package?!
    if(isConnected){
        sendPacket(payload);
    } else {
        delete payload;
    }
}

void UDPPublisher::handleMessage(cMessage* msg) {
    Enter_Method("UDPPublisher::handleMessage()");

    if (_serverSocket.belongsToSocket(msg)) {// match message and socket
        EV << "Message: " << msg;
    } else {
        delete msg;
    }
}

ConnectionSpecificInformation* UDPPublisher::getConnectionSpecificInformation() {
    CSI_UDP* connection = new CSI_UDP();
    connection->setAddress(_localAddress.c_str());
    connection->setPort(_localPort);
    return connection;
}

void UDPPublisher::connect() {
    // TODO UDP add parameters to connect to subscriber direktly
    Enter_Method("UDPPublisher::connect()");
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

void UDPPublisher::close() {
    Enter_Method("UDPPublisher::close()");
    EV_INFO << "issuing CLOSE command\n";
    isConnected = false;
    _serverSocket.close();
    //TODO shouldnt we clean up an delete this publisher?!
}

void UDPPublisher::sendPacket(cPacket* pkt) {
    Enter_Method("UDPPublisher::sendPacket()");
    int numBytes = pkt->getByteLength();

    for (auto processor : _processors){
        processor->deliver(pkt, "PubMessage");
    }

    delete pkt;
    packetsSent++;
    bytesSent += numBytes;
}

void UDPPublisher::handleTimer(cMessage* msg) {
    Enter_Method("UDPPublisher::handleTimer()");
    delete msg;
}

void UDPPublisher::notify(omnetpp::cMessage* notification) {
    Enter_Method("UDPPublisher::notify()");
    UDPControlInfo *ind = dynamic_cast<UDPControlInfo *>(notification->getControlInfo());
    if (!ind) {
        delete notification;
        return;
    }
    //check if for server
    if (_serverSocket.belongsToSocket(notification)) {// match message and socket
        EV << "Notification: " << notification;
    } else {
        EV << "Notification isn't intended for this socket.";
    }
}

void UDPPublisher::addConnection(
    ConnectionSpecificInformation* csi) {
    if(CSI_UDP* csiUdp = dynamic_cast<CSI_UDP*>(csi)){
        // create new processor and add to list
        _processors.push_back(new UDPSocketProcessor(&_serverSocket, csiUdp->getAddress(), csiUdp->getPort()));
    }
}

}
    // end namespace soqosmw

