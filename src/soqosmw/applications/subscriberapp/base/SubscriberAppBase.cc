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

#include <applications/subscriberapp/base/SubscriberAppBase.h>
#include "soqosmw/connector/base/ConnectorBase.h"
#include <messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.h>
#include <qospolicy/base/qospolicy.h>
#include <servicemanager/LocalServiceManager.h>
#include <cstring>
#include <iostream>

#include <core4inet/utilities/ConfigFunctions.h>
#include <inet/linklayer/ethernet/EtherFrame_m.h>
#include <core4inet/base/avb/AVBDefs.h>

namespace soqosmw {
using namespace std;
using namespace CoRE4INET;

#define START_MSG_NAME "Start Message"

Define_Module(SubscriberAppBase);

simsignal_t SubscriberAppBase::_rxPkSignal = registerSignal("rxPk");

SubscriberAppBase::SubscriberAppBase() {
}

SubscriberAppBase::~SubscriberAppBase() {
}

void SubscriberAppBase::initialize()
{
    SOQoSMWApplicationBase::initialize();
    handleParameterChange(nullptr);

    scheduleAt(simTime() + par("startTime").doubleValue(), new cMessage(START_MSG_NAME));
    if (getEnvir()->isGUI())
    {
        getDisplayString().setTagArg("i2", 0, "status/asleep");
    }

    if (getEnvir()->isGUI())
    {
        getDisplayString().setTagArg("i2", 0, "status/hourglass");
    }
}

void SubscriberAppBase::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0)){
        setQoS();
        //create a subscriber
        _connector = _localServiceManager->registerSubscriberService(this->_subscriberName, this->_publisherName, this->_qosPolicies, this);

        //TODO set the gate at the reader to get all messages

    } else {
        EV_DEBUG << "Subscriber " << _subscriberName << " received a message."  << endl;
        //this is a subscription message so handle it.
        if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(msg))
        {
            emit(_rxPkSignal, frame);
        }
    }
    delete msg;
}

void SubscriberAppBase::setQoS() {
    _qosPolicies[QoSPolicyNames::QoSGroup] = _qosGroup;
    _qosPolicies[QoSPolicyNames::LocalAddress] = new LocalAddressQoSPolicy(_localAddress);
    std::string qosGroup = par("qosGroup").stdstringValue();
    if(qosGroup == "STD_TCP") {
            _qosPolicies[QoSPolicyNames::LocalPort] = new LocalPortQoSPolicy(_tcpPort);
    } else if(qosGroup == "STD_UDP") {
            _qosPolicies[QoSPolicyNames::LocalPort] = new LocalPortQoSPolicy(_udpPort);
    }
}

void SubscriberAppBase::handleParameterChange(const char* parname)
{
    SOQoSMWApplicationBase::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "subscriberName"))
    {
        this->_subscriberName = par("subscriberName").stdstringValue();
    }

    if (!parname || !strcmp(parname, "publisherName"))
    {
        this->_publisherName = par("publisherName").stdstringValue();
    }
    if (!parname || !strcmp(parname, "startTime"))
    {
        this->_startTime = CoRE4INET::parameterDoubleCheckRange(par("startTime"), 0, SIMTIME_MAX.dbl());
    }

    if (!parname || !strcmp(parname, "qosGroup")) {
        string group = par("qosGroup").stdstringValue();
        if(group == "WS"){
            _qosGroup = new QoSGroup(QoSGroup::WEB);
        } else if(group == "STD_TCP"){
            _qosGroup = new QoSGroup(QoSGroup::STD_TCP);
        } else if(group == "STD_UDP"){
            _qosGroup = new QoSGroup(QoSGroup::STD_UDP);
        } else if(group == "RT"){
            _qosGroup = new QoSGroup(QoSGroup::RT);
        } else {
            cRuntimeError("Not a valid connection type");
        }

    }

}

}/* end namespace soqosmw */
