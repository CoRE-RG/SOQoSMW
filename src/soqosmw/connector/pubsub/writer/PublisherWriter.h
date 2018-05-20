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

#ifndef SOQOSMW_ENDPOINTS_WRITER_WRITER_H_
#define SOQOSMW_ENDPOINTS_WRITER_WRITER_H_

#include <connector/base/IConnector.h>
#include <endpoints/publisher/base/IPublisher.h>
#include <qospolicy/base/IQoSPolicy.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace omnetpp {
class cPacket;
} /* namespace omnetpp */

namespace soqosmw {

class PublisherWriter :  public virtual IConnector {
    //todo add friends for access...
public:
    PublisherWriter(SOQoSMWApplicationBase* executingApplication, std::unordered_map<std::string, IQoSPolicy*> qos);
    virtual ~PublisherWriter();

    //insert data
    virtual void write(omnetpp::cPacket* packet);

    //register/unregister publishers to deliver data to
    void addPublisher(IPublisher* publisher);
    void removePublisher(IPublisher* publisher);

    IQoSPolicy* getQoSValueFor(std::string property);

private:
    /**
     * Contains pointers to the registered publishers on this writer.
     */
    std::vector<IPublisher*> _publishers;

    /**
     * QoS Policies set for this Endpoint.
     */
    std::unordered_map<std::string, IQoSPolicy*> _qos;
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_WRITER_WRITER_H_ */
