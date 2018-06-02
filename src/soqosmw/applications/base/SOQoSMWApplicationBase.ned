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

package soqosmw.applications.base;

import soqosmw.applications.base.ISOQoSMWApplication;

//
// TODO auto-generated module
//
simple SOQoSMWApplicationBase like ISOQoSMWApplication
{
    parameters:
        @class(soqosmw::SOQoSMWApplicationBase);
        string serviceManagerModule = default ("lsm");
        string appCallbackGateName = default ("appCallback");
        
        string localAddress = default("");
    	int applicationTCPPort = default(3333);
    	int applicationUDPPort = default(6666);
        
    gates:
        input appCallback;
    	
        input std_tcpIn @labels(TCPCommand/up);
        output std_tcpOut @labels(TCPCommand/down);
        input std_udpIn @labels(UDPCommand/up);
        output std_udpOut @labels(UDPCommand/down);
}
