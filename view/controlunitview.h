#ifndef CONTROLUNITVIEW_H
#define CONTROLUNITVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "lib/gui/modellistwidget.h"

#include "model/usermodel.h"
#include "model/membermodel.h"
#include "model/permissionmodel.h"

#include "view/addmemberview.h"
#include "view/editmemberview.h"
#include "view/triggermoveoutview.h"
#include "view/triggerinternalmoveview.h"
#include "view/dependantlistview.h"
#include "controller/printcontroller.h"
#include "model/documentmodel.h"

class ControlUnitView : public QWidget
{
    Q_OBJECT
public:
    ControlUnitView(QWidget *parent = 0);
    ~ControlUnitView();

public slots:
    void triggerMoveOut();
    void triggerInternalMove();
    void activateButtons();

private:
    ModelListWidget<UnitModel> *unit_list;
    QPushButton *move_out_button;
    QPushButton *internal_move_button;

    void populateUnits();
};

#endif // CONTROLUNITVIEW_H
