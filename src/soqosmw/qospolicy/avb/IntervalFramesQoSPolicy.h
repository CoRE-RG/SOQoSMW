/*
 * IntervalFramesQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_AVB_INTERVALFRAMESQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_AVB_INTERVALFRAMESQOSPOLICY_H_

#include <qospolicy/base/types/UInt16QoSPolicy.h>

namespace soqosmw {

namespace QoSPolicyNames {

const std::string IntervalFrames = "IntervalFrames";

} /* namespace QoSPolicyNames */

class IntervalFramesQoSPolicy: public UInt16QoSPolicy {
public:
    IntervalFramesQoSPolicy(uint16_t value) : UInt16QoSPolicy(value){

    }
    virtual ~IntervalFramesQoSPolicy(){

    }
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_AVB_INTERVALFRAMESQOSPOLICY_H_ */
