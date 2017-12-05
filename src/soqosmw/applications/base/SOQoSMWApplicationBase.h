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

#include <omnetpp.h>
#include <soqosmw/servicemanager/LocalServiceManager.h>

using namespace omnetpp;

namespace soqosmw {

/**
 * @brief Base class for a SOQoSMW-Application.
 *
 * contains the module connection to the LocalServiceManager
 *
 * @ingroup Applications
 *
 * @author Timo Haeckel
 */
class SOQoSMWApplicationBase: public virtual cSimpleModule {
public:
    virtual ~SOQoSMWApplicationBase();

    LocalServiceManager* getLocalServiceManager() const {
        return _localServiceManager;
    }

protected:
    /**
     * @brief Initialization of the module.
     */
    virtual void initialize() override;

    /**
     * @brief This method should be called from subclasses unless the module
     * resets the bag on its own.
     *
     * @param msg Parameter must be forwarded from subclass
     */
    virtual void handleMessage(cMessage *msg) override;

    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     *
     * @throws cRuntimeError When buffer module and application module do not have the same parent module
     */
    virtual void handleParameterChange(const char* parname) override;

private:
    LocalServiceManager* _localServiceManager;
};

} /* end namespace soqosmw */

#endif
