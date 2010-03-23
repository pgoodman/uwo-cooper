#include "documentmodel.h"

DocumentModel::DocumentModel(int doctype){

    //cursor = new QTextCursor(this);

    switch(doctype){

    case PHONE_LIST_PUBLIC:
        generatePhoneList(false);
        break;
    case PHONE_LIST_ALL:
        generatePhoneList(true);
        break;
    case COMMITTEE_LIST:
        generateCommitteeList();
        break;
    case TASK_LIST:
        generateTaskList(0);
        break;
    }
}
//generate document with sorting
//valid for phone list only
DocumentModel::DocumentModel(int doctype, int sort){

    if(doctype == PHONE_LIST_PUBLIC) {
        generatePhoneList(false, sort);
    }else if(doctype == PHONE_LIST_ALL) {
        generatePhoneList(true, sort);
    }else {}
}
DocumentModel::DocumentModel(int doctype, CommitteeModel *committee){
    if(doctype == TASK_LIST){
        generateTaskList(committee);
    }else {
        generateCommitteeList();
    }
}

DocumentModel::~DocumentModel(){

}

void DocumentModel::generatePhoneList(bool isconfidential, int sort){

    QString html;

    html.append("<p><b>MEMBER PHONE LIST</b></p><br />");
    html.append("NOTE: Contacts listed in italic are under 21 years old living with the nearest member above");
    html.append("<table border=0 cellpadding=10>");
    html.append("<tr><td align=""left""><b>Name</b></td><td align=""left""><b>Unit</b></td><td align=""left""><b>Phone Number</b></td></tr>");

    const char *cond;
    if (sort == SORT_BY_LASTNAME) {
        cond = "1=1 ORDER BY last_name ASC";
    }else if(sort == SORT_BY_UNIT){
        cond = "1=1 ORDER BY unit_id ASC";
    }else{
        cond = "1=1";
    }


    MemberModel::iterator_range itr = MemberModel::findAll(cond);
    MemberModel::iterator it = itr.first;
    MemberModel::iterator end = itr.second;

    int membercount;
    QString cell1;
    QString cell2;
    QString cell3;
    for(membercount = 0; it != end; it++){
        membercount++;
        MemberModel *m = *it;
        if(!m->isMarkedDeleted()){
            if(isconfidential ||  m->isTelephoneShared()){
                cell1 = "";
                cell2 = "";
                cell3 = "";
                cell1.append("<td>" + m->getLastName() + "," + m->getFirstName() + "</td>");
                cell2.append("<td>" + QString::number(m->findUnit()->id) + "-" + m->findUnit()->address + "</td>");
                cell3.append("<td>" + m->getTelephoneNum() + "</td>");
                html.append("<tr>" + cell1 + cell2 + cell3 + "</tr>");
            }
            DependantModel::iterator_range ditr = m->findDependants();
            DependantModel::iterator dit = ditr.first;
            DependantModel::iterator dend = ditr.second;
            for(; dit != dend; dit++){
                DependantModel *d = *dit;
                cell1 = "";
                cell2 = "";
                cell3 = "";
                cell1.append("<td><i>" + d->getName() + "</i></td>");
                cell2.append("<td><i>" + QString::number(m->findUnit()->id) + "-" + m->findUnit()->address + "</i></td>");
                cell3.append("<td><i>" + m->getTelephoneNum() + "</i></td>");
                html.append("<tr>" + cell1 + cell2 + cell3 + "</tr>");
            }
        }
    }
    html.append("</table><br />");

    this->setHtml(html);
}

void DocumentModel::generateCommitteeList(){
    QString html;
    html.append("<p><b>COMMITTEE LIST</b></p><br />");

    CommitteeModel::iterator_range citr = CommitteeModel::findAll();
    CommitteeModel::iterator cit = citr.first;
    CommitteeModel::iterator cend = citr.second;

    //committee name
    int committeecount;
    for(committeecount = 0; cit != cend; cit++){
        CommitteeModel *c = *cit;

        //committee member
        html.append("<p><b>" + c->toString() + " Committee" + "</b></p>");
        html.append("<table border=0 cellpadding=10>");
        html.append("<tr><td align=""left"">Member Name</td><td align=""left"">Unit</td><td align=""left"">Role</td></tr>");

        //name | unit number | role
        MemberModel::iterator_range itr = c->findMembers();
        MemberModel::iterator it = itr.first;
        MemberModel::iterator end = itr.second;

        for(; it != end; it++){
            MemberModel *m = *it;
            if(!m->isMarkedDeleted()){
                QString cell1 = "";
                QString cell2 = "";
                QString cell3 = "";
                cell1.append("<td>" + m->getLastName() + "," + m->getFirstName() + "</td>");
                cell2.append("<td>" + QString::number(m->findUnit()->id) + "-" + m->findUnit()->address + "</td>");
                cell3.append("<td>" + m->getRoleAtCommittee() + "</td>");
                html.append("<tr>" + cell1 + cell2 + cell3 + "</tr>");
            }
        }
        html.append("</table><br />");
    }
    this->setHtml(html);
}

void DocumentModel::generateTaskList(CommitteeModel *committee){
    QString html;
    if(committee != 0){
        html.append("<p><b>PENDING TASK LIST</b></p><br />");
        html.append("NOTE: Highlighted tasks are overdue tasks");
        html.append("<table border=0 cellpadding=10>");
        html.append("<tr><td align=""left"">Check</td><td align=""left"">Task Name</td><td align=""left"">Due Date</td></tr>");

        TaskModel::iterator_range itr = committee->findTasks();
        TaskModel::iterator it = itr.first;
        TaskModel::iterator end = itr.second;

        for(; it != end; it++){
            TaskModel *t = *it;
            QDate today = QDate::currentDate();
            if(t->isPending()) {
                QString cell1 = "";
                QString cell2 = "";
                QString cell3 = "";
                QDate deadline = t->getDeadline().date();
                cell1.append("<td><img src=""images/checkbox.gif"" width=""15"" height=""15""></img></td>");
                cell2.append("<td>" + t->getName() + "</td>");
                cell3.append("<td>" + deadline.toString() + "</td>");

                //highlight row if deadline passed
                if(deadline < today) {
                    html.append("<tr style=""background-color:yellow"">");
                }else{
                    html.append("<tr>");
                }
                html.append(cell1 + cell2 + cell3 + "</tr>");
            }
        }
        this->setHtml(html);
    }
}
