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
#include <connector/pubsub/reader/SubscriptionReader.h>
#include <connector/pubsub/writer/PublisherWriter.h>
#include <discovery/static/StaticServiceDiscovery.h>
#include <omnetpp/cexception.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/cpar.h>
#include <omnetpp/regmacros.h>
#include <omnetpp/simutil.h>
#include <qosmanagement/negotiation/QoSNegotiationProtocol.h>
#include <servicemanager/LocalServiceManager.h>
#include <algorithm>
#include <cstring>
#include <iterator>

#include <inet/networklayer/common/L3AddressResolver.h>

using namespace std;
using namespace inet;

namespace soqosmw {

Define_Module(LocalServiceManager);

LocalServiceManager::LocalServiceManager() {
    _requestID = 0;
}

LocalServiceManager::~LocalServiceManager() {
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

PublisherWriter* LocalServiceManager::createPublisher(string& publisherPath,
        unordered_map<string, IQoSPolicy*>& qosPolicies,
        SOQoSMWApplicationBase* executingApplication) {
    PublisherWriter* writer = new PublisherWriter(executingApplication, qosPolicies);

    //save the writer so that new endpoints can be connected to the application.
    _publisherWriters[publisherPath] = writer;

    return writer;
}

SubscriptionReader* LocalServiceManager::createSubscriber(string& subscriberPath,
        string& publisherPath, unordered_map<string, IQoSPolicy*>& qosPolicies,
        SOQoSMWApplicationBase* executingApplication) {

    Enter_Method("LSM:createSubscriber()");

    //check if publisher exists in the network and start the negotiation with a request.
    if (_sd->contains(publisherPath)) {
        //create the request
        EndpointDescription local(subscriberPath, _localAddress,
                _qosnp->getProtocolPort());

        EndpointDescription remote(publisherPath, _sd->discover(publisherPath),
                _qosnp->getProtocolPort());
        Request * request = new Request(_requestID++, local, remote,
                qosPolicies, nullptr);

        //create qos broker for the request
        _qosnp->createQoSBroker(request);

    } else {
        throw cRuntimeError(
                "The publisher you are requesting is unknown and has no entry in the ServiceRegistry.");
    }

    //create the writer
    SubscriptionReader* reader = new SubscriptionReader(executingApplication, qosPolicies);

    // save the reader so that new endpoints can be connected to the application.
    _subscriptionReaders[publisherPath] = reader;

    return reader;
}

PublisherWriter* LocalServiceManager::getPublisherWriterForName(
        std::string& publisherPath) {

    return _publisherWriters[publisherPath];
}


SubscriptionReader* LocalServiceManager::getSubscriptionReaderForName(
        std::string& publisherPath) {

    return _subscriptionReaders[publisherPath];
}


bool LocalServiceManager::removePublisher(PublisherWriter* publisher,
        SOQoSMWApplicationBase* executingApplication){
    //dummy
    return true;
}

/**bool LocalServiceManager::removePublisher(PublisherWriter* publisher,
        SOQoSMWApplicationBase* executingApplication) {
    bool removed = false;
    _publisherWriters.erase("sasd");
    auto it = find(_publishers.begin(), _publishers.end(), publisher);
    if (it != _publishers.end()
            && publisher->isExecutedBy(executingApplication)) {
        _publishers.erase(it);
        delete publisher;
        removed = true;
    }
    return removed;
}**/

bool LocalServiceManager::removeSubscriber(SubscriptionReader* subscriber,
        SOQoSMWApplicationBase* executingApplication) {
    //dummy
    return true;
}
/**
bool LocalServiceManager::removeSubscriber(SubscriptionReader* subscriber,
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
}**/

} /* end namespace  */
