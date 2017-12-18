//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SOQOSMW_QOSPOLICY_GROUP_QOSGROUP_H_
#define SOQOSMW_QOSPOLICY_GROUP_QOSGROUP_H_

#include <qospolicy/base/IQoSPolicy.h>

namespace soqosmw {

enum QoSGroups {
    WEB, STD, RT
};

const std::string QoSGroup_NAME = "QoSGroup";

class QoSGroup: public soqosmw::IQoSPolicy {
public:
    QoSGroup(QoSGroups group);
    virtual ~QoSGroup();

    static const std::string& getName(){
        return QoSGroup_NAME;
    }

    QoSGroups getGroup() const {
        return _group;
    }

private:
    QoSGroups _group;
};

}/* end namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_GROUP_QOSGROUP_H_ */
