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

#include <connector/pubsub/reader/SubscriptionReader.h>
#include <connector/pubsub/writer/PublisherWriter.h>
#include <endpoints/publisher/realtime/avb/AVBPublisher.h>
#include <endpoints/publisher/standard/tcp/TCPPublisher.h>
#include <endpoints/subscriber/realtime/avb/AVBSubscriber.h>
#include <endpoints/subscriber/standard/tcp/TCPSubscriber.h>
#include <factory/ServiceEndpointFactory.h>
#include <messages/QoSNegotiationProtocol/ConnectionSpecificInformation_m.h>

namespace soqosmw {

IPublisher* ServiceEndpointFactory::createPublisher(std::string& publisherPath,
        int qos, PublisherWriter* writer) {
    IPublisher* publisher = nullptr;
    if(writer){
        switch(qos){
        case QoSGroups::RT:

            //Create AVB Publisher!
            publisher = new AVBPublisher(publisherPath, writer);
            break;
        case QoSGroups::STD:
            //check if UDP or TCP is required

            //Create TCP Publisher!
            publisher = new TCPPublisher(publisherPath, writer);
            break;

        default:
            break;
        }
    }

    //connect endpoint to the writer
    if(publisher){
        writer->addPublisher(publisher);
    }

    return publisher;
}

ISubscriber* ServiceEndpointFactory::createSubscriber(
        std::string& publisherPath, ConnectionSpecificInformation* csi,
        SubscriptionReader* reader) {
    ISubscriber* subscriber = nullptr;

    switch(csi->getConnectionType()){
    case ConnectionType::ct_avb:

        //create according endpoint
        subscriber = new AVBSubscriber(publisherPath, reader, csi);
        break;
    case ConnectionType::ct_tcp:

        //create according endpoint
        subscriber = new TCPSubscriber(publisherPath, reader, csi);
        break;
    case ConnectionType::ct_udp:

        //create according endpoint
        //TODO UDPSubscriber
    default:
        break;
    }

    //connect endpoint to the reader
    if(subscriber){
        reader->addSubscriber(subscriber);
    }
    return subscriber;
}

ServiceEndpointFactory& ServiceEndpointFactory::getInstance() {
    static ServiceEndpointFactory instance;
    return instance;
}

ServiceEndpointFactory::ServiceEndpointFactory() {
    // TODO Auto-generated constructor stub

}

ServiceEndpointFactory::~ServiceEndpointFactory() {
    // TODO Auto-generated destructor stub
}

ServiceEndpointFactory::ServiceEndpointFactory(const ServiceEndpointFactory&) {
}

} /* end namespace  */
