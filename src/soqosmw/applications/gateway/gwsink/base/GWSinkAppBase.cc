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

#include <applications/gateway/gwsink/base/GWSinkAppBase.h>
#include <connector/pubsub/reader/SubscriptionReader.h>
#include <omnetpp/cdisplaystring.h>
#include <omnetpp/cenvir.h>
#include <omnetpp/clog.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cnamedobject.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/cpar.h>
#include <omnetpp/csimplemodule.h>
#include <omnetpp/csimulation.h>
#include <omnetpp/regmacros.h>
#include <omnetpp/simtime.h>
#include <omnetpp/simtime_t.h>
#include <omnetpp/simutil.h>
#include <qospolicy/management/QoSGroup.h>
#include <qospolicy/tcp/LocalAddressQoSPolicy.h>
#include <qospolicy/tcp/LocalPortQoSPolicy.h>
#include <servicemanager/LocalServiceManager.h>
#include <cstring>
#include <iostream>

#include <core4inet/utilities/ConfigFunctions.h>
#include <inet/linklayer/ethernet/EtherFrame_m.h>

namespace soqosmw {
using namespace std;
using namespace CoRE4INET;

#define START_MSG_NAME "Start Message"

Define_Module(GWSinkAppBase);

simsignal_t GWSinkAppBase::_rxPkSignal = registerSignal("rxPk");

GWSinkAppBase::GWSinkAppBase() {
    _reader = nullptr;
}

GWSinkAppBase::~GWSinkAppBase() {

    delete _reader;
}

void GWSinkAppBase::initialize()
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

void GWSinkAppBase::handleMessage(cMessage *msg)
{
    SOQoSMWApplicationBase::handleMessage(msg);
    if(msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0)){
        setQoS();
        //create a subscriber
        _reader = getLocalServiceManager()->createSubscriber(this->_subscriberName, this->_publisherName, this->_qosPolicies, this);

        //TODO set the gate at the reader to get all messages

        delete msg;
    }else {
        EV_DEBUG << "Subscriber " << _subscriberName << " received a message."  << endl;


        if(msg->arrivedOn("std_tcpIn")){
            //send(msg, gate("std_tcpIn")->getNextGate());

            _reader->notify(msg);

        }else if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(msg))
        {

            send(msg, "upperLayerOut");

            emit(_rxPkSignal, frame);
        } else {
            delete msg;
        }

    }
}

void GWSinkAppBase::notify(cPacket* msg) {
    Enter_Method("GWSinkAppBase::notify()");
    EV_DEBUG << "Subscriber " << _subscriberName << " received a message."  << endl;

    if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(msg))
    {
        emit(_rxPkSignal, frame);
    }
    send(msg, "upperLayerOut");
}

void GWSinkAppBase::setQoS() {
    _qosPolicies[QoSPolicyNames::QoSGroup] = _qosGroup;
    _qosPolicies[QoSPolicyNames::LocalAddress] = new LocalAddressQoSPolicy(getLocalAddress());
    _qosPolicies[QoSPolicyNames::LocalPort] = new LocalPortQoSPolicy(getTcpPort());
}

void GWSinkAppBase::handleParameterChange(const char* parname)
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
        } else if(group == "STD"){
            _qosGroup = new QoSGroup(QoSGroup::STD);
        } else if(group == "RT"){
            _qosGroup = new QoSGroup(QoSGroup::RT);
        }

    }




}

}/* end namespace soqosmw */
