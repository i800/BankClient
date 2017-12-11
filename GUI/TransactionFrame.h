#ifndef TRANSACTIONFRAME_H
#define TRANSACTIONFRAME_H

#include <QFrame>

namespace Ui {
    class TransactionFrame;
}

class TransactionFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TransactionFrame(QWidget *parent = 0);
    ~TransactionFrame();
    void setCards(const QList<QString>&);

    bool firstInit() const
    {
        return _firstInit;
    }

public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void requestForTransaction();
    /**
      * Reactions.
      * Each reaction has a prefix 'react'.
      */
    void reactForClose();

signals:
    void callForClose();
    void callForTransaction(quint64, quint64, QString&);

private:
    Ui::TransactionFrame *ui;
    void closeEvent(QCloseEvent*);
    bool _firstInit;
};

#endif // TRANSACTIONFRAME_H
