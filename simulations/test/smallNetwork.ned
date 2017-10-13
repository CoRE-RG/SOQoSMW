package hauptprojekt_timo_haeckel.simulations.test;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import inet.node.ethernet.EtherLink;
import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;

network smallNetwork
{
parameters:
     @display("bgb=,,white");
     double measure_interval @unit(s) = default(1s);

types: 
 channel ethCable1 extends EtherLink
  {
	datarate = 100000000bps;
	length = 0.0m;
	ber = 0.0;
	per = 0.0;
  } 
 channel ETH_100MBIT extends EtherLink
  {
	datarate = 100000000bps;
	length = 0.0m;
	ber = 0.0;
	per = 0.0;
  }

submodules:
  gateway1: gateway1 {
    parameters: 
    }

  gateway2: gateway2 {
    parameters: 
    }

  canNode1: CanNode {
    parameters: 
    }

  canNode2: CanNode {
    parameters: 
    }

  switch1: switch1 {
    parameters: 
    gates:
      ethg[2];
  }

  canbus1: CanBus  {
    parameters: 
    gates:
        gate[2];
 }

  canbus2: CanBus  {
    parameters: 
    gates:
        gate[2];
 }

connections:
  gateway1.ethg[0] <--> ethCable1 <--> switch1.ethg[0];
  gateway2.ethg[0] <--> ETH_100MBIT <--> switch1.ethg[1];
  gateway1.cang[0] <--> canbus1.gate[0];
  canNode1.gate <--> canbus1.gate[1];
  gateway2.cang[0] <--> canbus2.gate[0];
  canNode2.gate <--> canbus2.gate[1];

}