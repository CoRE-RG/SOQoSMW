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

package soqosmw.applications.subscriberapp.base;

import soqosmw.applications.base.SOQoSMWApplicationBase;

//
// TODO auto-generated module
//
simple SubscriberAppBase extends SOQoSMWApplicationBase
{
    parameters:
        @class(soqosmw::SubscriberAppBase);
        @display("i=block/sink,blue");
        
        //Signal emitted when a frame is received, contains received EtherFrame
        @signal[rxPk](type=inet::EtherFrame);
        //Statistic of the amount of packets that were received by the application
        @statistic[rxPk](title="Received Packets"; source=rxPk; record=count; unit=packets);
        //Statistic of the amount of bytes that were received by the application
        @statistic[rxBytes](title="Received Bytes"; source=rxPk; unit=B; record="sum(packetBytes)","vector(packetBytes)", "histogram(packetBytes)?","floatingIntervalSumVector(packetBytes)?"; interpolationmode=none); //possible parameter e.g.: **.floatingintervalvectorrecorder-measure-interval = 20ms for floatingIntervalRecorders
        //End-to-end latency
        @statistic[rxLatency](title="End-to-end latency"; source="messageAge(rxPk)"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        //Uses encapsulated packet | Frame when nothing is encapsulated
        @statistic[rxLatencyInner](title="End-to-end latency inner"; source="messageAge(innerMessage(rxPk))"; unit=s; record=stats,histogram?,vector; interpolationmode=none);
        
        // Start time
        double startTime @unit(s) = default(0s);
        
        // ID of the AVB Stream
        int streamID = default(0);     
        
        string subscriberName = default("SubscriberService");
        
        string publisherName = default("PublisherService");
        
        string qosPolicies; //RT, WEB, STD ( " " seperated list of policies each policy with structure type::value)
	
	gates:
	    input AVBin;
}