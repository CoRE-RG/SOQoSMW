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

#include <connector/pubsub/writer/PublisherWriter.h>
#include <omnetpp/cmessage.h>
#include <algorithm>
#include <iterator>

using namespace std;
using namespace omnetpp;

namespace soqosmw {

PublisherWriter::PublisherWriter(SOQoSMWApplicationBase* executingApplication, unordered_map<string, IQoSPolicy*> qos) :
        IConnector(executingApplication), _qos(qos) {
}

PublisherWriter::~PublisherWriter() {
}

void PublisherWriter::write(cPacket* packet) {
    for (auto publisher : _publishers){
        //Todo add priority for real-time.
        publisher->publish(packet);
    }
}

void PublisherWriter::addPublisher(IPublisher* publisher) {
    //check if not already in the list, then add.
    auto it = find(_publishers.begin(), _publishers.end(), publisher);
    if (it == _publishers.end()){
        _publishers.push_back(publisher);
    }
}

void PublisherWriter::removePublisher(IPublisher* publisher) {
    //check if in the list, then remove.
    auto it = find(_publishers.begin(), _publishers.end(), publisher);
    if (it == _publishers.end()){
        _publishers.erase(it);
    }
}

IQoSPolicy* PublisherWriter::getQoSValueFor(std::string property) {
    return _qos[property];
}


void PublisherWriter::notify(cMessage* msg) {
    for (auto pub : _publishers){
        pub->notify(msg);
    }
}

} /*end namespace soqosmw*/

