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

#include <omnetpp/csimplemodule.h>
#include <qosmanagement/negotiation/datatypes/Request.h>
#include <qospolicy/base/qospolicy.h>
#include <atomic>
#include <string>
#include <unordered_map>
#include <vector>

#include <inet/networklayer/common/L3Address.h>

namespace soqosmw {
class PublisherConnector;
class SubscriberConnector;
} /* namespace soqosmw */

namespace soqosmw {
class QoSNegotiationProtocol;
} /* namespace soqosmw */

namespace soqosmw {
class SOQoSMWApplicationBase;
class StaticServiceDiscovery;
} /* namespace soqosmw */

using namespace omnetpp;

namespace soqosmw {

#define NO_OF_INIT_STAGES 15

/**
 * @brief The LocalServiceManager is used to create, find and remove local Services.
 *
 * @author Timo Haeckel
 */
class LocalServiceManager: public cSimpleModule {
protected:
    /**
     * @brief Initialization of the module.
     */
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override {
        return NO_OF_INIT_STAGES;
    }

    /**
     * @brief This module should receive any messages.
     *
     * @param msg Parameter
     */
    virtual void handleMessage(cMessage *msg);

    virtual void handleParameterChange(const char* parname) override;

public:
    LocalServiceManager();
    virtual ~LocalServiceManager();

    /**
     * @brief This Method creates a new Publisher according to the QoSPolicies.
     *
     * @param publisherPath Path of the Publisher Service (e.g. "reifendruck/links")
     * @param qosPolicies The QoS Policies for the Publisher.
     * @param executingModule The omnetpp::cModule executing the request.
     *
     * @return If a publisher could be created it returns a pointer to the PublisherWriter. Else nullptr.
     */
    ConnectorBase* createPublisher(std::string& publisherPath,
            std::unordered_map<std::string, IQoSPolicy*>& qosPolicies,
            SOQoSMWApplicationBase* executingApplication);

    /**
     * @brief This Method creates a new Subscriber for the publisher Service according to the QoSPolicies.
     *
     * @param subscriberPath Path of the Subscriber Service (e.g. "bordcomputer")
     * @param publisherPath Path of the Publisher Service (e.g. "reifendruck/links")
     * @param qosPolicies The QoS Policies for the Subscriber.
     * @param executingModule The omnetpp::cModule executing the request.
     *
     * @return If a subscriber could be created it returns a pointer to the SubscriptionReader. Else nullptr.
     */
    ConnectorBase* createSubscriber(std::string& subscriberPath,
            std::string& publisherPath,
            std::unordered_map<std::string, IQoSPolicy*>& qosPolicies,
            SOQoSMWApplicationBase* executingApplication);

    /**
     * Finds the connector for the publisher
     * @param publisherPath     the name of the publisher as a path
     * @return                  the connector if found, else nullptr
     */
    ConnectorBase* getPublisherWriterForName (std::string& publisherPath);

    /**
     * Finds the connector for the subscriber
     * @param publisherPath     the name of the publisher as a path
     * @return                  the connector if found, else nullptr
     */
    ConnectorBase* getSubscriptionReaderForName (std::string& publisherPath);


    /**
     * @brief This method removes the given publisher.
     * NOTE the publisher pointer is no longer valid now and will be set to a nullptr.
     *
     * @param publisher A pointer to the publisher that should be removed.
     * @param executingModule The omnetpp::cModule executing the request.
     *
     * @return true if the publisher was removed, false if not found.
     */
    bool removePublisher(ConnectorBase* publisher,
            SOQoSMWApplicationBase* executingApplication);

    /**
     * @brief This method removes the given subscriber.
     * NOTE the subscriber pointer is no longer valid now and will be set to a nullptr.
     *
     * @param subscriber A pointer to the subscriber that should be removed.
     * @param executingModule The omnetpp::cModule executing the request.
     *
     * @return true if the subscriber was removed, false if not found.
     */
    bool removeSubscriber(ConnectorBase* subscriber,
            SOQoSMWApplicationBase* executingApplication);

private:
    /**
     * Contains pointers to the existing publishers on a node.
     */
    std::unordered_map<std::string, PublisherConnector*> _publisherConnectors;

    /**
     * contains pointers to the existing subscribers on a node.
     */
    std::unordered_map<std::string, SubscriberConnector*> _subscriberConnectors;

    /**
     * A pointer to the service discovery.
     */
    StaticServiceDiscovery* _sd;

    /**
     * A pointer to the QoS Negotiation Protocol module.
     */
    QoSNegotiationProtocol* _qosnp;

    /**
     * Static ID for created Requests.
     */
    std::atomic<int> _requestID;

    /**
     * Stores all issued requests.
     */
    std::vector<Request*> _requests;

    /**
     * Caches the localAddress parameter.
     */
    inet::L3Address _localAddress;
};

} /* end namespace  */

#endif
