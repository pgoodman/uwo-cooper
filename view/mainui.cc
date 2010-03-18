#include "mainui.h"

MainUI::MainUI()
{
    setCenter();
    connect(this,SIGNAL(logoff()),this,SLOT(appLogoff()));
    connect(this,SIGNAL(appExit()),this,SLOT(closeMainUI()));
}

void MainUI::showApp(){

    if(this->menuBar()->actions().count()!=0){
        this->menuBar()->show();
    }else{
        makeMenuBar();
    }
    delete this->centralWidget();

    HomeView *view = new HomeView();
    this->setCentralWidget(view);
    this->setFixedSize(view->size().width(),view->size().height());
    setCenter();
    //QObject::connect(view,SIGNAL(accepted()),this,SLOT(closeMainUI()));
    //QObject::connect(view,SIGNAL(userLogoff()),this,SLOT(appLogoff()));
}

//disconnect database and close main ui
void MainUI::closeMainUI(){
    Database::disconnect();
    this->close();
}

//destory main app ui and reload login ui
void MainUI::appLogoff(){
    this->menuBar()->hide();
    delete this->centralWidget();

    LoginView *login = new LoginView();
    this->setCentralWidget(login);
    this->setFixedSize(login->size().width(),login->size().height());
    setCenter();
    QObject::connect(login,SIGNAL(rejected()),this,SLOT(closeMainUI()));
    QObject::connect(login,SIGNAL(accepted()),this,SLOT(showApp()));
}

/**
 * Create the menu bar.
 */
void MainUI::makeMenuBar(void) {
    QMenu *file_menu = menuBar()->addMenu("&System");
    //(void) file_menu;
    file_menu->addAction("Logoff",this,"&logoff()");
    file_menu->addAction("Exit",this,"&appExit()");
}

void MainUI::setCenter(){
    //get current screen size
    int screenwidth = QApplication::desktop()->availableGeometry().width();
    int screenheight = QApplication::desktop()->availableGeometry().height();
    int x = (screenwidth - this->size().width()) / 2;
    int y = (screenheight - this->size().height()) / 2;
    //move the main ui to the middle
    this->move(x,y);
}
