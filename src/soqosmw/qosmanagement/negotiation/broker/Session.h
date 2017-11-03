/*
 * Session.h
 *
 *  Created on: 23.10.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_BASE_SESSION_H_
#define SOQOSMW_BASE_SESSION_H_

#include "soqosmw/base/EndpointDescription.h"
#include "QoSBroker.h"
namespace soqosmw {

class Session {
public:
    Session();
    virtual ~Session();

    /**
     * comparing operators
     */
    inline bool operator==(const Session& other){
        bool value = false;

        if(_serverInfo == other.getServerInfo()) {
            if(_clientInfo == other.getClientInfo()){
                value = true;
            }
        }

        return value;
    }

    inline bool operator!=(const Session& other){ return !(*this == other); }

    QoSBrokerStates_t getBrokerState() const {
        return _brokerState;
    }

    void setBrokerState(QoSBrokerStates_t brokerState) {
        _brokerState = brokerState;
    }

    const EndpointDescription& getClientInfo() const {
        return _clientInfo;
    }

    void setClientInfo(const EndpointDescription& clientInfo) {
        _clientInfo = clientInfo;
    }

    const EndpointDescription& getServerInfo() const {
        return _serverInfo;
    }

    void setServerInfo(const EndpointDescription& serverInfo) {
        _serverInfo = serverInfo;
    }

private:
    EndpointDescription _clientInfo;
    EndpointDescription _serverInfo;

    QoSBrokerStates_t _brokerState;

    //Token? --> later with security update.
    //time _timeout; --> later with security update.
};

} /* namespace soqosmw */

#endif /* SOQOSMW_BASE_SESSION_H_ */
