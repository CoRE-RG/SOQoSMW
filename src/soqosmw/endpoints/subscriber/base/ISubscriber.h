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

#include <soqosmw/endpoints/base/IEndpoint.h>

namespace soqosmw {

class ISubscriber : public IEndpoint {
    friend class LocalServiceManager;
public:
    ISubscriber(std::string subscriberPath, std::string publisherPath,
            std::vector<IQoSPolicy> qosPolicies);
    virtual ~ISubscriber();

    const std::string& getPublisherPath() const {
        return _publisherPath;
    }

    void setPublisherPath(const std::string& publisherPath) {
        _publisherPath = publisherPath;
    }

private:
    std::string _publisherPath;
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_SUBSCRIBER_BASE_ISUBSCRIBER_H_ */
