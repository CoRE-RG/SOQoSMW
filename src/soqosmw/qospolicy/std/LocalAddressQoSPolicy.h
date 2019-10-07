//
// c Timo Haeckel for HAW Hamburg
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

#ifndef SOQOSMW_QOSPOLICY_STD_LOCALADDRESSQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_STD_LOCALADDRESSQOSPOLICY_H_

#include "soqosmw/qospolicy/base/types/StringQoSPolicy.h"

#include <string>

namespace soqosmw {

namespace QoSPolicyNames {

const std::string LocalAddress = "LocalAddress";

} /* namespace QoSPolicyNames */

/**
 * @brief The LocalAddressQoSPolicy.
 *
 * @ingroup soqosmw/qospolicy
 *
 * @author Timo Haeckel for HAW Hamburg
 */
class LocalAddressQoSPolicy: public StringQoSPolicy {
public:

    LocalAddressQoSPolicy(std::string value) :
        StringQoSPolicy(value) {

    }

    virtual ~LocalAddressQoSPolicy() {

    }
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_STD_LOCALADDRESSQOSPOLICY_H_ */
