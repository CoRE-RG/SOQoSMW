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

#include <applications/subscriberapp/gateway/GatewaySubscriberApp.h>

#include <core4inet/utilities/ConfigFunctions.h>
#include <inet/linklayer/ethernet/EtherFrame_m.h>
#include "signalsandgateways/applications/ethernet/EthernetGatewayApplication.h"

#include "signalsandgateways/gateway/messages/GatewayAggregationMessage.h"
#include <core4inet/linklayer/ethernet/avb/AVBFrame_m.h>

namespace soqosmw {
using namespace std;
using namespace SignalsAndGateways;
using namespace CoRE4INET;

Define_Module(GatewaySubscriberApp);

GatewaySubscriberApp::GatewaySubscriberApp() {
}

GatewaySubscriberApp::~GatewaySubscriberApp() {
}

void GatewaySubscriberApp::initialize()
{
    SubscriberAppBase::initialize();
    handleParameterChange(nullptr);

    //find the gateway to deliver messages
    if(EthernetGatewayApplication* gwApp = dynamic_cast<EthernetGatewayApplication*>(this->getParentModule()->getSubmodule("gatewayApp"))) {
        _toGateway = gwApp->gate("in");
    } else {
        throw cRuntimeError("Service GWSinkAppBase can not find EthernetGatewayApplication under the name \"gatewayApp\"");
    }
}

void GatewaySubscriberApp::notify(cMessage* msg) {
    Enter_Method("GWSinkAppBase::notify()");
    EV_DEBUG << "Subscriber " << _subscriberName << " received a message."  << endl;

    // check for in gate & cast to aggregation message
    SignalsAndGateways::GatewayAggregationMessage* gwam = nullptr;

    if(AVBFrame* avbframe = dynamic_cast<AVBFrame*>(msg)){
        gwam = dynamic_cast<SignalsAndGateways::GatewayAggregationMessage*>(avbframe->decapsulate());
        delete avbframe;
    } else {
        gwam = dynamic_cast<SignalsAndGateways::GatewayAggregationMessage*>(msg);
    }

    if(gwam){

        //TODO fix emit for GatewayAggregationMessage type
//        emit(_rxPkSignal, gwam);

        //unpack can frames and forward
        sendDirect(gwam->dup(), _toGateway);
    }

    delete gwam;
}

}/* end namespace soqosmw */
