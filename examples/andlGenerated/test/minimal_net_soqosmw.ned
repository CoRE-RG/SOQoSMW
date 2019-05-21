package soqosmw.examples.andlGenerated.test;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import inet.node.ethernet.EtherLink;
import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;

network minimal_net_soqosmw
{
    parameters:
        @display("bgb=768,464,white");
        double measure_interval @unit(s) = default(1s);

    types:
        channel ETH_100MBIT extends EtherLink
        {
            datarate = 100000000bps;
            length = 10.0m;
            ber = 0.0;
            per = 0.0;
        }

    submodules:
        Infotainment: Infotainment {
            parameters:
                @display("p=563,100");
        }

        Radio: Radio {
            parameters:
                @display("p=219,321");
        }

        GatewayLicht: GatewayLicht {
            parameters:
                @display("p=285,139");
        }

        GatewaySteuerung: GatewaySteuerung {
            parameters:
                @display("p=487,250");
        }

        Scheinwerfer: CanNode {
            parameters:
                @display("p=61,118");
        }

        Scheinwerfer_2: CanNode {
            parameters:
                @display("p=96,23");
        }

        Lichtregulierung: CanNode {
            parameters:
                @display("p=626,400");
        }

        Lichtregulierung_2: CanNode {
            parameters:
                @display("p=693,306");
        }

        mainSwitch: mainSwitch {
            parameters:
                @display("p=398,202");
            gates:
                ethg[4];
        }

        Licht: CanBus {
            parameters:
                @display("p=180,100");
            gates:
                gate[3];
        }

        Steuerung: CanBus {
            parameters:
                @display("p=579,307");
            gates:
                gate[3];
        }

        configurator: IPv4NetworkConfigurator;
    connections:
        GatewayLicht.ethg[0] <--> ETH_100MBIT <--> mainSwitch.ethg[0];
        GatewaySteuerung.ethg[0] <--> ETH_100MBIT <--> mainSwitch.ethg[1];
        Infotainment.ethg <--> ETH_100MBIT <--> mainSwitch.ethg[2];
        Radio.ethg <--> ETH_100MBIT <--> mainSwitch.ethg[3];
        GatewayLicht.cang[0] <--> Licht.gate[0];
        Scheinwerfer.gate <--> Licht.gate[1];
        Scheinwerfer_2.gate <--> Licht.gate[2];
        GatewaySteuerung.cang[0] <--> Steuerung.gate[0];
        Lichtregulierung.gate <--> Steuerung.gate[1];
        Lichtregulierung_2.gate <--> Steuerung.gate[2];

}
