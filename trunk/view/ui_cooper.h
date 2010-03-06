
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

#include "datatype/user.h"
#include "datatype/member.h"
#include "datatype/permission.h"
#include "cooperdb.h"
#include "ui_addmember.h"

#include "modellist.h"
#include "modellistitem.h"

#include "window.h"

class Ui_Cooper : public QWidget {

    Q_OBJECT

public:

    Ui_Cooper(void);

private:

    ModelList<Member> *member_list;
    ModelList<Committee> *committee_list;

    QPushButton *mark_button;
    QPushButton *unmark_button;
    QPushButton *del_button;
    QPushButton *edit_button;

    QWidget *makeMemberControls(void);
    QWidget *makeCommitteeControls(void);

    void makeMenuBar(void);

    void populateMembers();
    void populateCommittees();

public slots:
    void addMember();
    void editMember();
    void deleteMember();
    void markMember();
    void unmarkMember();

    void editCommittee() {
        cout << "show edit committee form." << endl;
    }
    void addCommittee() {
        cout << "show add committee form." << endl;
    }
    void deleteCommittee() {
        cout << "show delete committee form." << endl;
    }
    void viewCommittee() {
        cout << "show view committee." << endl;
    }

    /**
     * Change the buttons depending on whether or not members have a certain
     * status.
     */
    void activateMemberButtons(QListWidgetItem *old, QListWidgetItem *curr);
};


#endif // UI_COOPER_H
