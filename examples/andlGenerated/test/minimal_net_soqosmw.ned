package soqosmw.examples.andlGenerated.test;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import inet.node.ethernet.EtherLink;
import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;

network minimal_net_soqosmw
{
    parameters:
        @display("bgb=,,white");
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
                @display("p=195,50");
        }

        Radio: Radio {
            parameters:
                @display("p=310,40");
        }

        GatewayLicht: GatewayLicht {
            parameters:
                @display("p=180,324");
        }

        GatewaySteuerung: GatewaySteuerung {
            parameters:
                @display("p=392,109");
        }

        GatewaySteuerung_2: GatewaySteuerung_2 {
            parameters:
                @display("p=292,416");
        }

        Scheinwerfer: CanNode {
            parameters:
                @display("p=29,158");
        }

        Scheinwerfer_2: CanNode {
            parameters:
                @display("p=88,39");
        }

        Lichtregulierung: CanNode {
            parameters:
                @display("p=557,141");
        }

        Lichtregulierung_2: CanNode {
            parameters:
                @display("p=576,39");
        }

        Lichtregulierung_3: CanNode {
            parameters:
                @display("p=557,454");
        }

        Lichtregulierung_4: CanNode {
            parameters:
                @display("p=584,395");
        }

        mainSwitch: mainSwitch {
            parameters:
                @display("p=271,159");
            gates:
                ethg[4];
        }

        sideSwitch: sideSwitch {
            parameters:
                @display("p=108,416");
            gates:
                ethg[2];
        }

        Licht: CanBus {
            parameters:
                @display("p=88,255");
            gates:
                gate[2];
        }

        Licht_2: CanBus {
            parameters:
                @display("p=147,174");
            gates:
                gate[2];
        }

        Steuerung: CanBus {
            parameters:
                @display("p=478,142");
            gates:
                gate[2];
        }

        Steuerung_2: CanBus {
            parameters:
                @display("p=464,62");
            gates:
                gate[2];
        }

        Steuerung_3: CanBus {
            parameters:
                @display("p=439,455");
            gates:
                gate[2];
        }

        Steuerung_4: CanBus {
            parameters:
                @display("p=478,381");
            gates:
                gate[2];
        }

        configurator: IPv4NetworkConfigurator;
    connections:
        GatewayLicht.ethg[0] <--> ETH_100MBIT <--> mainSwitch.ethg[0];
        GatewayLicht.ethg[1] <--> ETH_100MBIT <--> sideSwitch.ethg[0];
        GatewaySteuerung_2.ethg[0] <--> ETH_100MBIT <--> sideSwitch.ethg[1];
        GatewaySteuerung.ethg[0] <--> ETH_100MBIT <--> mainSwitch.ethg[1];
        Infotainment.ethg <--> ETH_100MBIT <--> mainSwitch.ethg[2];
        Radio.ethg <--> ETH_100MBIT <--> mainSwitch.ethg[3];
        GatewayLicht.cang[0] <--> Licht.gate[0];
        GatewayLicht.cang[1] <--> Licht_2.gate[0];
        Scheinwerfer.gate <--> Licht.gate[1];
        Scheinwerfer_2.gate <--> Licht_2.gate[1];
        GatewaySteuerung.cang[0] <--> Steuerung.gate[0];
        GatewaySteuerung.cang[1] <--> Steuerung_2.gate[0];
        Lichtregulierung.gate <--> Steuerung.gate[1];
        Lichtregulierung_2.gate <--> Steuerung_2.gate[1];
        GatewaySteuerung_2.cang[0] <--> Steuerung_3.gate[0];
        GatewaySteuerung_2.cang[1] <--> Steuerung_4.gate[0];
        Lichtregulierung_3.gate <--> Steuerung_3.gate[1];
        Lichtregulierung_4.gate <--> Steuerung_4.gate[1];


}
