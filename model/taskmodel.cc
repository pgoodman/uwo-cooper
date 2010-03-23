/*
 * TaskModelBase.cc
 *
 *  Created on: Mar 12, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "model/taskmodel.h"

const char *TaskModelBase::table_name("task");

/**
 * Protected constructor, initialize a new task from db info.
 */
TaskModelBase::TaskModelBase(QString n, QString descript,
                             bool isComplete, QDateTime deadlineDate,
                             const int committeeId, const bool isAnnual)
 : name(n), description(descript), is_complete(isComplete),
   is_annual(isAnnual), deadline(deadlineDate), committee_id(committeeId) {
}

/**
 * Destructor.
 */
TaskModelBase::~TaskModelBase() { }

/**
 * Save a task to the database.
 */
bool TaskModelBase::save(const int id) {
    QSqlQuery q;
    q.prepare(
        "UPDATE task set name=?,description=?,status=?,"
        "deadline=? WHERE id=?"
    );
    q << name << description << is_complete << deadline << id;
    return q.exec();
}

/**
 * Create and return a task
 */
bool TaskModelBase::create(QString name, QString descript,
                       const QDateTime deadlineDate,
                       const int committeeId, const bool isAnnual) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO task (name,description,status,committee_id,deadline,"
        "is_annual) VALUES (?,?,0,?,?,?)"
    );
    q << name << descript << committeeId << deadlineDate << isAnnual;
    return q.exec();
}


/**
 * Get the name of a committee.
 */
QString TaskModelBase::toString(void) {
    stringstream ss;
    ss << name.toStdString();
    QDateTime now;
    now.setTime_t(time(0));

    if(!is_annual) {
        if(is_complete) {
            ss << " [completed]";
        } else {
            if(deadline < now) {
                ss << " [overdue]";
            } else {
                ss << " [pending]";
            }
        }
    }
    return QString(ss.str().c_str());
}

void TaskModelBase::setName(QString n) {
    name = n;
}

QString TaskModelBase::getName(void) {
    return name;
}

void TaskModelBase::setDescription(QString descript) {
    description = descript;
}

QString TaskModelBase::getDescription(void) {
    return description;
}

void TaskModelBase::setDeadline(QDateTime deadline_date) {
    deadline = deadline_date;
}

QDateTime TaskModelBase::getDeadline(void) {
    return deadline;
}

bool TaskModelBase::isPending(void) {
    return !is_complete;
}

bool TaskModelBase::isSpec(void) {
    return is_annual;
}

// ---------------------------------------------------------------------------

TaskModel::iterator_range TaskModel::findAll(const char *cond) {
    stringstream ss;
    ss << "is_annual=0 AND " << cond;
    return IModel<TaskModel, select_from_table_tag>::findAll(cond);
}

TaskModel::iterator_range TaskModel::findAll(void) {
    return findAll("1=1");
}

TaskModel *TaskModel::load(QSqlQuery &q, const int id) {
    return new TaskModel(
        id,
        qcol<QString>(q, "name"),
        qcol<QString>(q, "description"),
        qcol<bool>(q, "status"),
        qcol<QDateTime>(q, "deadline"),
        qcol<int>(q, "committee_id")
    );
}

TaskModel::TaskModel(const int id, QString n, QString desc,
                     bool isComplete, QDateTime deadlineDate,
                     const int committeeId)
 : TaskModelBase(n,desc,isComplete,deadlineDate,committeeId,false),
   IModel<TaskModel, select_from_table_tag>(id) {
}

bool TaskModel::save(void) {
    return TaskModelBase::save(id);
}

bool TaskModel::create(QString name,
                       QString descript,
                       const QDateTime deadlineDate,
                       const int committee_id) {
    return TaskModelBase::create(
        name, descript, deadlineDate,committee_id,false
    );
}

void TaskModel::setCompleted(bool newStatus) {
    is_complete = newStatus;
}

bool TaskModel::isCompleted(void) {
    return is_complete;
}

// ---------------------------------------------------------------------------

TaskSpecModel::iterator_range TaskSpecModel::findAll(const char *cond) {
    stringstream ss;
    ss << "is_annual=1 AND " << cond;
    return IModel<TaskSpecModel, select_from_table_tag>::findAll(cond);
}

TaskSpecModel::iterator_range TaskSpecModel::findAll(void) {
    return findAll("1=1");
}

TaskSpecModel *TaskSpecModel::load(QSqlQuery &q, const int id) {
    return new TaskSpecModel(
        id,
        qcol<QString>(q, "name"),
        qcol<QString>(q, "description"),
        qcol<QDateTime>(q, "deadline"),
        qcol<int>(q, "committee_id")
    );
}

TaskSpecModel::TaskSpecModel(const int id, QString n, QString desc,
                     QDateTime deadlineDate,
                     const int committeeId)
 : TaskModelBase(n,desc,false,deadlineDate,committeeId,true),
   IModel<TaskSpecModel, select_from_table_tag>(id) {
}

bool TaskSpecModel::save(void) {
    return TaskModelBase::save(id);
}

bool TaskSpecModel::create(QString name,
                       QString descript,
                       const QDateTime deadlineDate,
                       const int committee_id) {
    return TaskModelBase::create(
        name, descript, deadlineDate,committee_id,true
    );
}
