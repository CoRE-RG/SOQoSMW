//
// c Timo Haeckel for HAW Hamburg
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

#ifndef SOQOSMW_QOSPOLICY_BASE_TYPES_UINT16QOSPOLICY_H_
#define SOQOSMW_QOSPOLICY_BASE_TYPES_UINT16QOSPOLICY_H_

#include "soqosmw/qospolicy/base/IQoSPolicy.h"

#include <cstdint>

namespace soqosmw {

/**
 * @brief The UInt16QoSPolicy.
 *
 * @ingroup soqosmw/qospolicy
 *
 * @author Timo Haeckel for HAW Hamburg
 */
class UInt16QoSPolicy: public IQoSPolicy {
public:
    UInt16QoSPolicy(uint16_t value) : _value(value) {

    }
    virtual ~UInt16QoSPolicy(){

    }

    const uint16_t getValue() const {
        return _value;
    }

    virtual bool operator==(IQoSPolicy& other){
        UInt16QoSPolicy& real = static_cast<UInt16QoSPolicy&> (other);
        return real._value == _value;
    }

private:
    const uint16_t _value;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_QOSPOLICY_BASE_TYPES_UINT16QOSPOLICY_H_ */
