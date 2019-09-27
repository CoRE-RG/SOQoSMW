//
// c Timo Haeckel for HAW Hamburg
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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_GWSOURCEAPPBASE_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_GWSOURCEAPPBASE_H_

#include <applications/publisherapp/base/PublisherAppBase.h>
#include <vector>

using namespace omnetpp;

namespace soqosmw {

#define NO_OF_INIT_STAGES 15

/**
 * @brief A soqosmw gateway publisher application.
 *
 * @ingroup soqosmw/applications
 *
 * @author Timo Haeckel for HAW Hamburg
 */
class GatewayPublisherApp: public virtual PublisherAppBase {
private:

    /**
     * Caches the canIDs handled in this gateway app
     */
    std::vector<int> _canIds;

public:
    GatewayPublisherApp();

    virtual ~GatewayPublisherApp();

protected:

    /**
     * Initialization of the module. Sends activator message
     */
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override {
        return NO_OF_INIT_STAGES;
    }

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

    virtual void scheduleNextMessage() override;

private:
};

} /* end namespace soqosmw */

#endif
