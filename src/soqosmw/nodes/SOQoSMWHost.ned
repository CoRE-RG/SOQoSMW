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

import core4inet.nodes.inet.RTIPHost;

import soqosmw.qosmanagement.negotiation.QoSNegotiationProtocol;
import soqosmw.discovery.base.IServiceDiscovery;
import soqosmw.servicemanager.LocalServiceManager;
import soqosmw.applications.base.ISOQoSMWApplication;

module SOQoSMWHost extends RTIPHost
{
    parameters:
    	hasUdp = true; //needed for qosnp
    	int numServices = default(0);
    	string localAddress = default("");
    	*.localAddress = localAddress;
    	
    submodules:
        
        services [numServices] : <> like ISOQoSMWApplication {
            
        }
        
        qosnp: QoSNegotiationProtocol {
            @display("p=344,45");
        }

        lsm: LocalServiceManager {

            @display("p=276,45");
        }

        sd: <default("StaticServiceDiscovery")> like IServiceDiscovery {

            @display("p=213,45");
        }
        
    connections allowunconnected:

        qosnp.udpOut --> udp.appIn++;
        qosnp.udpIn <-- udp.appOut++;

}