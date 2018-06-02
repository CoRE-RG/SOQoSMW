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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_SOQOSMWAPPLICATIONBASE_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_SOQOSMWAPPLICATIONBASE_H_

#include <omnetpp/cpacket.h>
#include <omnetpp/csimplemodule.h>
#include <string>

using namespace omnetpp;

namespace soqosmw {

/**
 * forward declaration of LocalServiceManager to let them know each other.
 */
class LocalServiceManager;

/**
 * @brief Base class for a SOQoSMW-Application.
 *
 * contains the module connection to the LocalServiceManager
 *
 * @ingroup soqosmw/applications
 *
 * @author Timo Haeckel
 */
class SOQoSMWApplicationBase: public virtual cSimpleModule {
public:
    virtual ~SOQoSMWApplicationBase();

    /**
     * This method returns the LocalServiceManager reference to interact with soqosmw services.
     * @return
     */
    LocalServiceManager* getLocalServiceManager() const {
        return _localServiceManager;
    }

    virtual void notify(cPacket* msg){
        delete msg;
    }

    const std::string& getLocalAddress() const {
        return _localAddress;
    }

    void setLocalAddress(const std::string& localAddress) {
        _localAddress = localAddress;
    }

    int getTcpPort() const {
        return _tcpPort;
    }

    void setTcpPort(int tcpPort) {
        _tcpPort = tcpPort;
    }

    int getUdpPort() const {
        return _udpPort;
    }

    void setUdpPort(int udpPort) {
        _udpPort = udpPort;
    }

protected:
    /**
     * Initialization of the module.
     */
    virtual void initialize() override;

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
     *
     * @throws cRuntimeError When needed parameters could not be found.
     */
    virtual void handleParameterChange(const char* parname) override;

private:
    /**
     * Reference to the LocalServiceManager.
     */
    LocalServiceManager* _localServiceManager;

    int _tcpPort;
    int _udpPort;
    std::string _localAddress;
};

} /* end namespace soqosmw */

#endif
