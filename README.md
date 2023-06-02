# SOQoSMW
>**NOTE: This project has been moved to [SOA4CoRE](https://github.com/CoRE-RG/SOA4CoRE) and is no longer maintained here. Development and advancements continue in the new location.**

SOQoSMW (Service-Oriented Quality-of-Service MiddleWare) is an open-source extension for the event-based simulation of service-oriented communication in real-time Ethernet networks in the [OMNEST/OMNeT++](https://omnetpp.org/) simulation system. It is based on the [INET-Framework](https://inet.omnetpp.org/), providing internet technologies, the [CoRE4INET Framework](https://github.com/CoRE-RG/CoRE4INET), providing real-time Ethernet protocols such as AS6802, AVB and TSN, and the SignalsAndGateway framework (https://github.com/CoRE-RG/SignalsAndGateways) providing gateways to legacy bus systems.
SOQoSMW provides service-oriented middleware components, service applications and service endpoints for avb, tcp and udp. It was created by the [CoRE (Communication over Realtime Ethernet)](https://core-researchgroup.de/) at the [HAW-Hamburg (Hamburg University of Applied Sciences)](https://www.haw-hamburg.de/english.html).

<img src="/doc/images/soqosmw.png" alt="SOQoSMW Environment" width="75%">

## News
* Switch to OMNeT++ 5.5.1 and INET 3.6.6
* Continuous integration is now enabled.
* Model release including service-oriented middleware components, service applications and service endpoints for avb, tcp and udp. 


## Quick Start
1. Download OMNeT++ 5.5.1
    * [https://omnetpp.org/download/old](https://omnetpp.org/download/old)
2. Install OMNeT++
    * [https://doc.omnetpp.org/omnetpp/InstallGuide.pdf](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)
3. Get INET framework 3.6.6
    * [https://inet.omnetpp.org/Download.html](https://inet.omnetpp.org/Download.html)
4. Install CoRE plugins (optional)
    * OMNEST/OMNeT++ -> Help -> Install New Software...
    * URL `http://sim.core-rg.de/updates/`
    * Check [Abstract Network Description Language] | [CoRE Simulation Model Installer] | [Gantt Chart Timing Analyzer]
5. Get CoRE frameworks (GitHub or CoRE Simulation Model Installer)
    * GitHub: Clone frameworks and import it in OMNEST/OMNeT++
    * CoRE Simulation Model Installer: OMNEST/OMNeT++ -> Help -> Install CoRE Simulation Models...
6. Get SOQoSMW framework (GitHub)
	* GitHub: Clone framework and import it in OMNEST/OMNeT++
7. Working with the framework
    * See the documentation in [doc/](/doc)
    * Start the examples in the framework
    

## Continuous Integration

The build state of the master branch is monitored:
* Building:
<a><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SOQoSMW/SOQoSMW"></a>
* Tests:
<a><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SOQoSMW/SOQoSMW_tests"></a>

<table>
  <tr>
    <th></th>
    <th>Ubuntu 18.04</th>
    <th>Windows 10</th>
  </tr>
  <tr>
    <td>Building</td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SOQoSMW/SOQoSMW/Nodes=Ubuntu_18.04"></td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SOQoSMW/SOQoSMW/Nodes=Windows_10"></td>
  </tr>
  <tr>
    <td>Tests</td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SOQoSMW/SOQoSMW_tests/Nodes=Ubuntu_18.04"></td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SOQoSMW/SOQoSMW_tests/Nodes=Windows_10"></td>
  </tr>
</table>


## Further Information

### Installation
Please see [INSTALL](/INSTALL)

### Documentation
Please see [doc/](/doc)


## IMPORTANT
The SOQoSMW model is under continuous development: new parts are added, bugs are corrected, and so on. We cannot assert that the implementation will work fully according to the specifications. YOU ARE RESPONSIBLE YOURSELF TO MAKE SURE THAT THE MODELS YOU USE IN YOUR SIMULATIONS WORK CORRECTLY, AND YOU'RE GETTING VALID RESULTS.