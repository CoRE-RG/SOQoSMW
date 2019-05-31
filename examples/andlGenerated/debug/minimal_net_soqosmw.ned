package soqosmw.examples.andlGenerated.debug;

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
    }

  Radio: Radio {
    parameters: 
    }

  GatewayLicht: GatewayLicht {
    parameters: 
    }

  GatewaySteuerung: GatewaySteuerung {
    parameters: 
    }

  GatewaySteuerung_2: GatewaySteuerung_2 {
    parameters: 
    }

  Scheinwerfer: CanNode {
    parameters: 
    }

  Scheinwerfer_2: CanNode {
    parameters: 
    }

  Lichtregulierung: CanNode {
    parameters: 
    }

  Lichtregulierung_2: CanNode {
    parameters: 
    }

  Lichtregulierung_3: CanNode {
    parameters: 
    }

  Lichtregulierung_4: CanNode {
    parameters: 
    }

  mainSwitch: mainSwitch {
    parameters: 
    gates:
      ethg[4];
  }

  sideSwitch: sideSwitch {
    parameters: 
    gates:
      ethg[2];
  }

  Licht: CanBus  {
    parameters: 
    gates:
        gate[2];
 }

  Licht_2: CanBus  {
    parameters: 
    gates:
        gate[2];
 }

  Steuerung: CanBus  {
    parameters: 
    gates:
        gate[2];
 }

  Steuerung_2: CanBus  {
    parameters: 
    gates:
        gate[2];
 }

  Steuerung_3: CanBus  {
    parameters: 
    gates:
        gate[2];
 }

  Steuerung_4: CanBus  {
    parameters: 
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