

#include <QApplication>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDialog>

#include "conf.h"

#include "lib/database.h"
#include "lib/criticalerror.h"
#include "lib/maybe.h"

#include "controller/setupcontroller.h"
#include "controller/usercontroller.h"

#include "model/permissionmodel.h"

using namespace std;

/**
 * Install database tables.
 */
static void install_tables(QSqlQuery &q) {

    const char table_names[][20] = {
#include "sql/tablenames.conf"
    };
    const char tables[][500] = {
#include "sql/tabledefs.conf"
    };

    size_t num_tables = sizeof(table_names) / sizeof(table_names[0]);
    D( cout << "Num Tables: " << num_tables << endl; )
    stringstream error;

    for(; num_tables--; ) {
        if(!q.exec(tables[num_tables])) {
            error << "Error creating table '"
                  << table_names[num_tables]
                  << "'.";
            Database::queryError(error, q);
        }
    }
}

/**
 * Install default committees into the database.
 */
static void install_committees(QSqlQuery &q) {
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
}


/**
 * Install the database.
 */
static void install_database(QSqlQuery &q) {
    install_tables(q);
    install_committees(q);
}

/**
 * Run the program.
 */
int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    /*try {*/
    Database::connect(DATABASE_FILE, DATABASE_DRIVER, &install_database);

    int go;
    if(!CoordinatorModel::exists() || !UnitModel::exists()) {
        go = SetupController::install();
        cout << "Installed" << endl;
    } else {
        go = UserController::login();
        cout << "Logged in." << endl;
    }

    if(QDialog::Accepted == go) {
        UserController::home();
    }

    return app.exec();

    /*
    } catch(CriticalError &e) {
        cout << "Error: " << e.header() << endl << e.what() << endl;
        QMessageBox::critical(
            0,
            QString(e.header()),
            QString(e.what()),
            QMessageBox::Cancel
        );
        return 0;
    } catch(...) {
        cout << "Unkown Error Occured." << endl;
        return 0;
    }*/
}
