/*
 * SessionsDB.h
 *
 *  Created on: 23.10.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_STATE_SessionSDB_H_
#define SOQOSMW_STATE_SessionSDB_H_

#include "soqosmw/base/Singleton.h"
#include "soqosmw/base/Session.h"
#include <vector>

namespace soqosmw {

class SessionsDB: public Singleton<SessionsDB> {
friend class Singleton <SessionsDB>;

public:
    virtual ~SessionsDB();

    bool addSession (Session session);
    bool removeSession (Session session);
    bool contains (Session session);

    int numberOfSessions();

protected:
    SessionsDB();


private:
    int getIndexOf(Session session);
    std::vector<Session>::iterator find(Session session);

    std::vector<Session> _sessions;
};

} /* namespace soqosmw */

#endif /* SOQOSMW_STATE_SessionSDB_H_ */
