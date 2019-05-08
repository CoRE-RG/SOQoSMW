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
#include <connector/pubsub/writer/PublisherWriter.h>
#include <endpoints/publisher/base/IPublisher.h>
#include <endpoints/publisher/realtime/avb/AVBPublisher.h>
#include <messages/QoSNegotiationProtocol/ConnectionSpecificInformation_m.h>
#include <omnetpp/cexception.h>
#include <omnetpp/checkandcast.h>
#include <omnetpp/clog.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cpacket.h>
#include <qospolicy/base/qospolicy.h>
#include <cstdio>
#include <iostream>
#include <list>

#include <core4inet/base/NotifierConsts.h>
#include <core4inet/linklayer/ethernet/avb/AVBFrame_m.h>
#include <core4inet/services/avb/SRP/SRPTable.h>
#include <inet/linklayer/ethernet/Ethernet.h>

using namespace std;
using namespace omnetpp;
using namespace CoRE4INET;

namespace soqosmw {

AVBPublisher::AVBPublisher(string path, PublisherWriter* writer) :
        IRTPublisher(path, writer) {

    setupDefaultAttributes();

    setupSRP();

}

void AVBPublisher::setupDefaultAttributes() {
    _srpTable = check_and_cast<SRPTable *>(
            getWriter()->getExecutingApplication()->getParentModule()->getSubmodule("srpTable"));
    _multicastMAC = inet::MACAddress::generateAutoAddress();
    _multicastMAC.setAddressByte(0, (_multicastMAC.getAddressByte(1) | 0x01));
    _isStreaming = false;
    _streamID = (dynamic_cast<StreamIDQoSPolicy*>(getWriter()->getQoSValueFor(QoSPolicyNames::StreamID)))->getValue();
    _avbOutCTC =
            getWriter()->getExecutingApplication()->getParentModule()->getSubmodule(
                    "avbCTC");
}

ConnectionSpecificInformation* AVBPublisher::getConnectionSpecificInformation() {
    CSI_AVB* connection = new CSI_AVB();
    connection->setStreamID(_streamID);
    connection->setVlanID(_vlanID);

    return connection;
}

void AVBPublisher::setupSRP() {
    if (_srpTable) {
        //get parameters.
        auto srClass = dynamic_cast<SRClassQoSPolicy*>(getWriter()->getQoSValueFor(QoSPolicyNames::SRClass))->getValue();
        auto framesize = (dynamic_cast<FramesizeQoSPolicy*>(getWriter()->getQoSValueFor(QoSPolicyNames::Framesize)))->getValue();
        auto intervalFrames = (dynamic_cast<IntervalFramesQoSPolicy*>(getWriter()->getQoSValueFor(QoSPolicyNames::IntervalFrames)))->getValue();
        _vlanID = 7;

        EV_INFO << "Register Talker in node" << std::endl;
        _srpTable->subscribe(NF_AVB_LISTENER_REGISTERED, this);
        _srpTable->subscribe(NF_AVB_LISTENER_UNREGISTERED, this);
        _srpTable->subscribe(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, this);
        _srpTable->updateTalkerWithStreamId(_streamID, getWriter()->getExecutingApplication(),
                _multicastMAC, srClass, framesize, intervalFrames, _vlanID);
        EV_INFO << _endpointPath << ": Registered AVBTalker with streamID " << _streamID << endl;
    } else {
        throw cRuntimeError("srpTable module required for stream reservation");
    }
}

AVBPublisher::~AVBPublisher() {
    // TODO Auto-generated destructor stub
}

void AVBPublisher::publish(cPacket* payload) {
    if (_isStreaming) {
        char frameName[10];
        sprintf(frameName, "Stream %lu", _streamID);
        AVBFrame *outFrame = new AVBFrame(frameName);
        outFrame->setTimestamp();
        outFrame->setStreamID(_streamID);
        outFrame->setDest(_multicastMAC);
        outFrame->setVID(_vlanID);

        outFrame->encapsulate(payload);
        //Padding
        if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
            outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
        }
        getWriter()->getExecutingApplication()->sendDirect(outFrame, _avbOutCTC->gate("in"));
    } else {
        delete payload;
    }
}

void AVBPublisher::receiveSignal(__attribute__((unused))   cComponent *src,
        simsignal_t id, cObject *obj, __attribute__((unused))   cObject *details) {
    if (id == NF_AVB_LISTENER_REGISTERED)
    {
        SRPTable::ListenerEntry *lentry = dynamic_cast<SRPTable::ListenerEntry*>(obj);

        //If talker for the desired stream, register Listener
        if (lentry && lentry->streamId == _streamID && lentry->vlan_id == _vlanID)
        {
            EV_INFO << _endpointPath << ": Listener for stream " << lentry->streamId << " registered!" << std::endl;

            _isStreaming = true;
        }
    }
    else if (id == NF_AVB_LISTENER_REGISTRATION_TIMEOUT || id == NF_AVB_LISTENER_UNREGISTERED)
    {
        SRPTable::ListenerEntry *lentry = dynamic_cast<SRPTable::ListenerEntry*>(obj);

        //If talker for the desired stream, unregister Listener
        if (lentry && lentry->streamId == _streamID && lentry->vlan_id == _vlanID)
        {
            EV_INFO << _endpointPath << ": Listener Removed at stream " << _streamID << endl;
            //check whether there are listeners left
            if (_srpTable->getListenersForStreamId(_streamID, _vlanID).size() == 0)
            {
                EV_DEBUG << _endpointPath << ": No more Listeners Registered for " << _streamID << "!" << std::endl;
                _isStreaming = false;
            }
        }
    }
}

}
/*end namespace soqosmw*/

