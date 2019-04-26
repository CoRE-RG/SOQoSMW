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

package soqosmw.examples.soqosmw_myGateways.minimal_net;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import soqosmw.nodes.SOQoSMWHost;
import soqosmw.nodes.SOQoSMWGatewayHost;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;


import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;

network minimal_net
{
    submodules:
        //CAN
        Scheinwerfer[4]: CanNode {
            @display("p=118,53");
        }
        Licht: CanBus {
            @display("i=block/network;p=118,155");
        }

        Lichtregulierung[4]: CanNode {
            @display("p=416,53");
        }
        Steuerung: CanBus {
            @display("i=block/network;p=416,155");
        }

        //GATEWAYS
        GatewayLicht: SOQoSMWGatewayHost {
            @display("i=block/transport;is=l;p=118,280");
        }

        GatewaySteuerung: SOQoSMWGatewayHost {
            @display("i=block/transport;is=l;p=416,280");
        }

        //NET
        configurator: IPv4NetworkConfigurator {
            @display("p=343,29");
        }

        //ETH
        ethswitch: TTEAVBEtherSwitch {
            @display("p=277,280");
            gates:
                ethg[2];
        }

    connections:
        Licht.gate++ <--> Scheinwerfer[0].gate;
        Licht.gate++ <--> Scheinwerfer[1].gate;
        Licht.gate++ <--> Scheinwerfer[2].gate;
        Licht.gate++ <--> Scheinwerfer[3].gate;
        Licht.gate++ <--> GatewayLicht.cang[0];

        Steuerung.gate++ <--> Lichtregulierung[0].gate;
        Steuerung.gate++ <--> Lichtregulierung[1].gate;
        Steuerung.gate++ <--> Lichtregulierung[2].gate;
        Steuerung.gate++ <--> Lichtregulierung[3].gate;
        Steuerung.gate++ <--> GatewaySteuerung.cang[0];

        GatewayLicht.ethg <--> Eth100M {  length = 10m; } <--> ethswitch.ethg[0];
        GatewaySteuerung.ethg <--> Eth100M {  length = 10m; } <--> ethswitch.ethg[1];
}
