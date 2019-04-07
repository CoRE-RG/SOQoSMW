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

package soqosmw.examples.soqosmw_random.random_network;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import soqosmw.nodes.SOQoSMWHost;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;

//
// Small sample network with three hosts and one switch that shows how to 

// configure the TTEthernet Model. Configuration in omnetpp.ini

// - Uses 5ms Cycletime

// - 80ns Tick length
//
network random_network_rt
{
    @display("bgb=1366.4401,733.48804,white,black");
    submodules:
        MotortemperaturePublisher: SOQoSMWHost {
            @display("p=166.1125,73.637505;i=block/source;is=l");
        }

        MotoroilPublisher: SOQoSMWHost {
            @display("p=166.1125,649.03754;i=block/source;is=l");
        }

        MotortemperatureRTSubscriber: SOQoSMWHost {
            @display("p=1212.4501,649.03754;i=block/sink,#FF8080,50;is=l");
        }

        MotoroilRTSubscriber: SOQoSMWHost {
            @display("p=1212.4501,73.637505;i=block/sink,#FF8080,50;is=l");
        }

        Switch: TTEAVBEtherSwitch {
            parameters:
                @display("p=678.15,356.2;is=l");
            gates:
                ethg[4];
        }

        configurator: IPv4NetworkConfigurator {
            @display("p=429.048,218.06401");
        }
    connections:
        //
        // The example uses a simple star topology
        //
        MotortemperaturePublisher.ethg <--> Eth100M {  length = 20m; } <--> Switch.ethg[0];
        MotoroilPublisher.ethg <--> Eth100M {  length = 20m; } <--> Switch.ethg[1];

        MotortemperatureRTSubscriber.ethg <--> Eth100M {  length = 5m; } <--> Switch.ethg[2];
        MotoroilRTSubscriber.ethg <--> Eth100M {  length = 5m; } <--> Switch.ethg[3];
}
