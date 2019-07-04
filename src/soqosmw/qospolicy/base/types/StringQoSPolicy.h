/*
 * StringQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_BASE_TYPES_STRINGQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_BASE_TYPES_STRINGQOSPOLICY_H_

#include <qospolicy/base/IQoSPolicy.h>
#include <string>

namespace soqosmw {

class StringQoSPolicy: public IQoSPolicy {
public:

    StringQoSPolicy(std::string value) :
            _value(value) {

    }

    virtual ~StringQoSPolicy() {

    }

    const std::string getValue() const {
        return _value;
    }

    virtual bool operator==(IQoSPolicy& other){
        StringQoSPolicy& real = static_cast<StringQoSPolicy&> (other);
        return real._value == _value;
    }

private:
    const std::string _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_BASE_TYPES_STRINGQOSPOLICY_H_ */
