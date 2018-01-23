/*
 * UInt16QoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_BASE_TYPES_UINT16QOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_BASE_TYPES_UINT16QOSPOLICY_H_

#include <qospolicy/base/IQoSPolicy.h>
#include <cstdint>

namespace soqosmw {

class UInt16QoSPolicy: public IQoSPolicy {
public:
    UInt16QoSPolicy(uint16_t value) : _value(value) {

    }
    virtual ~UInt16QoSPolicy(){

    }

    const uint16_t getValue() const {
        return _value;
    }

private:
    const uint16_t _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_BASE_TYPES_UINT16QOSPOLICY_H_ */
