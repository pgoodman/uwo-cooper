#include "lib/gui/permlistwidget.h"



PermListWidget::PermListWidget(QWidget *parent)
    : QScrollArea(parent)
{
}

PermListWidget::PermListWidget(QString name, PermissionModelSet list, QWidget *parent)
    : QScrollArea(parent)
{
    boxGroup = new QGroupBox(name);
    this->list = list;
    setUpLayout();
}

void PermListWidget::setUpLayout()
{
    layout = new QGridLayout;
    setUpRadioButtons();

    boxGroup->setLayout(layout);
    setWidget(boxGroup);
}

void PermListWidget::setUpRadioButtons()
{
    setUpButton(QString("Add Member Permission?:"), 0);
    setUpButton(QString("Move Member Permission?:"), 1);
    setUpButton(QString("Edit Member Permission?:"), 2);
    setUpButton(QString("Edit Member Status Permission?:"), 3);
    setUpButton(QString("Delete Member Permission?:"), 4);
    setUpButton(QString("Initialize Member Committee Permission?:"), 5);
    setUpButton(QString("Edit Member Committee Permission?:"), 6);
    setUpButton(QString("Add Committee Permission?:"), 7);
    setUpButton(QString("Edit Committee Permission?:"), 8);
    setUpButton(QString("Delete Committee Permission?:"), 9);
    setUpButton(QString("Print Private ListPermission?:"), 10);
    setUpButton(QString("Print Public ListPermission?:"), 11);
    setUpButton(QString("Print Committee List Permission?:"), 12);
    setUpButton(QString("Add Task Permission?:"), 13);
    setUpButton(QString("Edit Task Permission?:"), 14);
    setUpButton(QString("Delete Task Permission?:"), 15);
    setUpButton(QString("Print Task List Permission?:"), 16);
    setUpButton(QString("Add Task Spec Permission?:"), 17);
    setUpButton(QString("Delete Task Spec Permission?:"), 18);
    setUpButton(QString("Activate Task Spec Permission?:"), 19);
    setUpButton(QString("Edit Committee Chair Permission?:"), 20);
    setUpButton(QString("Edit Committee Secretary Permission?:"), 21);
    setUpButton(QString("View Self Info Permission?:"), 22);
    setUpButton(QString("View Others Info Permission?:"), 23);
    setUpButton(QString("Edit Self Password Permission?:"), 24);
}

void PermListWidget::setUpButton(QString name, int permNum)
{
    QLabel *label = new QLabel(name);
    QRadioButton *no = new QRadioButton("No");
    QButtonGroup *buttonGroup(new QButtonGroup);

   options.push_back(new QRadioButton("Yes"));

   buttonGroup->addButton(options[permNum]);
   buttonGroup->addButton(no);

   if((list & 1 << permNum) != 0)
   {
       options[permNum]->setChecked(true);
   }
   else
   {
       no->setChecked(true);
   }

   layout->addWidget(label, permNum, 0);
   layout->addWidget(options[permNum], permNum, 1);
   layout->addWidget(no, permNum, 2);
}

PermissionModelSet PermListWidget::getPermissions()
{
    PermissionModelSet result = 0;

    for(int i = 0; i < (int)options.size(); i++)
    {
        if(options[i]->isChecked())
        {
            result |= 1 << i;
        }
    }

    return result;
}

PermListWidget::~PermListWidget()
{
    delete layout;
    delete boxGroup;
    options.clear();
}