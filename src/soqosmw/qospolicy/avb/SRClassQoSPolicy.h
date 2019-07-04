/*
 * SRClassQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_PUBLISHER_AVB_SRCLASSQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_PUBLISHER_AVB_SRCLASSQOSPOLICY_H_

#include <qospolicy/base/types/IntQoSPolicy.h>
#include <string>
#include <core4inet/base/avb/AVBDefs.h>

namespace soqosmw {

namespace QoSPolicyNames {

const std::string SRClass = "SRClass"; //integer ID

} /* namespace QoSPolicyNames */

class SRClassQoSPolicy: public IQoSPolicy {
public:

    SRClassQoSPolicy(CoRE4INET::SR_CLASS value) : _value (value) {

    }virtual ~SRClassQoSPolicy() {

    }

    const CoRE4INET::SR_CLASS getValue(){
        return _value;
    }

    virtual bool operator==(IQoSPolicy& other){
        SRClassQoSPolicy& real = static_cast<SRClassQoSPolicy&> (other);
        return real._value == _value;
    }

private:
    const CoRE4INET::SR_CLASS _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_PUBLISHER_AVB_SRCLASSQOSPOLICY_H_ */
