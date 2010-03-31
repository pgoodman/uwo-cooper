#include "controlunitview.h"

ControlUnitView::ControlUnitView(QWidget *parent) :QWidget(parent) {
    unit_list = new ModelListWidget<UnitModel>(this);

    QGridLayout *layout = new QGridLayout(this);
    QVBoxLayout *column = new QVBoxLayout;

    setGeometry(QRect(20, 20, 441, 231));

    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);

    column->setSpacing(0);

    move_out_button = new QPushButton("Trigger Move Out Event");
    internal_move_button = new QPushButton("Trigger Internal Move Event");

    connect(move_out_button, SIGNAL(clicked()), this, SLOT(triggerMoveOut()));
    connect(internal_move_button, SIGNAL(clicked()), this, SLOT(triggerInternalMove()));
    connect(
        unit_list, SIGNAL(itemSelectionChanged()),
        this, SLOT(activateButtons())
        );

    column->addWidget(move_out_button);
    column->addWidget(internal_move_button);

    layout->addWidget(
        new QLabel("Select a unit from the list to trigger the controls"),
        1, 1, 1, 2
    );
    layout->addWidget(unit_list, 2, 1, 1, 1);
    layout->addLayout(column, 2, 2, 1, 1);

    populateUnits();
}
ControlUnitView::~ControlUnitView() {

}

void ControlUnitView::populateUnits() {
     unit_list->fill(&UnitModel::findAll);
     move_out_button->setDisabled(true);
     internal_move_button->setDisabled(true);
}

/**
 * De/activate the various control buttons depending on the unit selected.
 */
void ControlUnitView::activateButtons() {
    UnitModel *unit(unit_list->getModel());
    if(0 == unit) {
        return;
    }
    move_out_button->setDisabled(false);
    internal_move_button->setDisabled(false);
}

/**
 * Launch the dialog to manage a move out event.
 */
void ControlUnitView::triggerMoveOut() {
    UnitModel *unit(unit_list->getModel());
    if (0 == unit) {
        return;
    }

    //TriggerMoveOutView moveOutDialog(member,this);
    //moveOutDialog.exec();
}

/**
 * Launch the dialog to manage an internal move event.
 */
void ControlUnitView::triggerInternalMove() {
    UnitModel *unit(unit_list->getModel());
    if (0 == unit) {
        return;
    }

    //TriggerInternalMoveView internalMoveDialog(member, this);
    //internalMoveDialog.exec();
}
