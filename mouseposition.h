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
#ifndef MOUSEPOSITION_H
#define MOUSEPOSITION_H

#include <QPoint>
#include <QIODevice>
#include <QDataStream>

#include <QFile>
#include <QSocketNotifier>
#include <QThread>
#include <X11/Xlib.h>

#include <X11/extensions/Xrandr.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#undef Bool
#undef None
class MiceThread : public QThread
{
    Q_OBJECT
public:
    void run();
signals:
    void buttonstateupdate(char flags);

};

class MousePosition : public QObject
{
    Q_OBJECT
private:
    Window *root_windows;
    Window window_returned;
    Display *display;
    QPoint m_size;
    MiceThread * mth;
    int mice;
public:
    explicit MousePosition( QObject *parent=0);
    ~MousePosition();
    QPoint GetPos();
    QPoint GetScreenSize();
public slots:
    void micereadready(int a);
    void stateuinternal(char flags);
signals:
    void bstateu(bool left, bool right, bool center);
};

#endif // MOUSEPOSITION_H
