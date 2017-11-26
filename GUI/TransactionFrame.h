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

public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void reactForClose();

private:
    Ui::TransactionFrame *ui;
};

#endif // TRANSACTIONFRAME_H
