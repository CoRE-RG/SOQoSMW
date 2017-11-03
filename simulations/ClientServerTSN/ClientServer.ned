package soqosmw.simulations.ClientServerTSN;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import inet.node.ethernet.EtherLink;

network ClientServer
{
parameters:
     @display("bgb=,,white");
     double measure_interval @unit(s) = default(1s);

types: 
 channel ETH_100MBIT extends EtherLink
  {
	datarate = 100000000bps;
	length = 0.0m;
	ber = 0.0;
	per = 0.0;
  }

submodules:
  client: client {
    parameters: 
    }

  server: server {
    parameters: 
    }

  eth_switch: eth_switch {
    parameters: 
    gates:
      ethg[2];
  }

connections:
  client.ethg <--> ETH_100MBIT <--> eth_switch.ethg[0];
  server.ethg <--> ETH_100MBIT <--> eth_switch.ethg[1];

}