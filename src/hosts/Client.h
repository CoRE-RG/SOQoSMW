/*
 * Client.h
 *
 *  Created on: 05.10.2017
 *      Author: skrec
 */

#ifndef HOSTS_CLIENT_H_
#define HOSTS_CLIENT_H_

#include "Host.h"

namespace hauptprojekt_timo_haeckel {

class Client: public Host {
public:
    Client();
    virtual ~Client();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}; // namespace

#endif /* HOSTS_CLIENT_H_ */
