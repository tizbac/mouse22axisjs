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
#include "ui_mouse2j.h"
#include "mouse2j.h"
#include <iostream>
Mouse2J * inst;
Mouse2J::Mouse2J(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mouse2J)
{
    inst = this;
    ui->setupUi(this);
    m_mpos = new MousePosition();
    m_joy = new VirtualJoystick(this,-1000,1000);
    m_update = new QTimer(this);
    connect(m_update,SIGNAL(timeout()),SLOT(onupdate()));
    connect(m_mpos,SIGNAL(bstateu(bool,bool,bool)),SLOT(onbuttonupdate(bool,bool,bool)));
    m_update->setSingleShot(false);
    m_update->setInterval(5);
    m_update->start();
    prevleft = false;
    prevright = false;
    prevcenter = false;
}

Mouse2J::~Mouse2J()
{
    delete ui;
    delete m_mpos;
    delete m_joy;
}

void Mouse2J::onupdate()
{
    QPoint p = m_mpos->GetPos();
    float x = (float(p.x())/float(m_mpos->GetScreenSize().x()))*2000-1000;
    float y = (float(p.y())/float(m_mpos->GetScreenSize().y()))*2000-1000;
    ui->label->setText(QString().sprintf("%f,%f",x,y));
    m_joy->UpdateAxisValue(ABS_X,int(x));
    m_joy->UpdateAxisValue(ABS_Y,int(y));

}
void Mouse2J::onbuttonupdate(bool left,bool right , bool center)
{
    if ( prevleft != left )
    {
        m_joy->UpdateButtonStatus(BTN_A,left);
        prevleft = left;
    }
    if ( prevright != right )
    {
        m_joy->UpdateButtonStatus(BTN_B,right);
        prevright = right;
    }
    if ( prevcenter != center )
    {
        m_joy->UpdateButtonStatus(BTN_C,center);
        prevcenter = center;
    }
}
