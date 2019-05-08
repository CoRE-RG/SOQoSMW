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

#ifndef SOQOSMW_ENDPOINTS_PUBLISHER_REALTIME_BASE_IRTPUBLISHER_H_
#define SOQOSMW_ENDPOINTS_PUBLISHER_REALTIME_BASE_IRTPUBLISHER_H_

#include <endpoints/publisher/base/IPublisher.h>
#include <qospolicy/base/qospolicy.h>
#include <string>
#include <unordered_map>

namespace soqosmw {

/**
 * @brief RTPublisher interfaces. Base class for all publishers with realtime Requirements.
 *
 * @ingroup soqosmw/endpoints
 *
 * @author Timo Haeckel
 */
class IRTPublisher: public IPublisher {
public:
    /**
     * Constructor.
     * @param path from IEndpoint.
     * @param qosPolicies from IEndpoint.
     * @param executingApplication from IEndpoint.
     */
    IRTPublisher(std::string path, PublisherWriter* writer);
    virtual ~IRTPublisher();

};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_PUBLISHER_REALTIME_BASE_IRTPUBLISHER_H_ */
