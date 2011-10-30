
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
