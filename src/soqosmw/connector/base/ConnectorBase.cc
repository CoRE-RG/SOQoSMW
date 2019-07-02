//
// c Timo Haeckel, for HAW Hamburg
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

#include "ConnectorBase.h"

#include "soqosmw/endpoints/base/EndpointBase.h"
#include "soqosmw/applications/base/SOQoSMWApplicationBase.h"

namespace soqosmw {

void ConnectorBase::initialize()
{
    enabled = true;
}

void ConnectorBase::handleMessage(cMessage *msg)
{
    if(enabled){
        if (msg->arrivedOn("applicationIn")){
            //from application --> forward to all endpoints
            for(auto endpoint : _endpoints) {
                sendDirect(msg->dup(), _endpoints->gate("connectorIn"));
            }

        } else if (msg->arrivedOn("endpointIn")) {
            //from endpoint --> forward to application
            sendDirect(msg->dup(), _executingApplication->gate("connectorIn"));
        }
    }

    delete msg;
}

const std::vector<EndpointBase*>& ConnectorBase::getEndpoints() const {
    return _endpoints;
}

void ConnectorBase::setEndpoints(
        const std::vector<EndpointBase*>& endpoints) {
    _endpoints = endpoints;
}

const SOQoSMWApplicationBase*& ConnectorBase::getExecutingApplication() const {
    return _executingApplication;
}

void ConnectorBase::setExecutingApplication(
        const SOQoSMWApplicationBase*& executingApplication) {
    _executingApplication = executingApplication;
}

bool ConnectorBase::isEnabled() const {
    return enabled;
}

void ConnectorBase::setEnabled(bool enabled = false) {
    this->enabled = enabled;
}

} /*end namespace soqosmw*/
