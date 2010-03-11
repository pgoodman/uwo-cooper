
#include "model/coordinatormodel.h"

bool CoordinatorModel::does_exist(false);
UserModel *CoordinatorModel::coord(0);

/**
 * Constructor, note: private.
 */
CoordinatorModel::CoordinatorModel(int coordId, QString pass)
 : UserModel(true, pass), id(coordId) {
}

/**
 * Destructor.
 */
CoordinatorModel::~CoordinatorModel() { }

/**
 * Check whether or not a coodinator has a permission.
 */
bool CoordinatorModel::hasPermission(const PermissionModel p) {
    (void) p;
    return true;
}

/**
 * Check if the coordinator exists.
 */
bool CoordinatorModel::exists(void) {
    return does_exist || (does_exist = Database::hasAny(
        "SELECT id FROM user WHERE is_coordinator=1"
    ));
}

/**
 * Update the coordinator in the db.
 */
void CoordinatorModel::save(void) {
    QSqlQuery q;
    q.prepare(
        "UPDATE user SET password=? WHERE id=? AND is_coordinator=1"
    );
    q << password << id;
    if(!q.exec()) {
        Database::queryError("Unable to Update Coordinator Information.", q);
    }
}

/**
 * Create a new coordinator in the database.
 */
UserModel *CoordinatorModel::create(QString password) {
    assert(!CoordinatorModel::exists());
    assert(0 == coord);
    QSqlQuery q;
    q.prepare(
        "INSERT INTO user (name, password, is_coordinator) VALUES ('"
        COORDINATOR_USER_NAME
        "',?,1)"
    );
    q << password;
    if(!q.exec()) {
        Database::queryError("Unable to create Coordinator", q);
    }
    does_exist = true;
    return load();
}

/**
 * Coordinator user name.
 */
QString CoordinatorModel::getUserName(void) {
    return QString(COORDINATOR_USER_NAME);
}

/**
 * Load the coordinator from the database.
 */
UserModel *CoordinatorModel::load(void) {
    assert(CoordinatorModel::exists());

    if(0 != coord) {
        return coord;
    }

    QSqlQuery q(Database::select("user", "is_coordinator=1"));
    int id(qcol<int>(q, "id"));
    UserModel *u = new CoordinatorModel(id, qcol<QString>(q, "password"));

    // cache the coordinator
    coord = u;
    return u;
}

/**
 * Load the coordinator with a given password, or return NULL.
 */
UserModel *CoordinatorModel::findByPassword(QString password) {
    UserModel *c = CoordinatorModel::load();
    if(c->hasPassword(password)) {
        cout << "good!" << endl;
        return c;
    }
    return 0;

}
