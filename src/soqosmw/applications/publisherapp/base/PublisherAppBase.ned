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

package soqosmw.applications.publisherapp.base;

import soqosmw.applications.base.SOQoSMWApplicationBase;

//
// TODO auto-generated module
//
simple PublisherAppBase extends SOQoSMWApplicationBase
{
    parameters:
        @class(soqosmw::PublisherAppBase);
        @display("i=block/source");
        
        // PublisherApp enabled or disabled
        bool enabled = default(true);
        // Start time
        double startTime @unit(s) = default(0s);
        // Interval of new messages
        double interval @unit(s) = default(125us);
        // Number of frames per interval
        int messagesPerInterval = default(1);
        //Size of the payload of the message (size of encapsulated cPacket) that is being generated
        volatile int payload @unit(Byte) = default(46Byte);
        
        @signal[payloadSignal];
    
    	//Service Description
    	string serviceName = default("PublisherService");
    	
    	//QoS Policies
    	string qosPolicies; //RT, WEB, STD ( " " seperated list of policies each policy with structure type::value)
    
}
