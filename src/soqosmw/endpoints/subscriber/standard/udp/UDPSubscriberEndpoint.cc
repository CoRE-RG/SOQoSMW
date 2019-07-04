//
// c Timo Haeckel, for HAW Hamburg
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

#include "UDPSubscriberEndpoint.h"

#include "soqosmw/applications/base/SOQoSMWApplicationBase.h"

//INET
#include <inet/networklayer/common/L3AddressResolver.h>

using namespace inet;

namespace soqosmw {

Define_Module(UDPSubscriberEndpoint);

ConnectionSpecificInformation* UDPSubscriberEndpoint::getConnectionSpecificInformation() {
    CSI_UDP* connection = new CSI_UDP();
    connection->setAddress(_localAddress.c_str());
    connection->setPort(_localPort);
    return connection;
}

void UDPSubscriberEndpoint::initializeTransportConnection() {
    // get owning app
    SOQoSMWApplicationBase* app = _connector->getApplications()[0];
    if(!app){
        throw cRuntimeError("Owning application not found in init of publisher.");
    }

    // find UDP module and add another gate.
    cModule* udp = app->getParentModule()->getSubmodule("udp");
    if(!udp){
        throw cRuntimeError("udp module required for udp subscriber but not found");
    }
    // create new gates
    udp->setGateSize("appIn", udp->gateSize("appIn")+1);
    udp->setGateSize("appOut", udp->gateSize("appOut")+1);
    // connect to transport gates
    this->gate(TRANSPORT_OUT_GATE_NAME)->connectTo(udp->gate("appIn", udp->gateSize("appIn")-1));
    this->gate(TRANSPORT_IN_GATE_NAME)->connectTo(udp->gate("appOut", udp->gateSize("appOut")-1));

    // update server socket and connect
    _socket.setOutputGate(gate("TRANSPORT_OUT_GATE_NAME"));
    _socket.setReuseAddress(true);
    _socket.bind(_localAddress.c_str() ? L3AddressResolver().resolve(_localAddress.c_str()) : L3Address(), _localPort);
}

void UDPSubscriberEndpoint::handleParameterChange(const char* parname) {
    if (!parname || !strcmp(parname, "localAddress"))
    {
        _localAddress = par("localAddress").stdstringValue();
    }
    if (!parname || !strcmp(parname, "localPort"))
    {
        _localPort = par("localPort");
    }
}

} /*end namespace soqosmw*/
