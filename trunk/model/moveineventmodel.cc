
#include "model/moveineventmodel.h"

/**
 * Create a new move-in event.
 */
MoveInEventModel::MoveInEventModel(const int taskId, const QString desc)
 : task_id(taskId), task_description(desc) { }

void MoveInEventModel::create(const int unit_id,
                              const int task_id,
                              const QDateTime time) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO move_in_event (unit_id, task_id, move_in_time) "
        "VALUES (?,?,?)"
    );

    q << unit_id << task_id << time;
    q.exec();
}

/**
 * Find all move-in events within +/- 30 days of the move-in that is happening.
 */
QList<MoveInEventModel *> MoveInEventModel::findAll(const int unit_id,
                                                    const QDateTime time) {
    QList<MoveInEventModel *> events;
    QSqlQuery q;

    q.prepare(
        "SELECT t.id AS id, t.description AS description "
        "FROM move_in_event m, task t "
        "WHERE m.move_in_time >= ? AND m.move_in_time <= ? AND m.unit_id=? "
        "AND m.task_id = t.id AND t.is_annual=0 AND t.status=0"
    );

    q << time.addDays(-30) << time.addDays(30) << unit_id;
    q.exec();
    while(q.next()) {
        events.append(new MoveInEventModel(
            qcol<int>(q, "id"),
            qcol<QString>(q, "description")
        ));
    }
    return events;
}
