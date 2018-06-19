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

#ifndef SOQOSMW_FACTORY_SERVICEENDPOINTFACTORY_H_
#define SOQOSMW_FACTORY_SERVICEENDPOINTFACTORY_H_

#include <messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.h>
#include <string>

namespace soqosmw {
class ConnectionSpecificInformation;
class IPublisher;
class ISubscriber;
class PublisherWriter;
class SubscriptionReader;
} /* namespace soqosmw */

namespace soqosmw {

class ServiceEndpointFactory {
public:
    virtual ~ServiceEndpointFactory();

    static ServiceEndpointFactory& getInstance();
    IPublisher* createPublisher(std::string& publisherPath, int qos, PublisherWriter* writer);

    ISubscriber* createSubscriber(std::string& publisherPath, ConnectionSpecificInformation* csi, SubscriptionReader* reader);



private:
    /**
     * Singleton --> private constructor. Call getInstance() to get the instance.
     */
    ServiceEndpointFactory();

    ServiceEndpointFactory( const ServiceEndpointFactory& );
};

} /* end namespace  */

#endif /* SOQOSMW_FACTORY_SERVICEENDPOINTFACTORY_H_ */
