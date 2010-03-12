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
                     const bool completed, QString deadlineDate)
 : IModel<TaskModel,select_from_table_tag>(id), name(n), description(descript),
                                status(completed), deadline(deadlineDate) {
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
        qcol<QString>(q, "deadline_date")
    );
}

/**
 * Save a task to the database.
 */
bool TaskModel::save(void) {
    QSqlQuery q;
    q.prepare(
        "UPDATE committee set name=?,description=?,status=?,deadline=? WHERE id=?"
    );
    q << name << description << status << deadline << id;
    return q.exec();
}

/**
 * Create and return a task
 */
bool TaskModel::create(QString n, QString descript, const bool completed, QString deadlineDate) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO task (name,description,status,deadline) VALUES (?,?,?,?)"
    );
    q << n << descript << completed << deadlineDate;
    if(!q.exec()) {
        return false;
    }
    return true;
}


/**
 * Get the name of a committee.
 */
QString TaskModel::toString(void) {
    return name;
}
