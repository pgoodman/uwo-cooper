#ifndef COOPER_H
#define COOPER_H

#include <QMainWindow>
#include "view/ui_cooper.h"
#include "controller/usercontroller.h"

namespace Ui {
    class Cooper;
}

class Cooper : public QMainWindow {
    Q_OBJECT
public:
    Cooper(QWidget *parent = 0);
    ~Cooper();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Cooper *ui;

private slots:
    void on_actionAbout_Cooper_triggered();
    void on_actionManual_triggered();
    void on_actionTask_List_triggered();
    void on_actionCommittee_List_triggered();
    void on_actionPhone_List_triggered();
    void on_actionAnnual_Task_Spec_triggered();
    void on_actionInternal_Move_triggered();
    void on_actionMove_Out_triggered();
    void on_actionDelete_Task_triggered();
    void on_actionEdit_Task_triggered();
    void on_actionAssign_Task_triggered();
    void on_actionDelete_Committee_triggered();
    void on_actionAdd_Committee_triggered();
    void on_actionDelete_Member_triggered();
    void on_actionEdit_Member_triggered();
    void on_actionAdd_Member_triggered();
    void on_actionLogoff_triggered();
};

#endif // COOPER_H
