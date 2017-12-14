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

#include <base/EndpointDescription.h>
#include <messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/cpar.h>
#include <omnetpp/csimulation.h>
#include <omnetpp/regmacros.h>
#include <qosmanagement/negotiation/broker/QoSBroker.h>
#include <qosmanagement/negotiation/QoSNegotiationProtocol.h>
#include <string>
#include <iostream>

#include <inet/networklayer/common/L3AddressResolver.h>


namespace soqosmw {
using namespace std;
using namespace inet;

Define_Module(QoSNegotiationProtocol);

QoSNegotiationProtocol::QoSNegotiationProtocol() {
    _broker = nullptr;
}

QoSNegotiationProtocol::~QoSNegotiationProtocol() {
    socketClose();
    delete _broker;
}

void QoSNegotiationProtocol::initialize(int stage) {
    if(stage == MY_INIT_STAGE) {
        cout << "QoSNegotiationProtocol::initialize ";
        handleParameterChange(nullptr);
        if (_isClient) {
            //Client Starts the Operation so create selfmsg for startsignal
            cMessage* startSignal = new cMessage("startSignal");

            scheduleAt(simTime(), startSignal);
            cout << "is Client so setup start message.";
        } else {
            //nothing to do
        }
        if(!isSocketBound()){
            socketSetup();
        }


        cout << endl;
    }
}

void QoSNegotiationProtocol::handleMessage(cMessage *msg) {
    cout << "QoSNegotiationProtocol:" << " --> message received";

    if(msg->isSelfMessage()) {
        //create a new client broker and start negotiation
        if(_broker == 0){
            //create new broker
            EndpointDescription remote(_destPath, _destAddress, _protocolPort);
            EndpointDescription local(_localPath, _localAddress, _protocolPort);
            _broker = new QoSBroker(&_socket, local, remote, true);
        }
        _broker->handleStartSignal();
    } else if (auto as_envelope = dynamic_cast<soqosmw::Envelope*>(msg)) {
        //is in soqosmw::Envelope --> check other types
        if (auto as_negotiation = dynamic_cast<soqosmw::QoSNegotiationProtocolMsg*>(as_envelope)) {
            //TODO check if it is a request --> create new broker else forward to all brokers to handle it.
            //if broker not set create a new one
            if(_broker == 0){

                //create new broker
                _broker = new QoSBroker(&_socket, as_negotiation->getReceiver(), as_negotiation->getSender(), false);
            }

            //let broker handle the message.
            _broker->handleMessage(as_negotiation->dup());

        } else {
            cout << " --> not of type soqosmw::QoSNegotiationProtocolMsg --> ignore it!";
        }
    } else {
        cout << " --> not in soqosmw::Envelope --> ignore it!";
    }

    //cleanup
    cout << endl;
    delete msg;
}

void QoSNegotiationProtocol::handleParameterChange(const char* parname) {

    //read UDP Common Parameters
    if(!parname || !strcmp(parname, "protocolPort")){
        _protocolPort = par("protocolPort");
    }
    if(!parname || !strcmp(parname, "destAddress")){
        const char* destAddr = par("destAddress");
        _destAddress = L3AddressResolver().resolve(destAddr);
    }
    if(!parname || !strcmp(parname, "destPath")){
        _destPath = par("destPath").stdstringValue();
    }
    if(!parname || !strcmp(parname, "localAddress")){
        const char* localAddr = par("localAddress");
        _localAddress = L3AddressResolver().resolve(localAddr);
    }
    if(!parname || !strcmp(parname, "localPath")){
        _localPath = par("localPath").stdstringValue();
    }
    //update parameters if nullptr or parameter specified.
    if (!parname || !strcmp(parname, "isClient")) { //is this a client?
        _isClient = this->par("isClient").boolValue();
    }

}

void QoSNegotiationProtocol::fillEnvelope(soqosmw::Envelope* envelope){
    //set receiver
    EndpointDescription receiver;
    receiver.setNetworkAddr(_destAddress);
    receiver.setNetworkPort(_protocolPort);
    envelope->setReceiver(receiver);
    //set sender
    EndpointDescription sender;
    sender.setNetworkAddr(_localAddress);
    sender.setNetworkPort(_protocolPort);
    envelope->setSender(sender);
}

void QoSNegotiationProtocol::sendMessage(cPacket* payload_packet) {
    if(!isSocketBound()){
        socketSetup();
    }
    //payload_packet->setByteLength(sizeof(*payload_packet));
    _socket.sendTo(payload_packet, _destAddress, _protocolPort);
}

void QoSNegotiationProtocol::socketSetup() {
    _socket.setOutputGate(gate("udpOut"));
    _socket.bind(_localAddress, _protocolPort);
    _socketBound = true;
}

bool QoSNegotiationProtocol::isSocketBound(){
    return _socketBound;
}

void QoSNegotiationProtocol::socketClose() {
    _socket.close();
    _socketBound = false;
}

} /* namespace soqosmw */
