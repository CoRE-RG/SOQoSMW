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

#include <soqosmw/applications/publisherapp/base/PublisherAppBase.h>
#include <soqosmw/qospolicy/base/QoSPolicyFactory.h>
#include <soqosmw/servicemanager/LocalServiceManager.h>

//CoRE4INET
#include "core4inet/utilities/ConfigFunctions.h"

//INET
#include "inet/linklayer/ethernet/Ethernet.h"

namespace soqosmw {

simsignal_t PublisherAppBase::sigPayload = registerSignal("payloadSignal");

Define_Module(PublisherAppBase);

PublisherAppBase::PublisherAppBase()
{
    this->enabled = false;
    this->payload = 0;
}

PublisherAppBase::~PublisherAppBase()
{

}


bool PublisherAppBase::isEnabled()
{
    return this->enabled;
}

size_t PublisherAppBase::getPayloadBytes(){
    handleParameterChange("payload");
    emit(sigPayload,static_cast<unsigned long>(this->payload));
    return this->payload;
}

void PublisherAppBase::initialize()
{
    SOQoSMWApplicationBase::initialize();
    handleParameterChange(nullptr);
    if (isEnabled())
    {
        scheduleAt(simTime() + par("startTime").doubleValue(), new cMessage(START_MSG_NAME));
        if (getEnvir()->isGUI())
        {
            getDisplayString().setTagArg("i2", 0, "status/asleep");
        }
    }
    else
    {
        if (getEnvir()->isGUI())
        {
            getDisplayString().setTagArg("i2", 0, "status/stop");
        }
    }
}

void PublisherAppBase::handleParameterChange(const char* parname)
{
    SOQoSMWApplicationBase::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "enabled"))
    {
        this->enabled = par("enabled").boolValue();
    }
    if (!parname || !strcmp(parname, "startTime"))
    {
        this->startTime = CoRE4INET::parameterDoubleCheckRange(par("startTime"), 0, SIMTIME_MAX.dbl());
    }
    if (!parname || !strcmp(parname, "payload"))
    {
        this->payload = CoRE4INET::parameterULongCheckRange(par("payload"), 0,
                MAX_ETHERNET_DATA_BYTES);
    }
    if (!parname || !strcmp(parname, "serviceName"))
    {
        this->serviceName = par("serviceName").stdstringValue();
    }
    if (!parname || !strcmp(parname, "interval"))
    {
        this->interval = CoRE4INET::parameterDoubleCheckRange(par("interval"), 0, SIMTIME_MAX.dbl());;
    }
    if (!parname || !strcmp(parname, "messagesPerInterval"))
    {
        this->messagesPerInterval = par("messagesPerInterval");
    }
    //TODO add real QoS Policies
    qosPolicies = QoSPolicyFactory::extractPolicyFromPar(par("qosPolicies"));
}

void PublisherAppBase::handleMessage(cMessage *msg){

    if(msg->isSelfMessage() && (strcmp(msg->getName(), START_MSG_NAME) == 0)){
        //register this as new publisher app!
        _publisher = getLocalServiceManager()->createPublisher(this->serviceName, this->qosPolicies, this);

        //schedule next send event
        scheduleAt(simTime() + (this->interval / this->messagesPerInterval), new cMessage(SEND_MSG_NAME));
    } else if (msg->isSelfMessage() && (strcmp(msg->getName(), SEND_MSG_NAME) == 0)) {
        if(_publisher){
            cPacket *payloadPacket = new cPacket;
            payloadPacket->setTimestamp();
            payloadPacket->setByteLength(static_cast<int64_t>(getPayloadBytes()));

            _publisher->publish(payloadPacket);

            //schedule next send event
            scheduleAt(simTime() + (this->interval / this->messagesPerInterval), new cMessage(SEND_MSG_NAME));
        } else {
            throw cRuntimeError("No Publisher Registered for this app.");
        }
    }

}

} /* end namespace soqosmw */
