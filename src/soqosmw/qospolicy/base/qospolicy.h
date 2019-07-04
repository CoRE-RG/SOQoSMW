/*
 * qospolicy.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_BASE_QOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_BASE_QOSPOLICY_H_

#include <soqosmw/qospolicy/base/IQoSPolicy.h>
#include <soqosmw/qospolicy/base/QoSPolicyFactory.h>

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

bool equalQoSMap(QoSPolicyMap& left, QoSPolicyMap& right){
    if(left.size() == right.size()){
        for(auto& elementsLeft : left){
            auto elementRight = right.find(elementsLeft.first);
            if(elementRight != right.end()){
                if(*(elementRight->second) != *(elementsLeft.second)) {
                    return false;
                }
            } else {
                return false;
            }
        }
    }

    return true;
}

} /* end namespace  */
#endif /* SOQOSMW_QOSPOLICY_BASE_QOSPOLICY_H_ */
