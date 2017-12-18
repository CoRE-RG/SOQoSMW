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

#include <endpoints/base/IEndpoint.h>

namespace soqosmw {
using namespace std;

IEndpoint::IEndpoint(string endpointPath, unordered_map<string, IQoSPolicy> qosPolicies, SOQoSMWApplicationBase* executingApplication) :
        _endpointPath(endpointPath), _qos(qosPolicies), _executingApplication(executingApplication){

}

IEndpoint::~IEndpoint() {
    // TODO Auto-generated destructor stub
}

//bool IEndpoint::mathes(string& path = NULL,
//        unordered_map<string, IQoSPolicy>& qos = NULL) {
//    bool pathMatches = false;
//    bool qosMatches = false;
//
//    if(path == NULL || path == _endpointPath){
//        pathMatches = true;
//    }
//    if(qos == NULL) {
//        qosMatches = true;
//    } else {
//        //TODO check if QOS are the same.
//    }
//
//    return pathMatches && qosMatches;
//}

bool IEndpoint::isExecutedBy(SOQoSMWApplicationBase* application) {
    return _executingApplication == application;
}
} /*end namespace soqosmw*/

