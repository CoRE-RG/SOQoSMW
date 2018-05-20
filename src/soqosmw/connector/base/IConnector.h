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

#ifndef SOQOSMW_CONNENCTOR_BASE_ICONNECTOR_H_
#define SOQOSMW_CONNENCTOR_BASE_ICONNECTOR_H_

namespace soqosmw {
class SOQoSMWApplicationBase;
} /* namespace soqosmw */

namespace soqosmw {

class IConnector {
public:
    IConnector(SOQoSMWApplicationBase* executingApplication);
    virtual ~IConnector();

    bool isEnabled() const {
        return enabled;
    }

    bool isTerminated() const {
        return terminated;
    }

    void terminate() {
        setTerminated(true);
    }

    void enable(){
        setEnabled(true);
    }

    void disable(){
        setEnabled(false);
    }

    /**
     * Get the owning application.
     * @return The executing application.
     */
    virtual SOQoSMWApplicationBase* getExecutingApplication() {
        return _executingApplication;
    }

private:

    void setEnabled(bool enabled = false) {
        this->enabled = enabled;
    }

    void setTerminated(bool terminated = false) {
        this->terminated = terminated;
    }

private:
    bool terminated = false;
    bool enabled = false;

    /**
     * Owner Module of this Endpoint.
     */
    SOQoSMWApplicationBase* _executingApplication;
};

} /*end namespace soqosmw*/

#endif /* SOQOSMW_CONNENCTOR_BASE_ICONNECTOR_H_ */
