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
#include "virtualjoystick.h"

#include <QMessageBox>

#define RESET_EVENT()	memset(&event, 0, sizeof(event));	\
                        gettimeofday(&event.time, NULL);
char *uinput_filename[] = {"/dev/uinput", "/dev/input/uinput",
                           "/dev/misc/uinput"};
__u16 joystickKeys[] = {
BTN_A,		// Gamepad - from linux/input.h
BTN_B,
BTN_C,
BTN_X,
BTN_Y,
BTN_Z,
BTN_TL,
BTN_TR,
BTN_TL2,
BTN_TR2,
BTN_SELECT,
BTN_START,
BTN_MODE,
BTN_THUMBL,
BTN_THUMBR,

BTN_TRIGGER,	// Joystick - in case program has stupidly large number of buttons
BTN_THUMB,
BTN_THUMB2,
BTN_TOP,
BTN_TOP2,
BTN_PINKIE,
BTN_BASE,
BTN_BASE2,
BTN_BASE3,
BTN_BASE4,
BTN_BASE5,
BTN_BASE6,
BTN_DEAD,
};

__u16 joystickAxes[] = {
ABS_X,
ABS_Y,
ABS_Z,
ABS_RX,
ABS_RY,
ABS_RZ,
ABS_THROTTLE,
ABS_RUDDER,
ABS_WHEEL,
ABS_GAS,
ABS_BRAKE,
ABS_HAT0X,
ABS_HAT0Y,
ABS_HAT1X,
ABS_HAT1Y,
ABS_HAT2X,
ABS_HAT2Y,
ABS_HAT3X,
ABS_HAT3Y,
ABS_PRESSURE,
ABS_DISTANCE,
ABS_TILT_X,
ABS_TILT_Y,
ABS_TOOL_WIDTH,
ABS_VOLUME,
ABS_MISC,
};
VirtualJoystick::VirtualJoystick(QWidget * parent,int amin,int amax)
{
    struct uinput_user_dev uinp;
    for (int i = 0; i < 3; i++)
    {
            if ((descriptor = open(uinput_filename[i], O_RDWR)) >= 0)
            {
                    break;
            }
    }
    if ( descriptor < 0 )
    {
        QMessageBox::critical(parent,"Error","Cannot open uinput device file , maybe the driver is missing!",QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name,"MouseJoystick",20);
    uinp.id.version = 4;
    uinp.id.bustype = BUS_USB;
    for(int i = 0; i < ABS_MAX; i++)
    {
            uinp.absmax[i] = amax;
            uinp.absmin[i] = amin;
    }
    ioctl(descriptor, UI_SET_EVBIT, EV_SYN);
    ioctl(descriptor, UI_SET_EVBIT, EV_KEY);
    ioctl(descriptor, UI_SET_EVBIT, EV_ABS);

    //Axes
    ioctl(descriptor, UI_SET_ABSBIT, ABS_X);
    ioctl(descriptor, UI_SET_ABSBIT, ABS_Y);


    ioctl(descriptor, UI_SET_KEYBIT, BTN_A);
    ioctl(descriptor, UI_SET_KEYBIT, BTN_B);
    ioctl(descriptor, UI_SET_KEYBIT, BTN_C);

    int retcode = write(descriptor, &uinp, sizeof(uinp));
    retcode = (ioctl(descriptor, UI_DEV_CREATE));
    if ( retcode )
    {
        QMessageBox::critical(parent,"Error","Failed to create virtual device",QMessageBox::Ok,QMessageBox::NoButton);
        ioctl (descriptor, UI_DEV_DESTROY);
        close (descriptor);
        return;

    }

}
void VirtualJoystick::UpdateAxisValue(int axis, int value)
{
    RESET_EVENT();
    event.type = EV_ABS;
    event.code = axis;
    event.value = value;
    write(descriptor,&event,sizeof(event));
    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    write(descriptor, &event, sizeof(event));

}
void VirtualJoystick::UpdateButtonStatus(int button, bool pressed)
{
    RESET_EVENT();
    event.type = EV_KEY;
    event.code = button;
    event.value = pressed;
    write(descriptor,&event,sizeof(event));
    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    write(descriptor, &event, sizeof(event));

}
VirtualJoystick::~VirtualJoystick()
{
    RESET_EVENT();

    event.type = SYN_CONFIG;
    event.code = 0;
    event.value = 0;
    write(descriptor,&event,sizeof(event));

    ioctl(descriptor, UI_DEV_DESTROY);
    close(descriptor);


}
