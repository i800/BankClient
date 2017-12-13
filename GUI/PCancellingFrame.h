#ifndef PCANCELLINGFRAME_H
#define PCANCELLINGFRAME_H

#include <QFrame>

namespace Ui {
class PCancellingFrame;
}

class PCancellingFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PCancellingFrame(QWidget *parent = 0);
    ~PCancellingFrame();

private:
    Ui::PCancellingFrame *ui;
};

#endif // PCANCELLINGFRAME_H
