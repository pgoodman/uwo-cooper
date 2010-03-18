#include "mainui.h"

MainUI::MainUI()
{
    this->setWindowTitle("UWO COOPER");
    //this->setWindowOpacity(0.8);
    setCenter();

    font.setPointSize(8);
    font.setBold(true);

    makeStatusBar();

    connect(this,SIGNAL(logoff()),this,SLOT(appLogoff()));
    connect(this,SIGNAL(appExit()),this,SLOT(closeMainUI()));

}

void MainUI::showApp(){

    if(this->menuBar()->actions().count()!=0){
        this->menuBar()->show();
    }else{
        makeMenuBar();
    }

    userstatus = new QLabel("Logged in User:   " + active_user->getUserName());
    userstatus->setFont(font);
    //userstatus->setAutoFillBackground(true);

    statusBar()->addWidget(userstatus);
    statusBar()->show();

    delete this->centralWidget();

    HomeView *view = new HomeView();

    this->setCentralWidget(view);
    int uiwidth = view->size().width();
    int uiheight = view->size().height() + this->statusBar()->height() + this->menuBar()->height() + 5;
    this->setFixedSize(uiwidth,uiheight);
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
    this->statusBar()->hide();
    this->statusBar()->removeWidget(userstatus);

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
    QMenu *help_menu = menuBar()->addMenu("&Help");
    //(void) file_menu;
    file_menu->addAction("Logoff",this,"&logoff()");
    file_menu->addAction("Exit",this,"&appExit()");

   QAction *a= help_menu->addAction("Manual");
    help_menu->addAction("About COOPER");
   a->setIcon(QIcon("../images/help_icon.gif"));
}


void MainUI::setCenter(){
    //get current screen size
    int screenwidth = QApplication::desktop()->availableGeometry().width();
    int screenheight = QApplication::desktop()->availableGeometry().height();
    int x = (screenwidth - this->size().width()) / 2;
    int y = (screenheight - this->size().height()) / 2;
    //move the main ui to the middle
    this->move(x,y);

    //set background image
    QPalette palette;
    QPixmap bgimage;
    //QImage image = QImage(QString("../images/mainbg.jpg"));
    //image.scaled();

    //bgimage.fromImage(image);
    bgimage = QPixmap(QString("../images/mainbg.jpg"));
    bgimage = bgimage.scaled(this->size(),Qt::IgnoreAspectRatio);
    //bgimage.scaledToWidth(this->size().width());
    //bgimage.scaledToHeight(this->size().height());
    palette.setBrush(QPalette::Window,bgimage);
    this->setPalette(palette);
    this->setAutoFillBackground(true);

}

void MainUI::makeStatusBar(){

    statusBar()->setStyleSheet("QStatusBar {"
                               "background: lightgrey;"
                               "border-top: 2px groove #979797;}"
                               //"border-top-left-radius: 4px;"
                               //"border-top-right-radius: 4px;}"
                               "QStatusBar::item {"
                               "border: 0px solid black;"
                               "border-radius: 3px;}");
    statusBar()->setSizeGripEnabled(false);

    //add a clock widget to the far right
    Clock *clock = new Clock();
    statusBar()->addPermanentWidget(clock);
}
