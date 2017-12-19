/*
 * StreamIDQoSPolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_PUBLISHER_AVB_STREAMIDQOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_PUBLISHER_AVB_STREAMIDQOSPOLICY_H_

#include <qospolicy/base/types/IntQoSPolicy.h>

namespace soqosmw {
namespace QoSPolicyNames {

const std::string StreamID = "StreamID"; //integer ID

} /* namespace QoSPolicyNames */

class StreamIDQoSPolicy: public IntQoSPolicy {
public:
    StreamIDQoSPolicy(int value) : IntQoSPolicy(value) {

    }
    virtual ~StreamIDQoSPolicy() {

    }
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_PUBLISHER_AVB_STREAMIDQOSPOLICY_H_ */
