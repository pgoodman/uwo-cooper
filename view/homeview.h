
#ifndef UI_COOPER_H
#define UI_COOPER_H

#include <Qt>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QFormLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGui>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QMessageBox>

#include "model/usermodel.h"
#include "model/membermodel.h"
#include "model/permissionmodel.h"

#include "lib/database.h"
#include "lib/gui/modellistwidget.h"
#include "lib/gui/modellistwidgetitem.h"

#include "view/addmemberview.h"
#include "view/addcommitteeview.h"

class HomeView : public QMainWindow {
    Q_OBJECT

public:
    HomeView(void);

private:

    ModelListWidget<MemberModel> *member_list;
    ModelListWidget<CommitteeModel> *committee_list;

    QPushButton *mark_button;
    QPushButton *unmark_button;
    QPushButton *del_button;
    QPushButton *edit_button;

    QWidget *makeMemberControls(void);
    QWidget *makeCommitteeControls(void);

    void makeMenuBar(void);

    void populateMembers();
    void populateCommittees();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void addMember();
    void editMember();
    void deleteMember();
    void markMember();
    void unmarkMember();

    void editCommittee() {
        cout << "show edit committee form." << endl;
    }
    void addCommittee();

    void deleteCommittee() {
        cout << "show delete committee form." << endl;
    }
    void viewCommittee() {
        cout << "show view committee." << endl;
    }
    void viewTasks() {
        cout << "show view tasks" << endl;
    }

    /**
     * Change the buttons depending on whether or not members have a
     * certain status.
     */
    void activateMemberButtons(QListWidgetItem *old, QListWidgetItem *curr);
};

#endif // UI_COOPER_H
