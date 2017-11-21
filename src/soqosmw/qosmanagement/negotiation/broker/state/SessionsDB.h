/*
 * SessionsDB.h
 *
 *  Created on: 23.10.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_STATE_SessionSDB_H_
#define SOQOSMW_STATE_SessionSDB_H_

#include "soqosmw/base/Singleton.h"
#include "soqosmw/qosmanagement/negotiation/broker/state/Session.h"
#include <vector>

namespace soqosmw {

class SessionsDB: public Singleton<SessionsDB> {
friend class Singleton <SessionsDB>;

public:
    virtual ~SessionsDB();

    /**
     * Adds the session to the database if possible.
     * @return true if added.
     */
    bool addSession (Session session);

    /**
     * Removes the session from the database if possible.
     * @return true if removed.
     */
    bool removeSession (Session session);

    /**
     * Checks if the database contains the session by checking equality of elemets.
     * @return true if database contains the session.
     */
    bool contains (Session session);

    /**
     * @return the current number of open sessions.
     */
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
