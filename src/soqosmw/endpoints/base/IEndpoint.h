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

#ifndef SOQOSMW_ENDPOINTS_BASE_IENDPOINT_H_
#define SOQOSMW_ENDPOINTS_BASE_IENDPOINT_H_

#include <string>

namespace soqosmw {

class IEndpoint {
public:
    IEndpoint(std::string path);
    virtual ~IEndpoint();

    const std::string& getPath() const {
        return _path;
    }

    void setPath(const std::string& path) {
        _path = path;
    }

private:
    std::string _path;
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_ENDPOINTS_BASE_IENDPOINT_H_ */
