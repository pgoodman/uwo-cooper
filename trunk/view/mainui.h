#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <QLayout>

#include "view/homeview.h"
#include "view/loginview.h"
#include "lib/database.h"
#include "lib/clock.h"

class MainUI : public QMainWindow
{
    Q_OBJECT
public:
    MainUI();

private:
    void makeMenuBar(void);
    void makeStatusBar(void);
    void setCenter(void);


signals:
    void logoff();
    void appExit();

public slots:
    void showApp(void);
    void closeMainUI(void);
    void appLogoff(void);
};

#endif // MAINUI_H
