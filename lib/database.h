#ifndef COOPERDB_H
#define COOPERDB_H

#include <sstream>
#include <utility>
#include <cassert>
#include <ctime>

#include <QDateTime>
#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>

#include "lib/imodeliterator.h"

/**
 * Handle creating, connecting, and querying the cooper database.
 */
class Database
{
    typedef bool (install_func_t)(QSqlQuery &);

public:
    ~Database();

    static bool connect(const char *, const char *, install_func_t *);
    static bool hasAny(const char *);
    static QSqlQuery select(const char *query);
    static QSqlQuery select(const char *table, const char *cond);
    static QSqlQuery select(const char *table, const int id);
    static bool remove(const char *table, const int id);
    static bool remove(const char *table, const char *cond);

    template <typename T>
    static pair<IModelIterator<T>, IModelIterator<T> >
    selectAll(const char *table, const char *cond="1=1");

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
template <> QSqlQuery &operator<< <QDateTime>(QSqlQuery &q, QDateTime val);
template <> QSqlQuery &operator<< <const QDateTime>(QSqlQuery &q, const QDateTime val);
template <> QSqlQuery &operator<< <bool>(QSqlQuery &q, bool val);

/**
 * Linkage stuff.
 */
template <typename T>
std::pair<IModelIterator<T>, IModelIterator<T> >
Database::selectAll(const char *table, const char *conditions) {
    stringstream ss;
    ss << "SELECT COUNT(id) as c FROM " << table << " WHERE " << conditions;
    QSqlQuery count(ss.str().c_str());
    int size((count.next() && count.isValid()) ? qcol<int>(count, "c") : 0);
    count.finish();
    ss.str(string(""));
    ss << "SELECT id FROM " << table << " WHERE " << conditions;
    return IModelIterator<T>::make(QSqlQuery(ss.str().c_str()), size);
}


#endif // COOPERDB_H
