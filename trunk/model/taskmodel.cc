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
                     const int the_status, QDateTime deadlineDate,
                     const int committeeId)
 : IModel<TaskModel,select_from_table_tag>(id), name(n),
   description(descript), status(the_status), deadline(deadlineDate),
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
        qcol<int>(q, "status"),
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
    q << name << description << status << deadline << id;
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

    if(Complete == status) {
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
