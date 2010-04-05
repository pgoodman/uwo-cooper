#ifndef CLOCK_H
#define CLOCK_H

#include <QLCDNumber>

/**
 * An LCD clock.
 */
class Clock : public QLCDNumber
{
    Q_OBJECT
public:
    Clock(QWidget *parent = 0);

private slots:
    void showTime();
};

#endif // CLOCK_H
