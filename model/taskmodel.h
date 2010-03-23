#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <sstream>
#include <iostream>

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>

#include "lib/database.h"
#include "lib/imodel.h"

using namespace std;

class TaskModelBase {
public:

    static const char *table_name;

    bool isPending(void);

    QString toString(void);

    void setName(QString n);
    QString getName(void);
    void setDescription(QString descript);
    QString getDescription(void);
    void setDeadline(QDateTime deadline_date);
    QDateTime getDeadline(void);
    bool isSpec(void);

    virtual ~TaskModelBase();

protected:

    static bool create(QString name,
                       QString descript,
                       const QDateTime deadlineDate,
                       const int committee_id,
                       const bool isAnnual);

    TaskModelBase(QString name, QString descript,
                  bool is_complete, const QDateTime deadlineDate,
                  const int committeeId, bool isAnnual);

    bool save(const int id);

    QString name;
    QString description;
    bool is_complete;             // False = Pending, True = Complete
    bool is_annual;
    QDateTime deadline;
    int committee_id;
};

/**
 * Tasks.
 */
class TaskModel : public TaskModelBase,
                  public IModel<TaskModel, select_from_table_tag> {
    MODEL_CLASS(TaskModel);
public:
    static TaskModel::iterator_range findAll(void);
    static TaskModel::iterator_range findAll(const char *);

    static bool create(QString name,
                       QString descript,
                       const QDateTime deadlineDate,
                       const int committee_id);
    virtual bool save(void);
    void setCompleted(bool newStatus);
    bool isCompleted(void);
protected:
    TaskModel(const int id, QString n, QString desc,
              bool isComplete, QDateTime deadlineDate,
              const int committeeId);
    static TaskModel *load(QSqlQuery &q, const int id);
};

/**
 * Annual Task Specs.
 */
class TaskSpecModel : public TaskModelBase,
                      public IModel<TaskSpecModel, select_from_table_tag> {
    MODEL_CLASS(TaskSpecModel);
public:
    static TaskSpecModel::iterator_range findAll(void);
    static TaskSpecModel::iterator_range findAll(const char *);

    static bool create(QString name,
                       QString descript,
                       const QDateTime deadlineDate,
                       const int committee_id);
    virtual bool save(void);
protected:
    TaskSpecModel(const int id, QString n, QString desc,
                  QDateTime deadlineDate,
                  const int committeeId);
    static TaskSpecModel *load(QSqlQuery &q, const int id);
};

#endif // TASKMODEL_H
