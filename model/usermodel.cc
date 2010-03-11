
#include "model/usermodel.h"

UserModel *UserModel::active = 0;

UserModel::UserModel(bool isCoordinator, QString &pwd)
 : is_coordinator(isCoordinator), password(pwd) { }

UserModel::~UserModel(void) { }

void UserModel::setActive(UserModel *u) {
    active = u;
}

bool UserModel::canDo(const PermissionModel p) {
    return (0 == active) ? false : active->hasPermission(p);
}

QString UserModel::getPassword(void) {
    return password;
}

void UserModel::setPassword(QString pwd){
    password = pwd;
}

bool UserModel::hasPassword(QString &pass) {
    return password == pass;
}

/**
 * Figure out whether or not someone exists with a particular user name.
 */
bool UserModel::nameExists(QString userName) {
    QSqlQuery q;
    q.prepare("SELECT id FROM user WHERE name=?");
    q << userName;
    return q.exec() && q.first();
}

