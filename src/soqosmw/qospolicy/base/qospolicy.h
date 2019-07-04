/*
 * qospolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_BASE_QOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_BASE_QOSPOLICY_H_

#include <soqosmw/qospolicy/base/IQoSPolicy.h>

#include <soqosmw/qospolicy/base/types/DoubleQoSPolicy.h>
#include <soqosmw/qospolicy/base/types/IntQoSPolicy.h>
#include <soqosmw/qospolicy/base/types/SizeQoSPolicy.h>
#include <soqosmw/qospolicy/base/types/StringQoSPolicy.h>
#include <soqosmw/qospolicy/base/types/UInt16QoSPolicy.h>

#include <soqosmw/qospolicy/avb/FramesizeQoSPolicy.h>
#include <soqosmw/qospolicy/avb/IntervalFramesQoSPolicy.h>
#include <soqosmw/qospolicy/avb/SRClassQoSPolicy.h>
#include <soqosmw/qospolicy/avb/StreamIDQoSPolicy.h>

#include <soqosmw/qospolicy/management/QoSGroup.h>

#include <soqosmw/qospolicy/std/LocalAddressQoSPolicy.h>
#include <soqosmw/qospolicy/std/LocalPortQoSPolicy.h>

#include <string>
#include <unordered_map>


namespace soqosmw {
typedef std::unordered_map<std::string, IQoSPolicy*> QoSPolicyMap;

/**
 * This function checks if the policies in the left and right map are equal.
 * @param left      one policy list
 * @param right     the other policy list
 * @return          left == right
 */
bool equalQoSMap(QoSPolicyMap& left, QoSPolicyMap& right);

} /* end namespace  */
#endif /* SOQOSMW_QOSPOLICY_BASE_QOSPOLICY_H_ */
