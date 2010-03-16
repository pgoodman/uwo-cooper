#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#define PHONE_LIST_PUBLIC   1
#define PHONE_LIST_ALL      2
#define COMMITTEE_LIST      3
#define TASK_LIST           4

#include <QTextDocument>
#include <QTextCursor>
#include <QMessageBox>
#include <QTextTable>

#include "lib/imodel.h"
#include "model/member_committee_models.h"
#include "controller/printcontroller.h"
#include "view/controlcommitteeview.h"
#include "model/taskmodel.h"


class DocumentModel : public QTextDocument
{
public:
    DocumentModel(int doctype);
    DocumentModel(int doctype, int sort);
    DocumentModel(int doctype, CommitteeModel *committee);
    ~DocumentModel();

private:
    QTextCursor *cursor;


    void generatePhoneList(bool isconfidential, int sort = SORT_BY_LASTNAME);
    void generateCommitteeList(void);
    void generateTaskList(CommitteeModel *committee);


};

#endif // DOCUMENTMODEL_H
