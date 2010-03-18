
#ifndef UI_COOPER_H
#define UI_COOPER_H

#include <QMainWindow>
#include <QDialog>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>
#include <QTabWidget>

#include "lib/database.h"

#include "model/usermodel.h"
#include "model/membermodel.h"

#include "view/controlmemberview.h"
#include "view/controlcommitteeview.h"
#include "view/viewmemberview.h"

//class HomeView : public QMainWindow {
class HomeView : public QDialog {
    Q_OBJECT

public:
    HomeView(QWidget *parent = 0);

private:
    //void makeMenuBar(void);
    void setTabFormat(QTabWidget *qtab);

protected:
    //void closeEvent(QCloseEvent *event);
    //void logout();

signals:
    void userLogoff(void);

};

#endif // UI_COOPER_H
