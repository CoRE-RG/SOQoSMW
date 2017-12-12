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

#include <algorithm>

#include "LocalServiceManager.h"
#include <soqosmw/endpoints/publisher/realtime/avb/AVBPublisher.h>
#include <soqosmw/endpoints/subscriber/realtime/avb/AVBSubscriber.h>

namespace soqosmw {

Define_Module(LocalServiceManager);

void LocalServiceManager::initialize() {
    _sd = dynamic_cast<StaticServiceDiscovery*>(getParentModule()->getSubmodule(
            par("sdmoduleName")));
}

void LocalServiceManager::handleMessage(cMessage *msg) {
    delete msg;
}

IPublisher* LocalServiceManager::createPublisher(std::string& publisherPath,
        std::vector<IQoSPolicy> qosPolicies) {
    IPublisher* publisher = nullptr;
    //TODO check if service already exists.

    //TODO check qosPolicies to know which publisher should be created...

    publisher = new AVBPublisher(publisherPath, qosPolicies);
    _publishers.push_back(publisher);

    return publisher;
}

ISubscriber* LocalServiceManager::createSubscriber(std::string& subscriberPath,
        std::string& publisherPath, std::vector<IQoSPolicy>& qosPolicies) {
    ISubscriber* subscriber = nullptr;
    //TODO check if service exists in the network
    if (_sd->contains(subscriberPath)) {

        //TODO check qosPolicies to know which subscriber should be created...

        //TODO check if such an subscriber exists already to reuse it.

        subscriber = new AVBSubscriber(subscriberPath, publisherPath,
                qosPolicies);
        _subscribers.push_back(subscriber);
    }

    return subscriber;
}

LocalServiceManager::~LocalServiceManager() {
    for (std::vector<IPublisher*>::iterator it = _publishers.begin();
            it != _publishers.end(); ++it) {
        delete (*it);
    }
    _publishers.clear();
    for (std::vector<ISubscriber*>::iterator it = _subscribers.begin();
            it != _subscribers.end(); ++it) {
        delete (*it);
    }
    _subscribers.clear();
}

//int LocalServiceManager::existsPublisher(std::string& publisherPath = NULL,
//        std::vector<IQoSPolicy> qosPolicies = NULL) {
//    const bool pubPathSet = publisherPath != NULL;
//    const bool qosSet = qosPolicies != NULL;
//
//    //If no arguments are passed,
//    if(!pubPathSet && !qosSet){
//        //this method checks if any publisher exists on this node.
//        return _publishers.size();
//    }
//    //If the publisherPath is set,
//    else {
//        //this method checks if a publisher with matching path exists.
//        int count = 0;
//        for (std::vector<IPublisher*>::iterator it = _publishers.begin();
//                it != _publishers.end(); ++it) {
//            if((*it)->matches(publisherPath, qosPolicies)){
//                count++;
//            }
//        }
//        return count;
//    }
//
//}

//int LocalServiceManager::existsSubscriber(std::string& subscriberPath,
//        std::vector<IQoSPolicy>& qosPolicies, std::string& publisherPath) {
//}

bool LocalServiceManager::removePublisher(IPublisher* publisher) {
    bool removed = false;
    auto it = find(_publishers.begin(), _publishers.end(), publisher);
    if (it != _publishers.end()) {
        _publishers.erase(it);
        delete publisher;
        removed = true;
    }
    return removed;
}

bool LocalServiceManager::removeSubscriber(ISubscriber* subscriber) {
    bool removed = false;
    auto it = find(_subscribers.begin(), _subscribers.end(), subscriber);
    if (it != _subscribers.end()) {
        _subscribers.erase(it);
        delete subscriber;
        removed = true;
    }
    return removed;
}

} /* end namespace  */
