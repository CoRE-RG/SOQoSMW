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

#ifndef SOQOSMW_ENDPOINTS_PUBLISHER_BASE_IPUBLISHER_H_
#define SOQOSMW_ENDPOINTS_PUBLISHER_BASE_IPUBLISHER_H_

#include <endpoints/base/IEndpoint.h>
#include <qospolicy/base/IQoSPolicy.h>
#include <string>
#include <unordered_map>

namespace omnetpp {
class cPacket;
} /* namespace omnetpp */

namespace soqosmw {

/**
 * @brief Publisher interface. Base class for all publishing modules. Provides the behavior the application knows about.
 *
 * @ingroup soqosmw/endpoints
 *
 * @author Timo Haeckel
 */
class IPublisher: public IEndpoint {
public:
    /**
     * Constructor.
     * @param path from IEndpoint.
     * @param qosPolicies from IEndpoint.
     * @param executingApplication from IEndpoint.
     */
    IPublisher(std::string path, std::unordered_map<std::string, IQoSPolicy> qosPolicies,
            SOQoSMWApplicationBase* executingApplication);
    virtual ~IPublisher();

    /**
     * Publish a payloud to all subscribers. This needs to be implemented by all subclasses.
     * @param payload
     */
    virtual void publish(omnetpp::cPacket* payload) = 0;
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_PUBLISHER_BASE_IPUBLISHER_H_ */
