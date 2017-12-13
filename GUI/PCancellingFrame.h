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
    void setIds();

public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void requestForPCancelling();
    void requestForClose();
    /**
      * Reactions.
      * Each reaction has a prefix 'react'.
      */
    void reactForClose();

    void setIds(QMap<quint64,QPair<quint64,quint64>>&);

signals:
    void callForClose();
    void callForIds();
    void callForPCancelling(quint64);

private:
    Ui::PCancellingFrame *ui;
    void closeEvent(QCloseEvent*);
};


#endif // PCANCELLINGFRAME_H
