#ifndef COOPERDB_H
#define COOPERDB_H

#include <stdexcept>
#include <iostream>
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

#include "conf.h"
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
//QVariant qcol(QSqlQuery &q, const char *index);
template <typename T> T qcol(const QSqlQuery &q, const char *index);

template <> QVariant qcol(const QSqlQuery &q, const char *index);
template <> int qcol(const QSqlQuery &q, const char *index);
template <> double qcol(const QSqlQuery &q, const char *index);
template <> bool qcol(const QSqlQuery &q, const char *index);
template <> string qcol(const QSqlQuery &q, const char *index);

const QVariant &operator>>(const QVariant &v, int &x);
const QVariant &operator>>(const QVariant &v, bool &x);
const QVariant &operator>>(const QVariant &v, double &x);
const QVariant &operator>>(const QVariant &v, string &x);
const QVariant &operator>>(const QVariant &v, QString &x);

template <typename T> QSqlQuery &operator<<(QSqlQuery &q, T val);
template <> QSqlQuery &operator<< <string &>(QSqlQuery &q, string &val);
template <> QSqlQuery &operator<< <string>(QSqlQuery &q, string val);
template <> QSqlQuery &operator<< <time_t>(QSqlQuery &q, time_t val);
template <> QSqlQuery &operator<< <void *>(QSqlQuery &q, void *val);

#endif // COOPERDB_H
