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

#include <qospolicy/base/QoSPolicyFactory.h>

namespace soqosmw {

using namespace std;

QoSPolicyFactory::QoSPolicyFactory() {
    // TODO Auto-generated constructor stub

}

QoSPolicyFactory::~QoSPolicyFactory() {
    // TODO Auto-generated destructor stub

}

unordered_map<string, IQoSPolicy*>& QoSPolicyFactory::extractPolicyFromPar(
        omnetpp::cPar& parameter) {
    unordered_map<string, IQoSPolicy*> policies;

    return policies;
}

} /* end namepsace soqosmw */
