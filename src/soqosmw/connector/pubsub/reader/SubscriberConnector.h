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

#ifndef __SOQOSMW_SUBSCRIPTIONCONNECTOR_H_
#define __SOQOSMW_SUBSCRIPTIONCONNECTOR_H_

#include "soqosmw/connector/base/ConnectorBase.h"

namespace soqosmw {
class SubscriberBase;
} /* namespace soqosmw */

namespace soqosmw {

/**
 * The SubscriptionConnector implements the common interface for all connctor modules @see~ConnectorBase.
 * This module is created by the LocalServiceManager module (@see~LocalServiceManager)
 * during runtime to connect a subscriber application to its protocol specific subscriper endpoints.
 *
 * @author Timo Haeckel, for HAW Hamburg
 */
class SubscriberConnector : public ConnectorBase
{
public:
    /**
     * Adds the endpoint to this connector only if the endpoint is not already in the list.
     * It allows the transmission of messages to the executing application.
     * Implementing ConnectorClasses need to check for the correct type of endpoint.
     *
     * @param endpoint    the endpoint to add.
     */
    void addEndpoint(EndpointBase* endpoint);

    /**
     * Removes the endpoint from this connector if present.
     * Implementing ConnectorClasses need to check for the correct type of endpoint.
     *
     * @param endpoint    the endpoint to remove.
     * @return  the endpoint if it was removed (pointer no longer managed by this module)
     *          nullptr if the endpoint is not registered.
     */
    EndpointBase* removeEndpoint(EndpointBase* endpoint);
};

} /*end namespace soqosmw*/

#endif
