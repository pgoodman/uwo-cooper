/*
 * window.h
 *
 *  Created on: Mar 5, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>

#include <QWidget>
#include <QLayout>
#include <QGridLayout>
#include <QMainWindow>
#include <QAction>
#include <QDialog>
#include <QCloseEvent>

#include "conf.h"
#include "cooperdb.h"

using namespace std;

class Window : public QMainWindow {
public:
    ~Window();
    static void setWidget(QWidget *);
    static void setDialog(QDialog *);
    static QMainWindow *create();
    static void setTitle(const char *name);
    static void setMenuBar(QMenuBar *menuBar);
    static QAction *action(void);
    static void setSize(int width, int height);
    static void close(void);

private:
    static QMainWindow *main_window;
    static QWidget *main_widget;
    static QLayout *main_layout;

    static bool do_resize;
    static int resize_h;
    static int resize_w;

    Window(QWidget *parent=0);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif /* WINDOW_H_ */
