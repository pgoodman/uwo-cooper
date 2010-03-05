/*
 * window.h
 *
 *  Created on: Mar 5, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>
#include <QLayout>
#include <QGridLayout>
#include <QMainWindow>
#include <QAction>

class Window {
public:
    static void setWidget(QWidget *layout);
    static QMainWindow *create();
    static void setTitle(const char *name);
    static void setMenuBar(QMenuBar *menuBar);
    static QAction *action(void);
    static void setSize(int width, int height);

private:
    static QMainWindow *main_window;
    static QWidget *main_widget;
    static QLayout *main_layout;

    static bool do_resize;
    static int resize_h;
    static int resize_w;

    Window(void);
};

#endif /* WINDOW_H_ */
