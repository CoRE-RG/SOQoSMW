/*
 * Session.h
 *
 *  Created on: 23.10.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_BASE_SESSION_H_
#define SOQOSMW_BASE_SESSION_H_

#include "soqosmw/base/EndpointDescription.h"
namespace soqosmw {

class Session {
public:
    Session();
    virtual ~Session();

    /**
     * comparing operators
     */
    inline bool operator==(const Session& rhs){ return true; }
    inline bool operator!=(const Session& rhs){ return !(*this == rhs); }


private:
    EndpointDescription _clientInfo;
    EndpointDescription _serverInfo;

    //QoSBrokerState _state; Create enum therefore...
    //Token?
    //time _timeout;


};

} /* namespace soqosmw */

#endif /* SOQOSMW_BASE_SESSION_H_ */
