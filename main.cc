
#include <iostream>

#include <QApplication>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDialog>
#include <QMainWindow>

#include "conf.h"

#include "lib/database.h"

#include "controller/setupcontroller.h"
#include "controller/usercontroller.h"

#include "model/permissionmodel.h"

using namespace std;

/**
 * Install database tables.
 */
static bool install_tables(QSqlQuery &q) {

    const char table_names[][20] = {
#include "sql/tablenames.conf"
    };
    const char tables[][500] = {
#include "sql/tabledefs.conf"
    };

    size_t num_tables = sizeof(table_names) / sizeof(table_names[0]);
    stringstream error;

    for(size_t i(0); i < num_tables; ++i) {
        if(!q.exec(tables[i])) {
            return false;
        }
    }
    return true;
}

/**
 * Install default committees into the database.
 */
static bool install_committees(QSqlQuery &q) {
    PermissionModelSet chair_perms(0
        | EDIT_COMMITTEE_CHAIR
        | EDIT_COMMITTEE_SECRETARY
        | ADD_TASK
        | PRINT_TASK_LIST
    );
    PermissionModelSet member_perms(0
        | PRINT_PUBLIC_LIST
        | PRINT_COMMITTEE_LIST
    );
    PermissionModelSet education_chair_perms(chair_perms
        | INIT_MEMBER_COMMITTEE
    );

    // chair can: everything
    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Board',0,?,33554431)"
    );
    q << member_perms;
    q.exec();

    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Inspections',0,?,?)"
    );
    q << member_perms << chair_perms;
    q.exec();

    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Membership',0,?,?)"
    );
    q << member_perms << chair_perms;
    q.exec();

    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Education',0,?,?)"
    );
    q << member_perms << education_chair_perms;
    q.exec();

    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Member Relations',0,?,?)"
    );
    q << member_perms << chair_perms;
    q.exec();
    return true;
}


/**
 * Install the database.
 */
static bool install_database(QSqlQuery &q) {
    return install_tables(q) && install_committees(q);
}

/**
 * Run the program.
 */
int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    if(!Database::connect(DATABASE_FILE, DATABASE_DRIVER, &install_database)) {
        QMessageBox::critical(0,
            "Unable to conntect to the database",
            "Unable to conntect to the database"
        );
    }

    int go;
    if(!CoordinatorModel::exists() || !UnitModel::exists()) {
        go = SetupController::install();
    } else {
        go = UserController::login();
    }

    if(QDialog::Accepted == go) {
        UserController::home();
    } else {
        Database::disconnect();
    }

    return app.exec();
}
