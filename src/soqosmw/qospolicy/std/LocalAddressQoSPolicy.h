/*
 * StringQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_STD_LOCALADDRESSQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_STD_LOCALADDRESSQOSPOLICY_H_

#include <qospolicy/base/types/StringQoSPolicy.h>
#include <string>

namespace soqosmw {

namespace QoSPolicyNames {

const std::string LocalAddress = "LocalAddress";

} /* namespace QoSPolicyNames */

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
