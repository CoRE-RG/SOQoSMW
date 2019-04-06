/*
 * IntervalFramesQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_STD_LOCALPORTQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_STD_LOCALPORTQOSPOLICY_H_

#include <qospolicy/base/types/IntQoSPolicy.h>
#include <string>

namespace soqosmw {

namespace QoSPolicyNames {

const std::string LocalPort = "LocalPort";

} /* namespace QoSPolicyNames */

class LocalPortQoSPolicy: public IntQoSPolicy {
public:
    LocalPortQoSPolicy(int value) : IntQoSPolicy(value){

    }
    virtual ~LocalPortQoSPolicy(){

    }
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_STD_LOCALPORTQOSPOLICY_H_ */
