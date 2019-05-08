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

#ifndef SOQOSMW_ENDPOINTS_SUBSCRIBER_BASE_ISUBSCRIBER_H_
#define SOQOSMW_ENDPOINTS_SUBSCRIBER_BASE_ISUBSCRIBER_H_

#include <endpoints/base/IEndpoint.h>
#include <qospolicy/base/qospolicy.h>
#include <string>
#include <unordered_map>

namespace soqosmw {
class SubscriptionReader;
} /* namespace soqosmw */

namespace soqosmw {

/**
 * @brief Subscriber interface. Base class for all subscribers.
 *
 * @ingroup soqosmw/endpoints
 *
 * @author Timo Haeckel
 */
class ISubscriber : public IEndpoint {
public:
    /**
     * Constructor.
     * @param subscriberPath from IEndpoint.
     * @param publisherPath Path/name of the publisher.
     * @param qosPolicies from IEndpoint.
     * @param executingApplication fromIEndpoint.
     */
    ISubscriber(std::string publisherPath, SubscriptionReader* reader);
    virtual ~ISubscriber();

    const std::string& getPublisherPath() const {
        return _publisherPath;
    }

    void setPublisherPath(const std::string& publisherPath) {
        _publisherPath = publisherPath;
    }

    SubscriptionReader* getReader()  {
        return _reader;
    }

    void setReader(SubscriptionReader* reader) {
        _reader = reader;
    }

private:
    /**
     * The path/name of the publisher.
     */
    std::string _publisherPath;

    /**
     * reader for subscription
     */
   SubscriptionReader* _reader;
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_SUBSCRIBER_BASE_ISUBSCRIBER_H_ */
