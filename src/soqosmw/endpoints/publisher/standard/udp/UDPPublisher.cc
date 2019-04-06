/*
 * UDPPublisher.cc
 *
 *  Created on: Apr 6, 2019
 *      Author: mehkir
 */

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
#include <qospolicy/base/types/IntQoSPolicy.h>
#include <qospolicy/base/types/StringQoSPolicy.h>
#include <qospolicy/std/LocalAddressQoSPolicy.h>
#include <qospolicy/std/LocalPortQoSPolicy.h>
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

    _serverSocket.setReuseAddress(true);
    _serverSocket.bind(*_localAddress.c_str() ? L3AddressResolver().resolve(_localAddress.c_str()) : L3Address(), _localPort);
    _serverSocket.setOutputGate(_udpOut);
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
    Enter_Method("TCPPublisher::handleMessage()");

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
    //shouldnt we clean up an delete this publisher?!
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
    Enter_Method("UDPPublisher::handleMessage()");
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

}// end namespace soqosmw
