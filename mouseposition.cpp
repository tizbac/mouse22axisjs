
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


#include "mouseposition.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>



static int _XlibErrorHandler(Display *display, XErrorEvent *event) {
    std::cerr << "An error occured detecting the mouse position" << std::endl;
    return True;
}
MousePosition::MousePosition( QObject *parent) : QObject(parent)
{
    display = XOpenDisplay(NULL);

    if (!display)
    {
        std::cerr << "Cannot open X11 display" << std::endl;
        abort();

    }
    int num_sizes;
    Rotation original_rotation;
    XSetErrorHandler(_XlibErrorHandler);
    Window root = RootWindow(display,0);
    XRRScreenSize *xrrs = XRRSizes(display, 0, &num_sizes);
    XRRScreenConfiguration *conf = XRRGetScreenInfo(display, root);
    short original_rate          = XRRConfigCurrentRate(conf);
    SizeID original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);
    m_size.setX(xrrs[original_size_id].width);
    m_size.setY(xrrs[original_size_id].width);
    mth = new MiceThread();
    mth->start();
    connect(mth,SIGNAL(buttonstateupdate(char)),SLOT(stateuinternal(char)));

    //XGrabButton(display,AnyButton,AnyModifier,root,)
}
QPoint MousePosition::GetScreenSize()
{
    return m_size;

}

QPoint MousePosition::GetPos()
{
    int root_x;
    int root_y;
    int win_x;
    int win_y;
    bool result;
    unsigned int mask_return;
    int nscreens = XScreenCount(display);
    root_windows = (Window*)malloc(sizeof(Window)*nscreens);
    for ( int i = 0; i < nscreens; i++)
        root_windows[i] = XRootWindow(display,i);
    for ( int i = 0; i < nscreens; i++)
    {
        result = XQueryPointer(display,root_windows[i],&window_returned,&window_returned,&root_x,&root_y,&win_x,&win_y,&mask_return);
        if ( result )
        {


            break;
        }


    }
    if ( !result )
        std::cerr << "NO MOUSE" << std::endl;
    free(root_windows);
    return QPoint(root_x,root_y);

}
MousePosition::~MousePosition()
{
    XCloseDisplay(display);
    mth->terminate();


}
void MousePosition::micereadready(int a)
{

    /*while ( mice->isReadable() )
    {
        QByteArray data = mice->read(3);
        QDataStream s(data);
        unsigned char bitfield;
        unsigned char rx;
        unsigned char ry;
        std::cout << "Datasize: " << data.length() << std::endl;
    }*/


}
void MiceThread::run()
{
    int mice = open("/dev/input/mice",O_RDONLY );
    if ( mice < 0)
    {
        std::cerr << "Cannot open mouse!" << std::endl;
        return;

    }
    while ( 1 )
    {
        char packet[3];
        //std::cout << "Data from mouse!" << std::endl;
        read(mice,packet,3);
        //std::cout << "Flags " << int(packet[0]) << " RX " << int(packet[1]) << " RY " << int(packet[2]) << std::endl;
        emit buttonstateupdate(packet[0]);

    }


}
void MousePosition::stateuinternal(char flags)
{
    emit bstateu(flags & 1 , flags & 2, flags & 4);

}

