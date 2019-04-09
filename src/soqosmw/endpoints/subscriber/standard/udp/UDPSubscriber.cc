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
#include <endpoints/subscriber/standard/udp/UDPSubscriber.h>
#include <messages/QoSNegotiationProtocol/ConnectionSpecificInformation_m.h>
#include <omnetpp/cexception.h>
#include <omnetpp/cgate.h>
#include <omnetpp/clog.h>
#include <omnetpp/cpacket.h>
#include <omnetpp/simutil.h>
#include <qospolicy/base/types/IntQoSPolicy.h>
#include <qospolicy/base/types/StringQoSPolicy.h>
#include <qospolicy/std/LocalAddressQoSPolicy.h>
#include <qospolicy/std/LocalPortQoSPolicy.h>
#include <iostream>

#include <inet/networklayer/common/L3Address.h>
#include <inet/networklayer/common/L3AddressResolver.h>

using namespace std;
using namespace inet;
using namespace omnetpp;

namespace soqosmw {

UDPSubscriber::UDPSubscriber(string publisherPath, SubscriptionReader* reader, ConnectionSpecificInformation* info) :
        ISTDSubscriber(publisherPath, reader) {
    Enter_Method("UDPSubscriber::UDPSubscriber()");
    if(info->getConnectionType() == ConnectionType::ct_udp){
        CSI_UDP* connection = dynamic_cast<CSI_UDP*>(info);

        //set output gate for tcp connection.
        _udpOut = this->addGate("udpOut", cGate::Type::OUTPUT);
        cGate* gateOut = getReader()->getExecutingApplication()->gate("std_udpOut")->getNextGate();
        getReader()->getExecutingApplication()->gate("std_udpOut")->disconnect();
        _udpOut->connectTo(gateOut);

        numSessions = numBroken = packetsSent = packetsRcvd = bytesSent = bytesRcvd = 0;
        _isConnected = false;
        //get address
        _localAddress = (dynamic_cast<LocalAddressQoSPolicy*>(getReader()->getQoSValueFor(QoSPolicyNames::LocalAddress)))->getValue();
        //get port
        _localPort = (dynamic_cast<LocalPortQoSPolicy*>(getReader()->getQoSValueFor(QoSPolicyNames::LocalPort)))->getValue();

        _remoteAddress = connection->getAddress();
        _remotePort = connection->getPort();

        socket.setOutputGate(_udpOut);

        connect();

    } else{
        throw cRuntimeError("No AVB Connection information available"); // TODO Shouldn't rather be UDP instead AVB?
    }
    delete info;
}

UDPSubscriber::~UDPSubscriber() {
    // TODO Auto-generated destructor stub

}

ConnectionSpecificInformation* UDPSubscriber::getConnectionSpecificInformation() {
    CSI_UDP* connection = new CSI_UDP();
    connection->setAddress(_localAddress.c_str());
    connection->setPort(_localPort);
    return connection;
}

void UDPSubscriber::connect() {
    Enter_Method("UDPSubscriber::connect()");

    socket.setReuseAddress(true);
    socket.bind(*_localAddress.c_str() ? L3AddressResolver().resolve(_localAddress.c_str()) : L3Address(), _localPort);
    _isConnected = true;

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

void UDPSubscriber::close() {
    Enter_Method("UDPPublisher::close()");
    EV_INFO << "issuing CLOSE command\n";
    _isConnected = false;
    socket.close();
    //TODO shouldnt we clean up an delete this publisher?!
}

void UDPSubscriber::sendPacket(cPacket* pkt) {
    Enter_Method("UDPSubscriber::sendPacket()");
    int numBytes = pkt->getByteLength();
    socket.send(pkt);

    packetsSent++;
    bytesSent += numBytes;
}

void UDPSubscriber::handleTimer(cMessage* msg) {
    Enter_Method("UDPSubscriber::handleTimer()");
    delete msg;
}

void UDPSubscriber::handleMessage(cMessage* msg) {
    Enter_Method("UDPSubscriber::handleMessage()");
    if (socket.belongsToSocket(msg)) {// match message and socket
        EV << "Message: " << msg;
    } else {
        delete msg;
    }
}

void UDPSubscriber::notify(omnetpp::cMessage* notification) {
    Enter_Method("UDPSubscriber::notify()");
    if (socket.belongsToSocket(notification)) {// match message and socket
        EV << "Notification: " << notification;
    } else {
        delete notification;
    }
}


} /*end namespace soqosmw*/


