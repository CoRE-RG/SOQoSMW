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

#ifndef __SOQOSMW_CONNECTORBASE_H_
#define __SOQOSMW_CONNECTORBASE_H_

#include <omnetpp.h>

namespace soqosmw {
class SOQoSMWApplicationBase;
class EndpointBase;
} /* namespace soqosmw */

using namespace omnetpp;

namespace soqosmw {

/**
 * The ConnectorBase provides a common interface for all connctor modules.
 * Those modules are created by the LocalServiceManager module (@see~LocalServiceManager)
 * during runtime to connect a service application to its protocol specific service endpoints.
 *
 * @author Timo Haeckel, for HAW Hamburg
 */
class ConnectorBase : public cSimpleModule
{
public:
    /**
     * Adds the endpoint to this connector only if the endpoint is not already in the list.
     * It allows the transmission of messages to the executing application.
     * Implementing ConnectorClasses need to check for the correct type of endpoint.
     *
     * @param endpoint    the endpoint to add.
     */
    void addEndpoint(EndpointBase* endpoint) = 0;

    /**
     * Removes the endpoint from this connector if present.
     * Implementing ConnectorClasses need to check for the correct type of endpoint.
     *
     * @param endpoint    the endpoint to remove.
     * @return  the endpoint if it was removed (pointer no longer managed by this module)
     *          nullptr if the endpoint is not registered.
     */
    EndpointBase* removeEndpoint(EndpointBase* endpoint) = 0;

    //getter + setter
    const std::vector<EndpointBase*>& getEndpoints() const;
    const SOQoSMWApplicationBase* getExecutingApplication() const;
    void setExecutingApplication(
            const SOQoSMWApplicationBase* executingApplication);
    bool isEnabled() const;
    void setEnabled(bool enabled = false);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    /**
     * Caches if forwarding is enabled.
     */
    bool enabled = false;

    /**
     * Contains pointers to the registered subscribers on this writer.
     */
    std::vector<EndpointBase*> _endpoints;

    /**
     * Owner Module of this Endpoint.
     */
    SOQoSMWApplicationBase* _executingApplication;
};

} /*end namespace soqosmw*/

#endif
