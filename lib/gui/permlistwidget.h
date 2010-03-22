#ifndef PERMLISTWIDGET_H
#define PERMLISTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QRadioButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QLabel>

#include <vector>

#include "model/permissionmodel.h"

using namespace std;

class PermListWidget : public QScrollArea{
Q_OBJECT
public:
    PermListWidget(QWidget *parent = 0);
    PermListWidget(QString name, QWidget *parent = 0);

    int getPerm(int perm);

    ~PermListWidget();

private:
       void setUpRadioButtons();
       void setUpButton(QString name, int permNum);
       void setUpLayout();

       QGridLayout *layout;
       QGroupBox *boxGroup;
       vector<QRadioButton *> options;

};


#endif // PERMLISTWIDGET_H
