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
    setUpButton(QString("Can Add Member:"), 0);
    setUpButton(QString("Can Move Member:"), 1);
    setUpButton(QString("Can Edit Member:"), 2);
    setUpButton(QString("Can Edit Member:"), 3);
    setUpButton(QString("Can Delete Member:"), 4);
    setUpButton(QString("Can Initialize Member:"), 5);
    setUpButton(QString("Can Edit Member Committee:"), 6);
    setUpButton(QString("Can Add Committee:"), 7);
    setUpButton(QString("Can Edit Committee:"), 8);
    setUpButton(QString("Can Delete Committee:"), 9);
    setUpButton(QString("Can Print Private:"), 10);
    setUpButton(QString("Can Print Public:"), 11);
    setUpButton(QString("Can Print Committee:"), 12);
    setUpButton(QString("Can Add Task:"), 13);
    setUpButton(QString("Can Edit Task:"), 14);
    setUpButton(QString("Can Delete Task:"), 15);
    setUpButton(QString("Can Print Task:"), 16);
    setUpButton(QString("Can Add Task Spec:"), 17);
    setUpButton(QString("Can Delete Task Spec:"), 18);
    setUpButton(QString("Can Activate Task Spec:"), 19);
    setUpButton(QString("Can Edit Committee Chair:"), 20);
    setUpButton(QString("Can Edit Committee Secretary:"), 21);
    setUpButton(QString("Can View Self Info:"), 22);
    setUpButton(QString("Can View Others Info:"), 23);
    setUpButton(QString("Can Edit Self Password:"), 24);
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
