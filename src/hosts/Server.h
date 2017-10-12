/*
 * Server.h
 *
 *  Created on: 05.10.2017
 *      Author: skrec
 */

#ifndef HOSTS_SERVER_H_
#define HOSTS_SERVER_H_

#include "Host.h"

namespace hauptprojekt_timo_haeckel {

class Server: public Host {
public:
    Server();
    virtual ~Server();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}; // namespace

#endif /* HOSTS_SERVER_H_ */
