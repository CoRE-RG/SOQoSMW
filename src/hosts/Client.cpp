/*
 * Client.cpp
 *
 *  Created on: 05.10.2017
 *      Author: skrec
 */

#include "Client.h"

namespace hauptprojekt_timo_haeckel {

Define_Module(Client);

Client::Client() {
    // TODO Auto-generated constructor stub

}

void Client::initialize()
{
    cMessage *msg = new cMessage("hello");
    send(msg, "out");
}


void Client::handleMessage(cMessage *msg)
{
}

Client::~Client() {
    // TODO Auto-generated destructor stub
}

}
