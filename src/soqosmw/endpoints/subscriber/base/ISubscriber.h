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
#include <vector>
#include <soqosmw/qospolicy/base/IQoSPolicy.h>

namespace soqosmw {

class ISubscriber : public IEndpoint {
public:
    ISubscriber(std::string path, std::vector<IQoSPolicy> qosPolicies);
    virtual ~ISubscriber();

    const std::vector<IQoSPolicy>& getQos() const {
        return _qos;
    }

    void setQos(const std::vector<IQoSPolicy>& qos) {
        _qos = qos;
    }

private:
    std::vector<IQoSPolicy> _qos;
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_SUBSCRIBER_BASE_ISUBSCRIBER_H_ */
