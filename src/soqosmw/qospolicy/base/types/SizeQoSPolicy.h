/*
 * SizeQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_BASE_TYPES_SIZEQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_BASE_TYPES_SIZEQOSPOLICY_H_

#include <crtdefs.h>
#include <qospolicy/base/IQoSPolicy.h>

namespace soqosmw {

class SizeQoSPolicy: public IQoSPolicy {
public:
    SizeQoSPolicy(size_t value) : _value(value) {

    }virtual ~SizeQoSPolicy() {

    }

    const size_t getValue() const {
        return _value;
    }

private:
    const size_t _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_BASE_TYPES_SIZEQOSPOLICY_H_ */
