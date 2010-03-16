/*
 * taskmodel.cc
 *
 *  Created on: Mar 12, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "model/taskmodel.h"

const char *TaskModel::table_name("task");

/**
 * Private constructor, initialize a new task from db info.
 */
TaskModel::TaskModel(const int id, QString n, QString descript,
                     bool isComplete, QDateTime deadlineDate,
                     const int committeeId)
 : IModel<TaskModel,select_from_table_tag>(id), name(n),
   description(descript), is_complete(isComplete), deadline(deadlineDate),
   committee_id(committeeId) {
}

/**
 * Destructor.
 */
TaskModel::~TaskModel() { }

/**
 * Load a task by its id.
 */
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

/**
 * Save a task to the database.
 */
bool TaskModel::save(void) {
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
bool TaskModel::create(QString name, QString descript,
                       const QDateTime deadlineDate,
                       const int committeeId) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO task (name,description,status,committee_id,deadline) "
        "VALUES (?,?,0,?,?)"
    );
    q << name << descript << committeeId << deadlineDate;
    return q.exec();
}


/**
 * Get the name of a committee.
 */
QString TaskModel::toString(void) {
    stringstream ss;
    ss << name.toStdString();
    QDateTime now;
    now.setTime_t(time(0));

    if(is_complete) {
        ss << " [completed]";
    } else {
        if(deadline < now) {
            ss << " [overdue]";
        } else {
            ss << " [pending]";
        }
    }
    return QString(ss.str().c_str());
}

void TaskModel::setName(QString n) {
    name = n;
}

QString TaskModel::getName(void) {
    return name;
}

void TaskModel::setDescription(QString descript) {
    description = descript;
}

QString TaskModel::getDescription(void) {
    return description;
}

void TaskModel::setDeadline(QDateTime deadline_date) {
    deadline = deadline_date;
}

QDateTime TaskModel::getDeadline(void) {
    return deadline;
}

void TaskModel::setCompleted(bool newStatus) {
    is_complete = newStatus;
}

bool TaskModel::isCompleted(void) {
    return is_complete;
}

bool TaskModel::isPending(void) {
    return !is_complete;
}
