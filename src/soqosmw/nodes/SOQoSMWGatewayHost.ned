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

import signalsandgateways.gateway.GatewayBase;
import signalsandgateways.applications.can.CanGatewayNode;

module SOQoSMWGatewayHost extends SOQoSMWHost
{
    parameters:
        
        //Number of CAN bus ports
        int countOfCanBusses = default(1);
        //Number of Ethernet ports
        int countOfEthernetPorts = default(1);
    
    gates:
        //bus connection
        inout cang[countOfCanBusses];
    
     submodules:
        //bus module
        can[countOfCanBusses]: CanGatewayNode {
            @display("p=369,100,c,130");
        }
        //gateway module
        gateway: GatewayBase {
            @display("p=224,100");
            numPorts = countOfCanBusses + countOfEthernetPorts;
        }
        
    connections:
        for i=0..countOfCanBusses-1 {
        	can[i].upperLayerOut --> gateway.lowerLayerIn++;
        	can[i].upperLayerIn <-- gateway.lowerLayerOut++;
       		can[i].gate <--> cang[i];
        }
    	for i=0..numServices-1 {
            services[i].upperLayerOut --> gateway.lowerLayerIn++;
            services[i].upperLayerIn <-- gateway.lowerLayerOut++;
        }
    	
    
}