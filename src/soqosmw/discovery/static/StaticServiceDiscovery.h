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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_STATICSERVICEDISCOVERY_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_STATICSERVICEDISCOVERY_H_

//SOQOSMW
#include <discovery/base/IServiceDiscovery.h>

//STD
#include <string>
#include <unordered_map>

//INET
#include <inet/networklayer/common/L3Address.h>

namespace soqosmw {

#define NO_OF_INIT_STAGES 15
#define MY_INIT_STAGE 13

/**
 * @brief This class provides a static ServiceDiscovery Module via XML.
 *
 * @ingroup soqosmw/discovery
 *
 * @author Timo Haeckel
 */
class StaticServiceDiscovery: public IServiceDiscovery {
public:
    /**
     * Find a Service in the Registry.
     * @param path The name/path of the service to find.
     * @return The network address of the node running the service.
     */
    inet::L3Address& discover(std::string path);

    /**
     * Get all registry entries as a map.
     * @return the registry.
     */
    const std::unordered_map<std::string, inet::L3Address>& getRegistry() const {
        return _registry;
    }

    /**
     * Check if the registry contains a service with the given path.
     * @param path The name/path of the service to find
     * @return True if the registry contains the service, otherwise false.
     */
    bool contains(std::string path);

protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override {
        return NO_OF_INIT_STAGES;
    }
    virtual void handleMessage(cMessage *msg);

private:
    /**
     * The static registry.
     */
    std::unordered_map<std::string, inet::L3Address> _registry;
};

} /*end namespace soqosmw*/

#endif
