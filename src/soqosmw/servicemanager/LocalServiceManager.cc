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
#include "soqosmw/connector/pubsub/reader/SubscriberConnector.h"
#include "soqosmw/connector/pubsub/writer/PublisherConnector.h"
#include <discovery/static/StaticServiceDiscovery.h>
#include <qosmanagement/negotiation/QoSNegotiationProtocol.h>
#include <servicemanager/LocalServiceManager.h>
#include <algorithm>
#include <cstring>
#include <iterator>

#include <inet/networklayer/common/L3AddressResolver.h>

using namespace std;
using namespace inet;

namespace soqosmw {
#define LSM_INIT_STAGE_1 1
#define LSM_INIT_STAGE 14

Define_Module(LocalServiceManager);

LocalServiceManager::LocalServiceManager() {
    _requestID = 0;
}

LocalServiceManager::~LocalServiceManager() {
}

void LocalServiceManager::initialize(int stage) {

    if(stage == LSM_INIT_STAGE_1) {
    }
    if (stage == LSM_INIT_STAGE) {
        handleParameterChange(nullptr);
        _sd = dynamic_cast<StaticServiceDiscovery*>(getParentModule()->getSubmodule(
                   par("sdmoduleName")));

       _qosnp =
               dynamic_cast<QoSNegotiationProtocol*>(getParentModule()->getSubmodule(
                       par("qosnpmoduleName")));
       WATCH_MAP(_publisherConnectors);
       WATCH_MAP(_subscriberConnectors);
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

ConnectorBase* LocalServiceManager::registerPublisherService(std::string& publisherPath,
            QoSPolicyMap& qosPolicies,
            SOQoSMWApplicationBase* executingApplication) {
    Enter_Method("LSM:registerPublisherService()");

    // check if the publisher already exists.
    if(PublisherConnector *connector = _publisherConnectors.find(publisherPath)){
        if(connector->addApplication(executingApplication)){
            connector->setQos(qosPolicies);
            return connector;
        } else {
            throw cRuntimeError("This Publisher Service already exists on this host...");
        }
    }

    // create a connector for the publisher
    // 1. Find the factory object;
    cModuleType *moduleType = cModuleType::get("soqosmw.connector.pubsub.writer.PublisherConnector");
    // 2. Create the module;
    PublisherConnector *module = dynamic_cast<PublisherConnector*> (moduleType->create("PublisherConnector", this));
    // 3. Set up its parameters and gate sizes as needed;
    module->addApplication(executingApplication);
    module->setQos(qosPolicies);
    module->finalizeParameters();
    // 4. Tell the (possibly compound) module to recursively create its internal submodules and connections;
    module->buildInside();
    // 5. Schedule activation message(s) for the new simple module(s).
    module->scheduleStart(simTime());

    //save the writer so that new endpoints can be connected to the application.
    _publisherConnectors[publisherPath] = module;

    return module;
}

ConnectorBase* LocalServiceManager::registerSubscriberService(std::string& subscriberPath,
            std::string& publisherPath,
            QoSPolicyMap& qosPolicies,
            SOQoSMWApplicationBase* executingApplication)
{
    Enter_Method("LSM:registerSubscriberService()");

    // check if the subscriber already exists.
    if(SubscriberConnector *connector = _subscriberConnectors.find(publisherPath)){
        // we allready have a service subscribing to the data
        if(equalQoSMap(qosPolicies, connector->getQos())){
            // same qos as well so try to add and return
            if(connector->addApplication(executingApplication)){
                return connector;
            } else {
                throw cRuntimeError("This Subscriber service already exists on this host...");
            }
        }
    }
    // otherwise we need a new negotiation!

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

    // create a connector for the subscriber
    // 1. Find the factory object;
    cModuleType *moduleType = cModuleType::get("soqosmw.connector.pubsub.writer.SubscriberConnector");
    // 2. Create the module;
    SubscriberConnector *module = dynamic_cast<SubscriberConnector*> (moduleType->create("SubscriberConnector", this));
    // 3. Set up its parameters and gate sizes as needed;
    module->addApplication(executingApplication);
    module->setQos(qosPolicies);
    module->finalizeParameters();
    // 4. Tell the (possibly compound) module to recursively create its internal submodules and connections;
    module->buildInside();
    // 5. Schedule activation message(s) for the new simple module(s).
    module->scheduleStart(simTime());

    // save the reader so that new endpoints can be connected to the application.
    _subscriberConnectors[publisherPath] = module;

    return module;
}

ConnectorBase* LocalServiceManager::getPublisherConnectorForName(
        std::string& publisherPath) {

    return _publisherConnectors[publisherPath];
}


ConnectorBase* LocalServiceManager::getSubscriberConnectorForName(
        std::string& publisherPath) {

    return _subscriberConnectors[publisherPath];
}

PublisherEndpointBase* LocalServiceManager::createOrFindPublisherFor(
        std::string& publisherPath, int qos) {
}

PublisherEndpointBase* LocalServiceManager::findPublisherLike(
        std::string& publisherPath, int qos) {

}

SubscriberEndpointBase* LocalServiceManager::createOrFindSubscriberFor(
        std::string& publisherPath, int qos) {
}

SubscriberEndpointBase* LocalServiceManager::findSubscriberLike(
        std::string& publisherPath, int qos) {
}

} /* end namespace  */
