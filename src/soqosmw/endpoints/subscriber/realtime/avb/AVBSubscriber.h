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

#ifndef SOQOSMW_ENDPOINTS_SUBSCRIBER_REALTIME_AVB_AVBSUBSCRIBER_H_
#define SOQOSMW_ENDPOINTS_SUBSCRIBER_REALTIME_AVB_AVBSUBSCRIBER_H_

#include <endpoints/subscriber/realtime/base/IRTSubscriber.h>
#include <omnetpp/clistener.h>
#include <omnetpp/simtime_t.h>
#include <cstdint>
#include <string>

namespace soqosmw {
class ConnectionSpecificInformation;
} /* namespace soqosmw */

namespace CoRE4INET {
class SRPTable;
} /* namespace CoRE4INET */

namespace soqosmw {

class AVBSubscriber: public IRTSubscriber, public virtual omnetpp::cListener{
public:
    AVBSubscriber(std::string publisherPath, SubscriptionReader* reader, ConnectionSpecificInformation* info);
    virtual ~AVBSubscriber();

protected:

    /**
     * Receives Stream Reservation Protocol signals
     */
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;

private:

    /**
     * Stream update interval.
     */
    simtime_t _updateInterval;

    /**
     * Retry interval if registration fails.
     */
    simtime_t _retryInterval;

    /**
     * Stream ID.
     */
    unsigned long _streamID;

    uint16_t _vlanID;

};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_SUBSCRIBER_REALTIME_AVB_AVBSUBSCRIBER_H_ */
