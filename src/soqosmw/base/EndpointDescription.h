/*
 * EndpointDescription.h
 *
 *  Created on: 23.10.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_BASE_ENDPOINTDESCRIPTION_H_
#define SOQOSMW_BASE_ENDPOINTDESCRIPTION_H_

#include "soqosmw/base/QoS_Defines.h"
#include <string>
#include "inet/networklayer/common/L3Address.h"

using namespace inet;
using namespace std;

namespace soqosmw {

class EndpointDescription {
public:
    EndpointDescription(string path, L3Address networkAddr, int networkPort) : _path(path), _networkAddr (networkAddr), _networkPort(networkPort){

    }

    EndpointDescription() {
    }

    virtual ~EndpointDescription() {
    }

    /**
     * comparing operators
     */
    inline bool operator==(const EndpointDescription& other) {
        bool value = false;
        if (_networkAddr == other.getNetworkAddr()) {
            if (_networkPort == other.getNetworkPort()) {
                if (_path == other.getPath()) {
                    value = true;
                }
            }
        }
        return value;
    }

    inline bool operator!=(const EndpointDescription& other) {
        return !(*this == other);
    }

    const L3Address& getNetworkAddr() const {
        return _networkAddr;
    }

    void setNetworkAddr(const L3Address& networkAddr) {
        _networkAddr = networkAddr;
    }

    int getNetworkPort() const {
        return _networkPort;
    }

    void setNetworkPort(int networkPort) {
        _networkPort = networkPort;
    }

    const string& getPath() const {
        return _path;
    }

    void setPath(const string& path) {
        _path = path;
    }

private:
    string _path;
    L3Address _networkAddr;
    int _networkPort;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_BASE_ENDPOINTDESCRIPTION_H_ */
