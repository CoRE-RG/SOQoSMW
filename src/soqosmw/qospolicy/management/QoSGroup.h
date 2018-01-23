/*
 * QoSGroup.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_MANAGEMENT_QOSGROUP_H_
#define SOQOSMW_QOSPOLICY_MANAGEMENT_QOSGROUP_H_

#include <qospolicy/base/types/IntQoSPolicy.h>

namespace soqosmw {

namespace QoSPolicyNames {

const std::string QoSGroup = "QoSGroup"; //one of enum WEB, STD, RT

} /* namespace QoSPolicyNames */


class QoSGroup: public IQoSPolicy {
public:

    typedef enum QoSGroups{
        WEB, STD, RT
    }QoSGroups_t;

    QoSGroup(QoSGroups_t value) : _value (value){

    }
    virtual ~QoSGroup(){

    }

    const QoSGroups_t getValue(){
        return _value;
    }

private:
    const QoSGroups_t _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_MANAGEMENT_QOSGROUP_H_ */
