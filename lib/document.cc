#include "document.h"

Document::Document(int doctype){

    cursor = new QTextCursor(this);

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
        generateTaskList();
        break;
    }
}

Document::~Document(){

}

void Document::generatePhoneList(bool isconfidential){

    QString html;

    html.append("<p><b>MEMBER PHONE LIST</b></p><br />");
    html.append("<table border=0>");
    html.append("<tr><td>Name</td><td>Unit</td><td>Phone Number</td></tr>");



    MemberModel::iterator_range itr = MemberModel::findAll();
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
                cell1.append("<td>" + m->getUserName() + "</td");
                cell2.append("<td>" + QString::number(m->findUnit()->id) + "-" + m->findUnit()->address + "</td>");
                cell3.append("<td>" + m->getTelephoneNum() + "</td>");
                html.append("<tr>" + cell1 + cell2 + cell3 + "</tr>");
            }
        }
    }
    html.append("</table><br />");

    this->setHtml(html);
}

void Document::generateCommitteeList(){
    QString html;
    html.append("<p><b>COMMITTEE LIST</b></p><br />");
    html.append("<table border=0>");

    CommitteeModel::iterator_range citr = CommitteeModel::findAll();
    CommitteeModel::iterator cit = citr.first;
    CommitteeModel::iterator cend = citr.second;

    //committee name
    int committeecount;
    for(committeecount = 0; cit != cend; cit++){
        CommitteeModel *c = *cit;

        //committee member
        html.append("<p>" + c->toString() + "</p><br />");
        html.append("<table border=0>");
        html.append("<tr><td>Member Name</td><td>Unit</td><td>Role</td></tr>");

        //name | unit number | role
        MemberModel::iterator_range itr = c->findMembers();
        MemberModel::iterator it = itr.first;
        MemberModel::iterator end = itr.second;

        MemberModel *m = *it;
        if(!m->isMarkedDeleted()){
            QString cell1 = "";
            QString cell2 = "";
            QString cell3 = "";
            cell1.append("<td>" + m->getUserName() + "</td>");
            cell2.append("<td>" + QString::number(m->findUnit()->id) + "-" + m->findUnit()->address + "</td>");
            cell3.append("<td>" + m->getRoleAtCommittee() + "</td>");
            html.append("<tr>" + cell1 + cell2 + cell3 + "</tr>");
        }
    }
}

void Document::generateTaskList(){
    QString html;
    html.append("<p><b>PENDING TASK LIST</b></p><br />");
    html.append("<table border=0>");


}
