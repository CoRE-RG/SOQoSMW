/*
 * QoSGroup.h
 *
 *  Created on: 19.12.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSPOLICY_MANAGEMENT_QOSGROUP_H_
#define SOQOSMW_QOSPOLICY_MANAGEMENT_QOSGROUP_H_

#include <qospolicy/base/types/IntQoSPolicy.h>

#include <soqosmw/messages/QoSNegotiationProtocol/QoSNegotiationProtocol_m.h>

namespace soqosmw {

namespace QoSPolicyNames {

const std::string QoSGroup = "QoSGroup"; //one of enum WEB, STD, RT

} /* namespace QoSPolicyNames */


class QoSGroup: public IQoSPolicy {
public:

    QoSGroup(QoSGroups value) : _value (value){

    }
    virtual ~QoSGroup(){

    }

    const QoSGroups getValue(){
        return _value;
    }

    virtual bool operator==(IQoSPolicy& other){
        QoSGroup& real = static_cast<QoSGroup&> (other);
        return real._value == _value;
    }

private:
    const QoSGroups _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_MANAGEMENT_QOSGROUP_H_ */
