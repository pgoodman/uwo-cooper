
#include "view/permlistview.h"

PermListView::PermListView(QWidget *parent)
    : QScrollArea(parent)
{
}

PermListView::PermListView(QString name, PermissionModelSet list, QWidget *parent)
    : QScrollArea(parent)
{
    boxGroup = new QGroupBox(name);
    this->list = list;
    setUpLayout();
}

void PermListView::setUpLayout()
{
    layout = new QGridLayout;
    setUpRadioButtons();

    boxGroup->setLayout(layout);
    setWidget(boxGroup);
}

void PermListView::setUpRadioButtons()
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
    setUpButton(QString("Can Add Self Committe Task:"), 13);
    setUpButton(QString("Can Edit Self Committe Task:"), 14);
    setUpButton(QString("Can Delete Self Committe Task:"), 15);
    setUpButton(QString("Can Print Self Committe Task:"), 16);
    setUpButton(QString("Can Add Self Committe Task Spec:"), 17);
    setUpButton(QString("Can Delete Self Committe Task Spec:"), 18);
    setUpButton(QString("Can Activate Self Committe Task Spec:"), 19);
    setUpButton(QString("Can Edit Committee Chair:"), 20);
    setUpButton(QString("Can Edit Committee Secretary:"), 21);
    setUpButton(QString("Can View Self Info:"), 22);
    setUpButton(QString("Can View Others Info:"), 23);
    setUpButton(QString("Can Edit Self Password:"), 24);
    setUpButton(QString("Can Add Task:"), 25);
    setUpButton(QString("Can Edit Task:"), 26);
    setUpButton(QString("Can Delete Task:"), 27);
    setUpButton(QString("Can Print Task:"), 28);
    setUpButton(QString("Can Add Task Spec:"), 29);
    setUpButton(QString("Can Delete Task Spec:"), 30);
    setUpButton(QString("Can Activate Task Spec:"), 31);
}

void PermListView::setUpButton(QString name, int permNum)
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

PermissionModelSet PermListView::getPermissions()
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

PermListView::~PermListView()
{
    delete layout;
    delete boxGroup;
    options.clear();
}
