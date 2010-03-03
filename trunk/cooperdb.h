#ifndef COOPERDB_H
#define COOPERDB_H

#include <stdexcept>
#include <sstream>
#include <assert.h>
#include <time.h>

#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>

#include "criticalerror.h"

/**
 * Handle creating, connecting, and querying the cooper database.
 */
class CooperDB
{
public:
    ~CooperDB();

    static void connect(const char *);
    static bool hasAny(const char *);
    static QSqlQuery select(const char *query);

    static void queryError(const char *, QSqlQuery &);
    static void queryError(string, QSqlQuery &);
    static void queryError(stringstream &, QSqlQuery &);

private:
    CooperDB();

    static QSqlDatabase db;
    static void makeDatabase();
    static bool is_connected;
};

/* helper functions for dealing with db stuff */
QVariant qcol(QSqlQuery &q, const char *index);
string qcol_str(QSqlQuery &q, const char *index);

template <typename T> void qbind(QSqlQuery &q, T val);
template <> void qbind<string &>(QSqlQuery &q, string &val);
template <> void qbind<string>(QSqlQuery &q, string val);
template <> void qbind<time_t>(QSqlQuery &q, time_t val);

#endif // COOPERDB_H
