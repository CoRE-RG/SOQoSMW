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

package soqosmw.discovery.static;

import soqosmw.discovery.base.IServiceDiscovery;

//
// TODO auto-generated module
//
simple StaticServiceDiscovery like IServiceDiscovery
{
    parameters:
        @class(soqosmw::StaticServiceDiscovery);
        //this parameter holds the information of all services in the network,
        //so each node knows where the services are located.
        //Style:
        //<service name="servicename" address="ip or node (if autoconfig)">
        //</service>
        xml services = default(xmldoc("services.xml"));
}
