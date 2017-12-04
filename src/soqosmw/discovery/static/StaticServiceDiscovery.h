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

#include <omnetpp.h>
#include <unordered_map>
#include <soqosmw/discovery/base/IServiceDiscovery.h>
#include <inet/networklayer/common/L3Address.h>


using namespace omnetpp;

namespace soqosmw{
#define NO_OF_INIT_STAGES 15
#define MY_INIT_STAGE 13
/**
 * TODO - Generated class
 */
class StaticServiceDiscovery : public IServiceDiscovery
{
  public:
    inet::L3Address& discover(std::string serviceName);

    const std::unordered_map<std::string, inet::L3Address>& getRegistry() const {
        return _registry;
    }

    bool contains(std::string path);

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override {
        return NO_OF_INIT_STAGES;
    }
    virtual void handleMessage(cMessage *msg);

  private:
    std::unordered_map<std::string, inet::L3Address> _registry;
};

} /*end namespace soqosmw*/

#endif
