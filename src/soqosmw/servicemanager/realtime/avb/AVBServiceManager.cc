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

#include "AVBServiceManager.h"

namespace soqosmw{

Define_Module(AVBServiceManager);

void AVBServiceManager::initialize()
{
    // TODO - Generated method body
}

void AVBServiceManager::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

AVBSubscriber* AVBServiceManager::createSubscriber(std::string path) {
    return new AVBSubscriber(path);
}

AVBPublisher* AVBServiceManager::createPublisher(std::string path) {
    return new AVBPublisher(path);
}

} /*end namespace soqosmw*/
