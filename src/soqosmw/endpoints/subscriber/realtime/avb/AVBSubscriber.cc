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
#include <endpoints/subscriber/realtime/avb/AVBSubscriber.h>
#include <messages/QoSNegotiationProtocol/ConnectionSpecificInformation_m.h>
#include <omnetpp/cexception.h>
#include <omnetpp/checkandcast.h>
#include <omnetpp/clog.h>
#include <iostream>

#include <core4inet/base/NotifierConsts.h>
#include <core4inet/services/avb/SRP/SRPTable.h>

namespace soqosmw {
using namespace std;
using namespace CoRE4INET;

#define SUBSCRIBER_MSG_RETRY "retrySubscription"
#define SUBSCRIBER_MSG_UPDATE "updateSubscription"

AVBSubscriber::AVBSubscriber(string publisherPath, SubscriptionReader* reader, ConnectionSpecificInformation* info) :
        IRTSubscriber(publisherPath, reader) {

    if(info->getConnectionType() == ConnectionType::ct_avb){
        CSI_AVB* connection = dynamic_cast<CSI_AVB*>(info);
        SRPTable* srpTable = check_and_cast<SRPTable *>(
                getReader()->getExecutingApplication()->getParentModule()->getSubmodule("srpTable"));
        _streamID = connection->getStreamID();
        _vlanID = connection->getVlanID();

        if (srpTable) {
                srpTable->subscribe(NF_AVB_TALKER_REGISTERED, this);
                srpTable->subscribe(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, this);
                srpTable->updateListenerWithStreamId(_streamID, getReader()->getExecutingApplication(), _vlanID);
            } else {
                throw cRuntimeError("srpTable module required for stream reservation");
            }
    } else{
        throw cRuntimeError("No AVB Connection information available");
    }
    delete info;
}

AVBSubscriber::~AVBSubscriber() {
    // TODO Auto-generated destructor stub
}

void AVBSubscriber::receiveSignal(cComponent *src, simsignal_t id, cObject *obj,
        __attribute__((unused)) cObject *details)
{

    if (id == NF_AVB_TALKER_REGISTERED)
    {
        SRPTable::TalkerEntry *tentry = check_and_cast<SRPTable::TalkerEntry*>(obj);

        //If talker for the desired stream, register Listener
        if (tentry->streamId == _streamID && tentry->vlan_id == _vlanID)
        {
            SRPTable *signal_srpTable = check_and_cast<SRPTable *>(src);

            signal_srpTable->updateListenerWithStreamId(tentry->streamId, getReader()->getExecutingApplication(), _vlanID);

            EV_INFO << _endpointPath << ": Registered AVBListener for streamID " << _streamID << endl;
//            if (_updateInterval != 0)
//            {
//                scheduleAt(simTime() + _updateInterval, new cMessage(SUBSCRIBER_MSG_UPDATE));
//            }
        }
    }
    else if (id == NF_AVB_LISTENER_REGISTRATION_TIMEOUT)
    {
        SRPTable::ListenerEntry *lentry = check_and_cast<SRPTable::ListenerEntry*>(obj);
        if (lentry->streamId == _streamID && lentry->vlan_id == _vlanID)
        {
            if (lentry->module == getReader()->getExecutingApplication())
            {

                EV_ERROR << _endpointPath << ": Registration failed for AVBListener streamID " << _streamID << endl;
//                if (_retryInterval != 0)
//                {
//                    scheduleAt(simTime() + _retryInterval, new cMessage(SUBSCRIBER_MSG_RETRY));
//                }
            }
        }
    }
}

} /*end namespace soqosmw*/

