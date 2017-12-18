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

#ifndef SOQOSMW_ENDPOINTS_PUBLISHER_REALTIME_AVB_AVBPUBLISHER_H_
#define SOQOSMW_ENDPOINTS_PUBLISHER_REALTIME_AVB_AVBPUBLISHER_H_

#include <endpoints/publisher/realtime/base/IRTPublisher.h>
#include <omnetpp/clistener.h>
#include <qospolicy/base/IQoSPolicy.h>
#include <string>
#include <unordered_map>

#include <core4inet/base/avb/AVBDefs.h>
#include <inet/linklayer/common/MACAddress.h>

namespace CoRE4INET {
class SRPTable;
} /* namespace CoRE4INET */

namespace soqosmw {

/**
 * @brief AVBPublisher class provides an avb protocol specific implementation of the publish subscribe pattern.
 *
 * @ingroup soqosmw/endpoints
 *
 * @author Timo Haeckel
 */
class AVBPublisher: public IRTPublisher, public virtual cListener {
public:
    /**
     * Constructor.
     * @param path from IEndpoint.
     * @param qosPolicies from IEndpoint.
     * @param executingApplication from IEndpoint.
     */
    AVBPublisher(std::string path, std::unordered_map<std::string, IQoSPolicy> qosPolicies,
            SOQoSMWApplicationBase* executingApplication);
    virtual ~AVBPublisher();

    virtual void publish(omnetpp::cPacket* payload) override;

protected:

    /**
     * Receives Stream Reservation Protocol signals
     */
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;

private:
    /**
     * sets Default values for all Attributes.
     */
    void setupDefaultAttributes();

    /**
     * Sets the SRP listeners and talkers.
     */
    void setupSRP();

private:
    /**
     * The SRP Table to register a talker and be notified about new listeners.
     */
    CoRE4INET::SRPTable *_srpTable;

    /**
     * the multicast address of the Stream.
     */
    inet::MACAddress _multicastMAC;

    /**
     * Is this publisher streaming?
     */
    bool _isStreaming;

    /**
     * The SR_CLASS of this publishers stream.
     */
    CoRE4INET::SR_CLASS _srClass;

    /**
     * Stream ID.
     */
    unsigned long _streamID;

    /**
     * Output module for AVB traffic.
     */
    cModule *_avbOutCTC;
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_PUBLISHER_REALTIME_AVB_AVBPUBLISHER_H_ */
