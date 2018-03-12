#ifndef ASYNC_QUERY_THREAD_HPP
#define ASYNC_QUERY_THREAD_HPP

#include <QThread>
#include <QSqlRecord>
#include <QSqlError>
#include "query-request.hpp"
#include "query-result.hpp"

class QueryWorker;

class QueryThread : public QThread {
        friend class QueryWorker;

        Q_OBJECT
    public:
        /* Transaction state represents the state of a started transaction.
         * -1 signifies that the transaction failed.
         * 0 signifies that there is no current transaction.
         * 1 signifies that there is a current transaction.
         */
        enum TransactionState {Failed = -1, Unset, Set};
        static const QueryThread &instance();
        static QString getSqliteConnectionName();
        static QString getMysqlConnectionName();

        static TransactionState getTransactionState();
    signals:
        void queryFinished(const QueryResult &);
        void queue(const QueryRequest &);
    public slots:
        void execute(const QueryRequest &);
    protected:
        virtual void run();
    private:
        explicit QueryThread(QObject *parent = 0);
        static TransactionState transactionState;
        static void setTransactionState(TransactionState state);

        QueryWorker *m_worker;
        static QueryThread *this_thread;
};

#endif // ASYNC_QUERY_THREAD_HPP
