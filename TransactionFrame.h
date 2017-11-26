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

private:
    Ui::TransactionFrame *ui;
};

#endif // TRANSACTIONFRAME_H
