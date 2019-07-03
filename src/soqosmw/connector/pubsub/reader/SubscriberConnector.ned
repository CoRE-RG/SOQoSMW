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

package soqosmw.connector.pubsub.reader;

import soqosmw.connector.base.ConnectorBase;

//
// The SubscriberConnector implements the common interface for all connctor modules @see~ConnectorBase.
// This module is created by the LocalServiceManager module (@see~LocalServiceManager)
// during runtime to connect a subscriber application to its protocol specific subscriper endpoints.
//
// @author Timo Haeckel, for HAW Hamburg
//
simple SubscriberConnector extends ConnectorBase
{
    parameters:
        @class(soqosmw::SubscriberConnector);
        // maximum number of appilcations allowed to connect to this connector.
        // -1 = infinite
        maxApplications = default(-1);
        // maximum number of endpoints allowed to connect to this connector.
        // -1 = infinite
        maxEndpoints = default(1);
        
        // Indicates if messages should be forwarded to applications.
        applicationFwdEnabled = default(true);
        // Indicates if messages should be forwarded to endpoints.
        endpointFwdEnabled = default(false);
}
