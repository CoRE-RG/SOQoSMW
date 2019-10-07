//
// c Timo Haeckel, for HAW Hamburg
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

package soqosmw.applications.subscriberapp.gateway;

import soqosmw.applications.subscriberapp.base.SubscriberAppBase;

//
// The GatewaySubscriberApp is a soqosmw service running on a gateway module.
// It is used to provide service data to a legacy bus.
//
// @author Timo Haeckel, for HAW Hamburg
//
simple GatewaySubscriberApp extends SubscriberAppBase
{
    parameters:
        @class(SOQoSMW::GatewaySubscriberApp);
        
}
