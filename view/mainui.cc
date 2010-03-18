#include "mainui.h"

MainUI::MainUI()
{
}

void MainUI::showApp(){
    delete this->centralWidget();

    HomeView *view(new HomeView);
    this->setCentralWidget(view);
    this->setFixedSize(view->size().width(),view->size().height());
    QObject::connect(view,SIGNAL(destroyed()),this,SLOT(closeMainUI()));
    QObject::connect(view,SIGNAL(userLogoff()),this,SLOT(appLogoff()));
}

//disconnect database and close main ui
void MainUI::closeMainUI(){
    Database::disconnect();
    this->close();
}

//destory main app ui and reload login ui
void MainUI::appLogoff(){
    delete this->centralWidget();

    LoginView *login = new LoginView();
    this->setCentralWidget(login);
    this->setFixedSize(login->size().width(),login->size().height());
    QObject::connect(login,SIGNAL(rejected()),this,SLOT(closeMainUI()));
    QObject::connect(login,SIGNAL(accepted()),this,SLOT(showApp()));
}
