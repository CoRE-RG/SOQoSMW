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

#ifndef __HAUPTPROJEKT_TIMO_HAECKEL_LOCALSERVICEMANAGER_H_
#define __HAUPTPROJEKT_TIMO_HAECKEL_LOCALSERVICEMANAGER_H_

#include <omnetpp.h>
#include <vector>

#include <soqosmw/endpoints/publisher/base/IPublisher.h>
#include <soqosmw/endpoints/subscriber/base/ISubscriber.h>
#include <soqosmw/discovery/static/StaticServiceDiscovery.h>

using namespace omnetpp;

namespace soqosmw {

/**
 * TODO - Generated class
 */
class LocalServiceManager : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    virtual ~LocalServiceManager();
    virtual IPublisher* createPublisher(std::string path, std::vector<IQoSPolicy> qosPolicies);
    virtual ISubscriber* createSubscriber(std::string path, std::vector<IQoSPolicy> qosPolicies);

  private:
    std::vector<IPublisher*> _publishers;
    std::vector<ISubscriber*> _subscribers;

    StaticServiceDiscovery* _sd;
};

} /* end namespace  */


#endif
