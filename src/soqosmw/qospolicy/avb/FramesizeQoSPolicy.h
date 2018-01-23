/*
 * FramesizeQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_PUBLISHER_AVB_FRAMESIZEQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_PUBLISHER_AVB_FRAMESIZEQOSPOLICY_H_

#include <qospolicy/base/types/SizeQoSPolicy.h>

namespace soqosmw {

namespace QoSPolicyNames {

const std::string Framesize = "Framesize";

} /* namespace QoSPolicyNames */

class FramesizeQoSPolicy: public SizeQoSPolicy {
public:
    FramesizeQoSPolicy(size_t value) : SizeQoSPolicy(value){

    }
    virtual ~FramesizeQoSPolicy(){

    }
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_PUBLISHER_AVB_FRAMESIZEQOSPOLICY_H_ */
