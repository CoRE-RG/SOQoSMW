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
    	hasTcp = true; //needed for tcp based communication
    	int numServices = default(0);
    	string localAddress = default("");
    	*.localAddress = localAddress;
    	*.lsmmoduleName = "lsm";
    	*.sdmoduleName = "sd";
    	*.qosnpmoduleName = "qosnp";
    	
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
        
        for i=0..numServices-1 {
            services[i].std_tcpOut --> tcp.appIn++;
            services[i].std_tcpIn <-- tcp.appOut++;
            services[i].std_udpOut --> udp.appIn++;
            services[i].std_udpIn <-- udp.appOut++;
        }

}
