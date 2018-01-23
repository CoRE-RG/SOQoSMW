/*
 * DoubleQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_BASE_TYPES_DOUBLEQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_BASE_TYPES_DOUBLEQOSPOLICY_H_

#include <qospolicy/base/IQoSPolicy.h>

namespace soqosmw {

class DoubleQoSPolicy: public IQoSPolicy {
public:

    DoubleQoSPolicy(double value) : _value(value) {

    }

    virtual ~DoubleQoSPolicy() {

    }

    const double getValue() const {
        return _value;
    }

private:
    const double _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_BASE_TYPES_DOUBLEQOSPOLICY_H_ */
