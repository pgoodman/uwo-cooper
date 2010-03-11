#ifndef COOPERDB_H
#define COOPERDB_H

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <utility>
#include <cassert>
#include <time.h>

#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>

#include "conf.h"
#include "lib/criticalerror.h"
#include "lib/imodeliterator.h"

/**
 * Handle creating, connecting, and querying the cooper database.
 */
class Database
{
    typedef void (install_func_t)(QSqlQuery &);

public:
    ~Database();

    static void connect(const char *, const char *, install_func_t *);
    static bool hasAny(const char *);
    static QSqlQuery select(const char *query);
    static QSqlQuery select(const char *table, const char *cond);
    static QSqlQuery select(const char *table, const int id);
    static bool remove(const char *table, const int id);

    template <typename T>
    static pair<IModelIterator<T,T>, IModelIterator<T,T> >
    selectAll(const char *table, const char *cond="1=1");

    static void queryError(const char *, QSqlQuery &);
    static void queryError(string, QSqlQuery &);
    static void queryError(stringstream &, QSqlQuery &);

    static void disconnect(void);

private:
    Database();

    static void makeDatabase();

    static QSqlDatabase db;
    static bool is_connected;
};

/* helper functions for dealing with db stuff */
//QVariant qcol(QSqlQuery &q, const char *index);
template <typename T> T qcol(const QSqlQuery &q, const char *index);

template <> QVariant qcol(const QSqlQuery &q, const char *index);
template <> int qcol(const QSqlQuery &q, const char *index);
template <> unsigned int qcol(const QSqlQuery &q, const char *index);
template <> double qcol(const QSqlQuery &q, const char *index);
template <> bool qcol(const QSqlQuery &q, const char *index);
template <> string qcol(const QSqlQuery &q, const char *index);
template <> QString qcol(const QSqlQuery &q, const char *index);
template <> long qcol(const QSqlQuery &q, const char *index);

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
//template <> QSqlQuery &operator<< <double>(QSqlQuery &q, double val);

/**
 * Linkage stuff.
 */
template <typename T>
pair<IModelIterator<T,T>, IModelIterator<T,T> >
Database::selectAll(const char *table, const char *conditions) {
    stringstream ss;
    ss << "SELECT COUNT(id) as c FROM " << table << " WHERE " << conditions;
    QSqlQuery count(ss.str().c_str());
    int size((count.next() && count.isValid()) ? qcol<int>(count, "c") : 0);
    count.finish();
    ss.str(string(""));
    ss << "SELECT id FROM " << table << " WHERE " << conditions;
    return IModelIterator<T,T>::make(QSqlQuery(ss.str().c_str()), size);
}


#endif // COOPERDB_H
