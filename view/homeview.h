
#ifndef UI_COOPER_H
#define UI_COOPER_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>

#include "lib/database.h"

#include "model/usermodel.h"
#include "model/membermodel.h"

#include "view/controlmemberview.h"
#include "view/controlcommitteeview.h"
#include "view/viewmemberview.h"

class HomeView : public QMainWindow {
    Q_OBJECT

public:
    HomeView(void);

private:
    void makeMenuBar(void);

protected:
    void closeEvent(QCloseEvent *event);
    void logout();

};

#endif // UI_COOPER_H
