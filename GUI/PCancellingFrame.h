#ifndef PCANCELLINGFRAME_H
#define PCANCELLINGFRAME_H

#include <QFrame>

namespace Ui
{
    class PCancellingFrame;
}

class PCancellingFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PCancellingFrame(QWidget *parent = 0);
    ~PCancellingFrame();

private:
    void setIds();

public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void requestForPCancelling();
    /**
      * Reactions.
      * Each reaction has a prefix 'react'.
      */
    void reactForClose();

signals:
    void callForClose();
    void callForPCancelling(quint64);

private:
    Ui::PCancellingFrame *ui;
    void closeEvent(QCloseEvent*);
};


#endif // PCANCELLINGFRAME_H
