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

#include <endpoints/publisher/realtime/avb/AVBPublisher.h>

//CoRE4INET
#include "core4inet/base/NotifierConsts.h"
#include "core4inet/base/avb/AVBDefs.h"

//INET
#include "inet/linklayer/common/MACAddress.h"

using namespace std;
using namespace omnetpp;
using namespace CoRE4INET;

namespace soqosmw {

AVBPublisher::AVBPublisher(string path,
        vector<IQoSPolicy> qosPolicies, SOQoSMWApplicationBase* owner,
        SRPTable* srpTable) :
        IRTPublisher(path, qosPolicies, owner), _srpTable(srpTable) {

    /*_multicastMAC = inet::MACAddress::generateAutoAddress();
     _multicastMAC.setAddressByte(0, (multicastMAC.getAddressByte(1) | 0x01));


     if (srpTable)
     {
     EV_INFO << "Register Talker in node" << std::endl;
     srpTable->subscribe(NF_AVB_LISTENER_REGISTERED, this);
     srpTable->subscribe(NF_AVB_LISTENER_UNREGISTERED, this);
     srpTable->subscribe(NF_AVB_LISTENER_REGISTRATION_TIMEOUT, this);
     srpTable->updateTalkerWithStreamId(45, this, _multicastMAC);
     }
     else
     {
     throw cRuntimeError("srpTable module required for stream reservation");
     }*/

}

AVBPublisher::~AVBPublisher() {
    // TODO Auto-generated destructor stub
}

void AVBPublisher::publish(cPacket* payload) {
//    int streamID = 1;
//
//
//    char frameName[10];
//    sprintf(frameName, "Stream %lu", streamID);
//    AVBFrame *outFrame = new AVBFrame(frameName);
//    outFrame->setTimestamp();
//    outFrame->setStreamID(streamID);
//    outFrame->setDest(multicastMAC);
//    outFrame->setVID(vlan_id);
//
//    cPacket *payloadPacket = new cPacket;
//    payloadPacket->setTimestamp();
//    payloadPacket->setByteLength(static_cast<int64_t>(getPayloadBytes()));
//    outFrame->encapsulate(payloadPacket);
//    //Padding
//    if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
//    {
//        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
//    }
//    sendDirect(outFrame, avbOutCTC->gate("in"));
}

} /*end namespace soqosmw*/

