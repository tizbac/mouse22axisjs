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
#ifndef VIRTUALJOYSTICK_H
#define VIRTUALJOYSTICK_H
#include <QObject>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
class VirtualJoystick
{
public:
    VirtualJoystick(QWidget * parent,int amin,int amax);
    void UpdateAxisValue(int axis, int value);
    void UpdateButtonStatus(int button,bool pressed);
    ~VirtualJoystick();
private:
    int descriptor;
    struct input_event event;
};

#endif // VIRTUALJOYSTICK_H
