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

package soqosmw.examples.soqosmw_gatewaypubsub_some.gateway_net;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import soqosmw.nodes.SOQoSMWHost;
import soqosmw.nodes.SOQoSMWGatewayHost;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;


import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network gateway_net
{
    @display("bgb=703,293,white");
    submodules:
        //CAN
        Fahrwerk: CanBus {
            @display("i=block/network;p=156,144;is=l");
        }
        Reifen[3]: CanNode {

            @display("p=89,86;is=l");
        }
        Fahrdynamik: CanBus {
            @display("i=block/network;p=579,144;is=l");
        }
        Controller[3]: CanNode {
            @display("p=647,86;is=l");
        }

        //GATEWAYS
        GatewayFahrwerk: SOQoSMWGatewayHost {
            @display("p=222,210;i=block/transport;is=l");
        }

        GatewayFahrdynamik: SOQoSMWGatewayHost {
            @display("p=511,210;i=block/transport;is=l");
        }

        //ETH
        InfotainmentSystem: SOQoSMWHost {
            @display("p=366,29;i=device/server");
        }

        ethswitch: TTEAVBEtherSwitch {
            parameters:
                @display("p=366,144;is=l");
            gates:
                ethg[3];
        }

		//NET
        configurator: IPv4NetworkConfigurator {
            @display("p=89,22");
        }
    connections:
        Fahrwerk.gate++ <--> Reifen[0].gate;
        Fahrwerk.gate++ <--> Reifen[1].gate;
        Fahrwerk.gate++ <--> Reifen[2].gate;
        GatewayFahrwerk.cang[0] <--> Fahrwerk.gate++;

        Fahrdynamik.gate++ <--> Controller[0].gate;
        Fahrdynamik.gate++ <--> Controller[1].gate;
        Fahrdynamik.gate++ <--> Controller[2].gate;
        GatewayFahrdynamik.cang[0] <--> Fahrdynamik.gate++;


        GatewayFahrwerk.ethg <--> Eth100M {  length = 20m; } <--> ethswitch.ethg[0];
        GatewayFahrdynamik.ethg <--> Eth100M {  length = 10m; } <--> ethswitch.ethg[1];
        InfotainmentSystem.ethg <--> Eth100M {  length = 5m; } <--> ethswitch.ethg[2];
}
