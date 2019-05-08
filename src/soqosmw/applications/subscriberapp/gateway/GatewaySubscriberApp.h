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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_GWSINKAPPBASE_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_GWSINKAPPBASE_H_

#include <applications/base/SOQoSMWApplicationBase.h>
#include <omnetpp/clistener.h>
#include <qospolicy/base/qospolicy.h>
#include <string>
#include <unordered_map>

namespace soqosmw {
class QoSGroup;
} /* namespace soqosmw */

namespace soqosmw {
class SubscriptionReader;
} /* namespace soqosmw */

namespace omnetpp {
class cMessage;
} /* namespace omnetpp */

using namespace omnetpp;

namespace soqosmw {

/**
 * TODO - Generated class
 */
class GatewaySubscriberApp: public virtual SOQoSMWApplicationBase {
private:
    /**
     * Signal that is emitted every time a frame was sent.
     */
    static simsignal_t _rxPkSignal;

    /**
     * Name of this subscriber service.
     */
    std::string _subscriberName;

    /**
     * Name of the publishing service to subscribe to.
     */
    std::string _publisherName;

    /**
     * Caches QoS Policy parameters
     */
    std::unordered_map<std::string, IQoSPolicy*> _qosPolicies;

    /**
     * Caches the start time parameter
     */
    double _startTime;

    /**
     * Reference to the soqosmw subscriberReader module.
     */
    SubscriptionReader *_reader;

    QoSGroup* _qosGroup;

    cGate* _toGateway;

protected:
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

public:
    GatewaySubscriberApp();
    virtual ~GatewaySubscriberApp();

    virtual void notify(cPacket* msg) override;

private:
    void setQoS();
};

}/* end namespace soqosmw */

#endif
