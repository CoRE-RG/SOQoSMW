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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_PUBLISHERAPP_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_PUBLISHERAPP_H_

#include <applications/base/SOQoSMWApplicationBase.h>
#include <crtdefs.h>
#include <omnetpp/clistener.h>
#include <qospolicy/base/IQoSPolicy.h>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <core4inet/base/avb/AVBDefs.h>

namespace soqosmw {
class PublisherWriter;
} /* namespace soqosmw */

using namespace omnetpp;

namespace soqosmw {

#define START_MSG_NAME "Start Message"
#define SEND_MSG_NAME "Send Message"

/**
 * @brief Base class for a soqosmw publisher application.
 *
 * @ingroup soqosmw/applications
 *
 * @author Timo Haeckel
 */
class PublisherAppBase: public virtual SOQoSMWApplicationBase {
private:
    /**
     * Caches enabled parameter
     */
    bool _enabled;

    /**
     * Caches payload parameter
     */
    size_t _payload;

    /**
     * size of the ethernet frame calculated from the payload.
     */
    size_t _framesize;

    /**
     * Save the responsible writer to publish
     */
    PublisherWriter* _writer;

    /**
     * Name of the service to publish.
     */
    std::string _serviceName;

    /**
     * Caches QoS Policy parameters
     */
    std::unordered_map<std::string, IQoSPolicy*> _qosPolicies;

    /**
     * Caches the start time parameter
     */
    double _startTime;

    /**
     * Caches the interval length parameter
     */
    double _interval;

    /**
     * Caches the number of Messages per Interval parameter.
     */
    int _intervalFrames;

    /**
     * Caches the AVB SR Class.
     */
    CoRE4INET::SR_CLASS _srClass;

    /**
     * Caches the stream ID.
     */
    unsigned long _streamID;

public:
    PublisherAppBase();

    virtual ~PublisherAppBase();

    /**
     * Indicated that PublisherApp is enabled
     *
     * @return true when enabled, otherwise false
     */
    bool isEnabled();

    /**
     * Returns the number of bytes of the payload desired
     *
     * @return Size of payload in bytes
     */
    size_t getPayloadBytes();

protected:
    /**
     * Signal that is emitted each time the payload is used.
     */
    static simsignal_t sigPayload;

    /**
     * Initialization of the module. Sends activator message
     */
    virtual void initialize();

    /**
     * This method should be called from subclasses unless the module
     * resets the bag on its own.
     *
     * @param msg Parameter must be forwarded from subclass
     */
    virtual void handleMessage(cMessage *msg) override;

    /**
     * Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname) override;

private:
    void setQoS();
    void printQoS();
};

} /* end namespace soqosmw */

#endif
