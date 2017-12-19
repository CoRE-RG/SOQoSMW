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

#include <endpoints/publisher/base/IPublisher.h>
#include <endpoints/subscriber/base/ISubscriber.h>
#include <omnetpp/csimplemodule.h>
#include <qospolicy/base/IQoSPolicy.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace soqosmw {
class SOQoSMWApplicationBase;
class StaticServiceDiscovery;
} /* namespace soqosmw */

using namespace omnetpp;

namespace soqosmw {

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
    virtual void initialize();

    /**
     * @brief This module should receive any messages.
     *
     * @param msg Parameter
     */
    virtual void handleMessage(cMessage *msg);

public:
    virtual ~LocalServiceManager();

    /**
     * @brief This Method creates a new Publisher according to the QoSPolicies.
     *
     * @param publisherPath Path of the Publisher Service (e.g. "reifendruck/links")
     * @param qosPolicies The QoS Policies for the Publisher.
     * @param executingModule The omnetpp::cModule executing the request.
     *
     * @return If a publisher could be created it returns a pointer to the Publisher. Else nullptr.
     */
    IPublisher* createPublisher(std::string& publisherPath,
            std::unordered_map<std::string, IQoSPolicy*>& qosPolicies, SOQoSMWApplicationBase* executingApplication);

    /**
     * @brief This Method creates a new Subscriber for the publisher Service according to the QoSPolicies.
     *
     * @param subscriberPath Path of the Subscriber Service (e.g. "bordcomputer")
     * @param publisherPath Path of the Publisher Service (e.g. "reifendruck/links")
     * @param qosPolicies The QoS Policies for the Subscriber.
     * @param executingModule The omnetpp::cModule executing the request.
     *
     * @return If a subscriber could be created it returns a pointer to the Subscriber. Else nullptr.
     */
    ISubscriber* createSubscriber(std::string& subscriberPath,
            std::string& publisherPath, std::unordered_map<std::string, IQoSPolicy*>& qosPolicies, SOQoSMWApplicationBase* executingApplication);

    /**
     * @brief Check if a publisher exists.
     *  If no arguments are passed,
     *             this method checks if any publisher exists on this node.
     *  If the publisherPath is set,
     *             this method checks if a publisher with matching path exists.
     *  If the publisherPath and the qosPolicies are set,
     *             this method checks if a publisher with matching path and matching qosPolicies exists.
     *
     * @param publisherPath The path of the publisher to find.
     * @param qosPolicies The QoS Policies of the publisher to find. //NOT YET IMPLEMENTED
     *
     * @return the number of matches.
     */
//    int existsPublisher(std::string& publisherPath = "",
//            std::vector<IQoSPolicy> qosPolicies = NULL);

    /**
     * @brief Check if a subscriber exists.
     *  If no arguments are passed,
     *             this method checks if any subscriber exists on this node.
     *  If the subscriberPath is set,
     *             this method checks if a subscriber with matching subscriberPath exists.
     *  If the subscriberPath and the qosPolicies are set,
     *             this method checks if a subscriber with matching subscriberPath and matching qosPolicies exists.
     *  If the publisherPath is set,
     *             this method checks if a subscriber with matching publisherPath exists.
     *  If the publisherPath and the qosPolicies are set,
     *             this method checks if a subscriber with matching publisherPath and matching qosPolicies exists.
     *  If the subscriberPath, the qosPolicies and the publisherPath are set,
     *             this method checks if a subscriber with matching subscriberPath, matching qosPolicies and matching publisherPath exists.
     *
     * @param subscriberPath The subscriberPath of the subscriber to find.
     * @param qosPolicies The QoS Policies of the subscriber to find. //NOT YET IMPLEMENTED
     * @param publisherPath The publisherPath of the subscriber to find.
     *
     * @return the number of matches.
     */
//    int existsSubscriber(std::string& subscriberPath = "",
//            std::vector<IQoSPolicy>& qosPolicies = NULL,
//            std::string& publisherPath = "");

    /**
     * @brief This method removes the given publisher.
     * NOTE the publisher pointer is no longer valid now and will be set to a nullptr.
     *
     * @param publisher A pointer to the publisher that should be removed.
     * @param executingModule The omnetpp::cModule executing the request.
     *
     * @return true if the publisher was removed, false if not found.
     */
    bool removePublisher(IPublisher* publisher, SOQoSMWApplicationBase* executingApplication);

    /**
     * @brief This method removes the given subscriber.
     * NOTE the subscriber pointer is no longer valid now and will be set to a nullptr.
     *
     * @param subscriber A pointer to the subscriber that should be removed.
     * @param executingModule The omnetpp::cModule executing the request.
     *
     * @return true if the subscriber was removed, false if not found.
     */
    bool removeSubscriber(ISubscriber* subscriber, SOQoSMWApplicationBase* executingApplication);

private:
    /**
     * Contains pointers to the existing publishers on a node.
     */
    std::vector<IPublisher*> _publishers;

    /**
     * contains pointers to the existing subscribers on a node.
     */
    std::vector<ISubscriber*> _subscribers;

    /**
     * A pointer to the service discovery.
     */
    StaticServiceDiscovery* _sd;
};

} /* end namespace  */

#endif
