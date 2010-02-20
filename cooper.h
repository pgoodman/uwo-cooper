#ifndef COOPER_H
#define COOPER_H

#include <QMainWindow>

namespace Ui {
    class Cooper;
}

class Cooper : public QMainWindow {
    Q_OBJECT
public:
    Cooper(QWidget *parent = 0);
    ~Cooper();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Cooper *ui;


};

#endif // COOPER_H
