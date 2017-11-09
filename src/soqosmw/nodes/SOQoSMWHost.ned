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

package soqosmw.nodes;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import soqosmw.qosmanagement.negotiation.broker.QoSBroker;

module SOQoSMWHost extends TTEAVBEtherHost
{
    
    //bgIn.destination_gates = "qos_broker.networkLayerIn";
    
    submodules:
        qos_broker : QoSBroker {
            //targetModule = "bgOut";
            //targetGate = "in";
        }
        
    connections:
        bgIn.out --> qos_broker.networkLayerIn;
        qos_broker.networkLayerOut --> bgOut.in;
}
