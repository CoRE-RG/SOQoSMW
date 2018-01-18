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
#include <endpoints/base/IEndpoint.h>
#include <endpoints/subscriber/realtime/avb/AVBSubscriber.h>
#include <omnetpp/cexception.h>
#include <omnetpp/checkandcast.h>
#include <qospolicy/avb/StreamIDQoSPolicy.h>
#include <qospolicy/base/types/IntQoSPolicy.h>
#include <iostream>

#include <core4inet/base/NotifierConsts.h>
#include <core4inet/services/avb/SRP/SRPTable.h>

namespace soqosmw {
using namespace std;
using namespace CoRE4INET;

#define SUBSCRIBER_MSG_RETRY "retrySubscription"
#define SUBSCRIBER_MSG_UPDATE "updateSubscription"

AVBSubscriber::AVBSubscriber(string subscriberPath, string publisherPath,
        unordered_map<string, IQoSPolicy*> qosPolicies, SOQoSMWApplicationBase* executingApplication) :
        IRTSubscriber(subscriberPath, publisherPath, qosPolicies, executingApplication) {

    setupDefaultAttributes();

    setupSRP();

}

AVBSubscriber::~AVBSubscriber() {
    // TODO Auto-generated destructor stub
}

void AVBSubscriber::setupDefaultAttributes() {
    _srpTable = check_and_cast<SRPTable *>(
            getExecutingApplication()->getParentModule()->getSubmodule("srpTable"));
    _streamID = (dynamic_cast<StreamIDQoSPolicy*>(_qos[QoSPolicyNames::StreamID]))->getValue();
    _vlanID = 7;
}

void AVBSubscriber::setupSRP() {
    if (_srpTable) {
        _srpTable->subscribe(NF_AVB_TALKER_REGISTERED, this);
        _srpTable->subscribe(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, this);
        _srpTable->updateListenerWithStreamId(_streamID, getExecutingApplication(), _vlanID);
    } else {
        throw cRuntimeError("srpTable module required for stream reservation");
    }
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

            signal_srpTable->updateListenerWithStreamId(tentry->streamId, getExecutingApplication(), _vlanID);

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
            if (lentry->module == getExecutingApplication())
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

