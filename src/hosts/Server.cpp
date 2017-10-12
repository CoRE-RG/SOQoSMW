/*
 * Server.cpp
 *
 *  Created on: 05.10.2017
 *      Author: skrec
 */

#include "Server.h"

namespace hauptprojekt_timo_haeckel {

Define_Module(Server);

void Server::initialize()
{
}

void Server::handleMessage(cMessage *msg)
{
    // just send back the message we received
    cMessage * answer = new cMessage("world");
    send(answer, "out");
}

Server::Server() {
    // TODO Auto-generated constructor stub

}

Server::~Server() {
    // TODO Auto-generated destructor stub
}

}
