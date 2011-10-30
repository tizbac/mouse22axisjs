#ifndef MOUSE2J_H
#define MOUSE2J_H

#include <QMainWindow>
#include <QTimer>
#include "mouseposition.h"
#include "virtualjoystick.h"
namespace Ui {
    class Mouse2J;
}

class Mouse2J : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mouse2J(QWidget *parent = 0);
    ~Mouse2J();

private:
    Ui::Mouse2J *ui;
    MousePosition * m_mpos;
    VirtualJoystick * m_joy;
    QTimer * m_update;
    bool prevleft;
    bool prevright;
    bool prevcenter;
public slots:
    void onupdate();
    void onbuttonupdate(bool left,bool right , bool center);
};

#endif // MOUSE2J_H
