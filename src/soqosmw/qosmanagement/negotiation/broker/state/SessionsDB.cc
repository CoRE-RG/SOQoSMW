/*
 * ConnectionsDB.cpp
 *
 *  Created on: 23.10.2017
 *      Author: skrec
 */

#include "SessionsDB.h"
#include <algorithm>
using namespace std;

namespace soqosmw {

SessionsDB::~SessionsDB() {

}

SessionsDB::SessionsDB() {
}

bool SessionsDB::addSession(Session session) {
    if (!contains(session)) {
        _sessions.push_back(session);
        return true;
    }
    return false;
}

bool SessionsDB::removeSession(Session session) {
    vector<Session>::iterator it = find(session);
    if (it != _sessions.end()) {
        //it is in the list --> delete it
        _sessions.erase(it);
        return true;
    }
    return false;
}

int SessionsDB::numberOfSessions() {
    return _sessions.size();
}

bool SessionsDB::contains(Session session) {
    return find(session) != _sessions.end();
}

int SessionsDB::getIndexOf(Session session) {
    vector<Session>::iterator it = find(session);
    if (it != _sessions.end()) {
        return distance(_sessions.begin(), it);
    }

    return -1;
}

vector<Session>::iterator SessionsDB::find(Session session) {
    return std::find(_sessions.begin(), _sessions.end(), session);
}

} /* namespace soqosmw */
