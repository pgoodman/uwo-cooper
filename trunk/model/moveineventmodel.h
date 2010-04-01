
#ifndef MOVE_IN_EVENT_MODEL_H_
#define MOVE_IN_EVENT_MODEL_H_

#include <QList>
#include <QDateTime>
#include <QSqlQuery>

#include "lib/database.h"

class MoveInEventModel {
public:
    static void create(const int unit_id, const int task_id, const QDateTime time);
    static QList<MoveInEventModel *> findAll(const int unit_id, const QDateTime time);

    const int task_id;
    const QString task_description;
private:
    MoveInEventModel(const int taskId, const QString desc);
};

#endif // MOVE_IN_EVENT_MODEL_H_
