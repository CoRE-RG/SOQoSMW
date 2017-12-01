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

#include "StaticServiceDiscovery.h"

#include "inet/networklayer/common/L3AddressResolver.h"
#include <string>

namespace soqosmw{

using namespace std;

Define_Module(StaticServiceDiscovery);

void StaticServiceDiscovery::initialize(int stage)
{
    if(stage == MY_INIT_STAGE) {
        cout << "Initialising SD:";
        cXMLElement *config = par("services").xmlValue();
        cout << " read config: " << config->str();
        //navigate to services and get all entries
        cXMLElementList services = config->getChildrenByTagName("service");
        if(services.empty()){
            cout << " --> list is empty";
        }
        for (size_t i = 0; i < services.size(); i++){
            //check each element and get the service name and the node
            cout << " --> element " << i << ": ";
            cXMLElement* service = services[i];
            const char* name = service->getAttribute("name");
            const char* node = service->getAttribute("node");

            cout << name << " at " << node;

            //ressolve the address
            const inet::L3Address address = inet::L3AddressResolver().resolve(node);

            //add entry to map
            _registry[name] = address;
        }
        cout << endl;
    }

}

inet::L3Address& StaticServiceDiscovery::discover(std::string serviceName) {
    return _registry[serviceName];
}

void StaticServiceDiscovery::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

} /*end namespace soqosmw*/
