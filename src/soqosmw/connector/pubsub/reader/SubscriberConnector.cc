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

#include <connector/pubsub/reader/SubscriberConnector.h>

#include "soqosmw/endpoints/subscriber/base/SubscriberBase.h"

namespace soqosmw {

Define_Module(SubscriberConnector);

void PublisherConnector::addEndpoint(EndpointBase* endpoint) {
    if(dynamic_cast<SubscriberBase*>(endpoint)){
        //check if not already in the list, then add.
        auto it = find(_endpoints.begin(), _endpoints.end(), _endpoints);
        if (it == _endpoints.end()){
            _endpoints.push_back(subscriber);
        }
    }
}

EndpointBase* PublisherConnector::removeEndpoint(EndpointBase* endpoint) {
    //check if in the list, then remove.
    if(dynamic_cast<SubscriberBase*>(endpoint)){
        auto it = find(_endpoints.begin(), _endpoints.end(), _endpoints);
        if (it == _endpoints.end()){
            EndpointBase* temp = *it;
            _endpoints.erase(it);
            return temp;
        }
    }
    return nullptr;
}

} /*end namespace soqosmw*/
