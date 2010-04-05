#include <QtGui>
#include "clock.h"

/**
 * Constructor, initialize the clock.
 */
Clock::Clock(QWidget *parent)
     : QLCDNumber(parent)
 {
    setSegmentStyle(Flat);
    setLineWidth(0);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    showTime();
    resize(30, 10);
}

/**
 * Show the time.
 */
void Clock::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0) {
        text[2] = ' ';
    }
    display(text);
 }
