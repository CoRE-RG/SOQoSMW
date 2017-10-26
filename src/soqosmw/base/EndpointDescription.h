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
    EndpointDescription(){}
    virtual ~EndpointDescription(){}

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
    string      _path;
    L3Address   _networkAddr;
    int         _networkPort;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_BASE_ENDPOINTDESCRIPTION_H_ */
