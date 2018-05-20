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

#ifndef SOQOSMW_ENDPOINTS_READER_READER_H_
#define SOQOSMW_ENDPOINTS_READER_READER_H_

#include <connector/base/IConnector.h>
#include <endpoints/subscriber/base/ISubscriber.h>
#include <string>
#include <vector>

namespace soqosmw {
class SubscriberAppBase;
} /* namespace soqosmw */

namespace omnetpp {
class cPacket;
} /* namespace omnetpp */

namespace soqosmw {

class SubscriptionReader : public virtual IConnector {
    //todo add friends for access...
public:
    SubscriptionReader(SOQoSMWApplicationBase* executingApplication);
    virtual ~SubscriptionReader();

    virtual omnetpp::cPacket* get();

    //insert and extract data
    virtual void put(omnetpp::cPacket* packet);

    //register/unregister subscribers to deliver data to
    void addSubscriber(ISubscriber* subscriber);
    void removeSubscriber(ISubscriber* subscriber);

private:
    /**
     * Contains pointers to the registered subscribers on this writer.
     */
    std::vector<ISubscriber*> _subscribers;

    /**
     * Name of the delivery gate to the executing Application
     */
    std::string _deliveryGate = "default";
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_READER_READER_H_ */
