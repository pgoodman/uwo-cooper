#ifndef CONTROLUNITVIEW_H
#define CONTROLUNITVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>

#include "lib/gui/modellistwidget.h"

#include "model/unitmodel.h"

#include "view/triggermoveoutview.h"
#include "view/triggerinternalmoveview.h"

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
