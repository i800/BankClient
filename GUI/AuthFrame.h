#ifndef AUTHFRAME_H
#define AUTHFRAME_H

#include <QFrame>

namespace Ui {
    class AuthFrame;
}

class AuthFrame : public QFrame
{
    Q_OBJECT
private:
    Ui::AuthFrame *ui;
    void setWaitingMode(const bool);

public:
    explicit AuthFrame(QWidget *parent = 0);
    ~AuthFrame();

public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void requestForAuth();
    void requestForQuit();

    /**
      * Reactions.
      * Each reaction has a prefix 'react'.
      */
    void reactAuthFailed();

signals:
    /**
     * Each user request called from interface
     * has a prefix 'call'.
     */
    void callForAuth(quint64, QString);
};

#endif // AUTHFRAME_H
