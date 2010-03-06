/*
 * window.cc
 *
 *  Created on: Mar 5, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "window.h"

QMainWindow *Window::main_window(0);
QLayout *Window::main_layout(0);
QWidget *Window::main_widget(0);

int Window::resize_h(0);
int Window::resize_w(0);
bool Window::do_resize(false);

QMainWindow *Window::create() {

    D( cout << "Window::create" << endl; )

    main_window = new QMainWindow;
    main_layout = new QGridLayout;

    QWidget *central_widget(new QWidget);

    central_widget->setLayout(main_layout);
    main_window->setCentralWidget(central_widget);
    return main_window;
}

void Window::setSize(int width, int height) {
    D( cout << "Window::setSize" << endl; )
    resize_w = width;
    resize_h = height;
    do_resize = true;
    //main_widget->resize(width, height);
}

void Window::setWidget(QWidget *widget) {
    D( cout << "Window::setWidget" << endl; )
    /*
    QLayout *curr(main_widget->layout());
    if(0 != curr) {
        delete curr;
    }
    main_widget->setLayout(layout);
    main_widget->repaint();
    main_window->update();*/

    if(0 != main_widget) {
        main_layout->removeWidget(main_widget);
        delete main_widget;
    }

    main_layout->addWidget(widget);
    main_widget = widget;
    if(do_resize) {
        do_resize = false;
        main_window->resize(resize_w, resize_h);
    }
    main_layout->update();
}

void Window::setDialog(QDialog *dialog) {
    dialog->setParent(main_widget);
    main_layout->update();
}

void Window::setMenuBar(QMenuBar *menuBar) {
    D( cout << "Window::setMenuBar" << endl; )
    main_window->setMenuBar(menuBar);
}

void Window::setTitle(const char *name) {
    D( cout << "Window::setTitle" << endl; )
    main_window->setWindowTitle(name);
}

QAction *Window::action(void) {
    D( cout << "Window::action" << endl; )
    return new QAction(main_window);
}
