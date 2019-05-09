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

package soqosmw.examples.paper.cross;


import soqosmw.nodes.SOQoSMWHost;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import core4inet.nodes.inet.RTIPHost;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;

import signalsandgateways.BusEthernetGateway;

import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network cross
{
    @display("bgb=1044.5549,332.41498,white");
    types:
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = 200ns;
        }
    submodules:
        //CAN
        Fahrwerk: CanBus {
            @display("i=block/network;p=169.31999,217.87498;is=l");
        }
        Reifen[3]: CanNode {

            @display("p=70.965,216.62999;is=l");
        }
        Fahrdynamik: CanBus {
            @display("i=block/network;p=825.435,217.87498;is=l");
        }
        Controller[3]: CanNode {
            @display("p=953.67,216.62999;is=l");
        }

        //GATEWAYS
        GatewaySource: BusEthernetGateway {
            @display("p=280.125,217.87498;i=block/source;is=l");
        }

        GatewaySink: BusEthernetGateway {
            @display("p=702.18,217.87498;i=block/sink,#FF8080;is=l");
        }

        //ETH
        InfotainmentSystem: SOQoSMWHost {
            @display("p=549.045,75.945;i=device/server");
        }

        Switch1: TTEAVBEtherSwitch {
            parameters:
                @display("p=409.60498,217.87498;is=l");
            gates:
                ethg[3];
        }
        Switch2: TTEAVBEtherSwitch {
            parameters:
                @display("p=565.23,217.87498;is=l");
            gates:
                ethg[4];
        }

        //CROSS
        Camera: RTIPHost {
            @display("p=334.905,105.825");
        }
        SensorFusion: RTIPHost {
            @display("p=702.18,87.149994");
        }


		//NET
        configurator: IPv4NetworkConfigurator {
            @display("p=89,22");
        }
    connections:
        Fahrwerk.gate++ <--> Reifen[0].gate;
        Fahrwerk.gate++ <--> Reifen[1].gate;
        Fahrwerk.gate++ <--> Reifen[2].gate;
        GatewaySource.cang[0] <--> Fahrwerk.gate++;

        Fahrdynamik.gate++ <--> Controller[0].gate;
        Fahrdynamik.gate++ <--> Controller[1].gate;
        Fahrdynamik.gate++ <--> Controller[2].gate;
        GatewaySink.cang[0] <--> Fahrdynamik.gate++;


        Switch1.ethg[0] <--> cable <--> GatewaySource.ethg[0];
        Switch1.ethg[1] <--> cable <--> Camera.ethg;

        Switch1.ethg[2] <--> cable <--> Switch2.ethg[3];

        Switch2.ethg[0] <--> cable <--> GatewaySink.ethg[0];
        Switch2.ethg[1] <--> cable <--> SensorFusion.ethg;
        Switch2.ethg[2] <--> cable <--> InfotainmentSystem.ethg;
}
