
#include "coordinator.h"

bool Coordinator::does_exist(false);
User *Coordinator::coord(0);

Coordinator::Coordinator(int _id, string _full_name, string _password)
 : User() {
    full_name = _full_name;
    id = _id;
    password = _password;
}

/**
 * Check if the coordinator exists.
 */
bool Coordinator::exists(void) {
    if(does_exist) {
        return true;
    }
    return does_exist = CooperDB::hasAny(
        "SELECT * FROM user WHERE is_coordinator=1"
    );
}

/**
 * Create a new coordinator in the database.
 */
void Coordinator::create(string full_name, string password) {
    assert(!Coordinator::exists());
    assert(0 == coord);
    QSqlQuery q;
    q.prepare(
        "INSERT INTO user (full_name, password, is_coordinator VALUES(?,?,1)"
    );
    q.bindValue(0, QString(full_name.c_str()));
    q.bindValue(1, QString(password.c_str()));
    if(!q.exec()) {
        CooperDB::queryError("Unable to create Coordinator", q);
    }
}

/**
 * Coordinator user name.
 */
string Coordinator::getUserName(void) {
    return string(COORDINATOR_USER_NAME);
}

/**
 * Load the coordinator from the database.
 */
User *Coordinator::load(void) {
    assert(Coordinator::exists());

    if(0 != coord) {
        return coord;
    }

    QSqlQuery r = CooperDB::select(
        "SELECT id, full_name, password FROM users "
        "WHERE is_coordinator=1 LIMIT 1"
    );

    // turn the sql record into an object
    int id = r.value(0).toInt();
    User *u = new Coordinator(
        id,
        r.value(1).toString().toStdString(),
        r.value(2).toString().toStdString()
    );

    // cache the coordinator
    users.insert(users.begin() + id, u);
    return coord = u;
}
