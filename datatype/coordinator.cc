
#include "coordinator.h"

bool Coordinator::does_exist(false);
User *Coordinator::coord(0);

/**
 * Constructor, note: private.
 */
Coordinator::Coordinator(int _id, QString _password)
 : User() {
    id = _id;
    password = _password;
}

/**
 * Destructor.
 */
Coordinator::~Coordinator() { }

/**
 * Check whether or not a coodinator has a permission.
 */
bool Coordinator::hasPermission(const Permission p) {
    (void) p;
    return true;
}

/**
 * Check if the coordinator exists.
 */
bool Coordinator::exists(void) {
    if(does_exist) {
        return true;
    }
    return does_exist = CooperDB::hasAny(
        "SELECT id FROM user WHERE is_coordinator=1"
    );
}

/**
 * Update the coordinator in the db.
 */
void Coordinator::save(void) {
    QSqlQuery q;
    q.prepare(
        "UPDATE user SET password=? WHERE id=? AND is_coordinator=1"
    );
    q << password << id;
    if(!q.exec()) {
        CooperDB::queryError("Unable to Update Coordinator Information.", q);
    }
}

/**
 * Create a new coordinator in the database.
 */
User *Coordinator::create(QString password) {
    assert(!Coordinator::exists());
    assert(0 == coord);
    QSqlQuery q;
    q.prepare(
        "INSERT INTO user (name, password, is_coordinator VALUES('"
        COORDINATOR_USER_NAME
        "',?,1)"
    );
    q << password;
    if(!q.exec()) {
        CooperDB::queryError("Unable to create Coordinator", q);
    }
    return load();
}

/**
 * Coordinator user name.
 */
QString Coordinator::getUserName(void) {
    return QString(COORDINATOR_USER_NAME);
}

/**
 * Load the coordinator from the database.
 */
User *Coordinator::load(void) {
    assert(Coordinator::exists());

    if(0 != coord) {
        return coord;
    }

    QSqlQuery q = CooperDB::select(
        "SELECT id, password FROM user "
        "WHERE is_coordinator=1 LIMIT 1"
    );

    // turn the sql record into an object
    int id(qcol<int>(q, "id"));
    User *u = new Coordinator(
        id,
        qcol<QString>(q, "password")
    );

    // cache the coordinator
    User::remember(id, u);
    return coord = u;
}

/**
 * Load the coordinator with a given password, or return NULL.
 */
User *Coordinator::load(QString password) {
    User *c = Coordinator::load();
    if(c->hasPassword(password)) {
        return c;
    }
    return 0;

}
