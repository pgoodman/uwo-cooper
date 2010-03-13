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

class TaskModel : public IModel<TaskModel, select_from_table_tag> {

    MODEL_CLASS(TaskModel);

public:
    static const char *table_name;

    virtual bool save(void);
    static bool create(QString name, QString descript,
                       const QDateTime deadlineDate, const int committee_id);

    bool isPending(void);

    QString toString(void);

    void setName(QString n);
    QString getName(void);
    void setDescription(QString descript);
    QString getDescription(void);
    void setDeadline(QDateTime deadline_date);
    QDateTime getDeadline(void);
    void setStatus(bool newStatus);
    bool getStatus(void);

    virtual ~TaskModel();

protected:

    static TaskModel *load(QSqlQuery &q, const int id);

private:

    enum {
        Complete=1,
        Pending=0
    } TaskStatus;

    explicit TaskModel(const int id, QString name, QString descript,
                       bool status, const QDateTime deadlineDate,
                       const int committeeId);

    QString name;
    QString description;
    bool status;             // False = Pending, True = Complete
    QDateTime deadline;
    int committee_id;
};

#endif // TASKMODEL_H
