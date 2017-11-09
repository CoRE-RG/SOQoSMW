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

package soqosmw.qosmanagement.negotiation.broker;


//
// TODO auto-generated module
//
simple QoSBroker
{
    parameters:
        bool isClient = default(false);//TODO remove and create client and server apps
        string destAddress = default("auto");// destination MAC address
        
        string targetModule;
        string targetGate;
        //--> sendDirect(msg, _target); --> sendMessage()
        //holen mit cGate _target = getParentModule()->getSubmodule(this->par("targetModule"))->gate(this->par("targetGate")) --> handleParameterChange() (else throw cRuntimeError)
        
    @class(soqosmw::QoSBroker);
    gates:
        //connections to lower layer
        input networkLayerIn; //in connected via connections out needs to be specified in targetModule and Gate.
        
        //app connections
        input appIn;
        output appOut;
}
