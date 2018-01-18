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

#include <base/EndpointDescription.h>
#include <discovery/static/StaticServiceDiscovery.h>
#include <endpoints/publisher/realtime/avb/AVBPublisher.h>
#include <endpoints/subscriber/realtime/avb/AVBSubscriber.h>
#include <omnetpp/cexception.h>
#include <omnetpp/cgate.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/cpar.h>
#include <omnetpp/regmacros.h>
#include <omnetpp/simutil.h>
#include <qosmanagement/negotiation/QoSNegotiationProtocol.h>
#include <qospolicy/management/QoSGroup.h>
#include <servicemanager/LocalServiceManager.h>
#include <algorithm>
#include <cstring>
#include <iterator>

#include <inet/networklayer/common/L3AddressResolver.h>

using namespace CoRE4INET;
using namespace std;
using namespace inet;

namespace soqosmw {

Define_Module(LocalServiceManager);

LocalServiceManager::LocalServiceManager() {
    _requestID = 0;
}

void LocalServiceManager::initialize(int stage) {


    if (stage == MY_INIT_STAGE) {
        _sd = dynamic_cast<StaticServiceDiscovery*>(getParentModule()->getSubmodule(
                   par("sdmoduleName")));

       _qosnp =
               dynamic_cast<QoSNegotiationProtocol*>(getParentModule()->getSubmodule(
                       par("qosnpmoduleName")));

        handleParameterChange(nullptr);
    }

}

void LocalServiceManager::handleMessage(cMessage *msg) {
    delete msg;
}

void LocalServiceManager::handleParameterChange(const char* parname) {

    //read UDP Common Parameters
    if (!parname || !strcmp(parname, "localAddress")) {
        const char* localAddr = par("localAddress");
        _localAddress = L3AddressResolver().resolve(localAddr);
    }

}

IPublisher* LocalServiceManager::createPublisher(string& publisherPath,
        unordered_map<string, IQoSPolicy*>& qosPolicies,
        SOQoSMWApplicationBase* executingApplication) {
    IPublisher* publisher = nullptr;

    //TODO check if service already exists.

    switch ((dynamic_cast<QoSGroup*>(qosPolicies[QoSPolicyNames::QoSGroup]))->getValue()) {
    case QoSGroup::WEB:
        break;
    case QoSGroup::STD:
        break;
    case QoSGroup::RT:
        publisher = new AVBPublisher(publisherPath, qosPolicies,
                executingApplication);
        _publishers.push_back(publisher);
        break;
    default:
        break;
    }

    return publisher;
}

int LocalServiceManager::requestSubscription(string& subscriberPath,
        string& publisherPath, unordered_map<string, IQoSPolicy*>& qosPolicies,
        cGate *notificationGate) {
    Enter_Method("LSM:requestSubscription()");
    int id = -1; // if an error occurs...

    //check if publisher exists in the network.
    if (_sd->contains(publisherPath)) {
        //create the request
        EndpointDescription local(subscriberPath, _localAddress,
                _qosnp->getProtocolPort());

        EndpointDescription remote(publisherPath, _sd->discover(publisherPath),
                _qosnp->getProtocolPort());
        Request * request = new Request(_requestID++, local, remote,
                qosPolicies, notificationGate);

        //create qos broker for the request
        _qosnp->createQoSBroker(request);

    } else {
        throw cRuntimeError(
                "The publisher you are requesting is unknown and has no entry in the ServiceRegistry.");
    }

    return id;

}

ISubscriber* LocalServiceManager::createSubscriber(string& subscriberPath,
        string& publisherPath, unordered_map<string, IQoSPolicy*>& qosPolicies,
        SOQoSMWApplicationBase* executingApplication) {
    ISubscriber* subscriber = nullptr;

    //TODO check if service exists in the network
    if (_sd->contains(publisherPath)) {
        switch ((dynamic_cast<QoSGroup*>(qosPolicies[QoSPolicyNames::QoSGroup]))->getValue()) {
        case QoSGroup::WEB:
            break;
        case QoSGroup::STD:
            break;
        case QoSGroup::RT:

            //TODO check if such an subscriber exists already to reuse it.

            subscriber = new AVBSubscriber(subscriberPath, publisherPath,
                    qosPolicies, executingApplication);
            _subscribers.push_back(subscriber);
            break;
        default:
            break;
        }

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

bool LocalServiceManager::removePublisher(IPublisher* publisher,
        SOQoSMWApplicationBase* executingApplication) {
    bool removed = false;
    auto it = find(_publishers.begin(), _publishers.end(), publisher);
    if (it != _publishers.end()
            && publisher->isExecutedBy(executingApplication)) {
        _publishers.erase(it);
        delete publisher;
        removed = true;
    }
    return removed;
}

bool LocalServiceManager::removeSubscriber(ISubscriber* subscriber,
        SOQoSMWApplicationBase* executingApplication) {
    bool removed = false;
    auto it = find(_subscribers.begin(), _subscribers.end(), subscriber);
    if (it != _subscribers.end()
            && subscriber->isExecutedBy(executingApplication)) {
        _subscribers.erase(it);
        delete subscriber;
        removed = true;
    }
    return removed;
}

} /* end namespace  */
