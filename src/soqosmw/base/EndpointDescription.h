/*
 * EndpointDescription.h
 *
 *  Created on: 23.10.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_BASE_ENDPOINTDESCRIPTION_H_
#define SOQOSMW_BASE_ENDPOINTDESCRIPTION_H_

#include <string>

#include <inet/networklayer/common/L3Address.h>

namespace soqosmw {

/**
 * @brief This class describes an Endpoint for soqosmw messages.
 *
 * @ingroup soqosmw/base
 *
 * @author Timo Haeckel
 */
class EndpointDescription {
public:
    EndpointDescription(std::string path, inet::L3Address networkAddr, int networkPort) : _path(path), _networkAddr (networkAddr), _networkPort(networkPort){

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

    const inet::L3Address& getNetworkAddr() const {
        return _networkAddr;
    }

    void setNetworkAddr(const inet::L3Address& networkAddr) {
        _networkAddr = networkAddr;
    }

    int getNetworkPort() const {
        return _networkPort;
    }

    void setNetworkPort(int networkPort) {
        _networkPort = networkPort;
    }

    const std::string& getPath() const {
        return _path;
    }

    void setPath(const std::string& path) {
        _path = path;
    }

private:
    /**
     * The name of the Endpoint as a path.
     */
    std::string _path;

    /**
     * The network address of the node running the Endpoint.
     */
    inet::L3Address _networkAddr;

    /**
     * The network port of the Endpoint.
     */
    int _networkPort;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_BASE_ENDPOINTDESCRIPTION_H_ */
