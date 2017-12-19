/*
 * IntQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_BASE_TYPES_INTQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_BASE_TYPES_INTQOSPOLICY_H_

#include <qospolicy/base/IQoSPolicy.h>

namespace soqosmw {

class IntQoSPolicy: public IQoSPolicy {
public:
    IntQoSPolicy(int value) : _value(value) {

    }
    virtual ~IntQoSPolicy(){

    }

    const int getValue() const {
        return _value;
    }

private:
    const int _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_BASE_TYPES_INTQOSPOLICY_H_ */
