#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <utility>

#include <QString>
#include <QDate>
#include <QSqlQuery>

#include "lib/database.h"
#include "lib/imodel.h"

using namespace std;

class TaskModel : public IModel<TaskModel, select_from_table_tag> {

    MODEL_CLASS(TaskModel);

public:
    static const char *table_name;

    virtual bool save(void);
    bool create(QString n, QString descript, const bool completed, QString deadlineDate);

    QString toString(void);

    virtual ~TaskModel();

protected:

    //static const char *column_names[20];
    static TaskModel *load(QSqlQuery &q, const int id);

private:
    explicit TaskModel(const int id, QString n, QString descript,
                       const bool completed, QString deadlineDate);

    QString name;
    QString description;
    bool status;
    QString deadline;
};

#endif // TASKMODEL_H
