/*
    Joystick Emulator
    Copyright (C) 2011  Tiziano Bacocco <tizbac2@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
