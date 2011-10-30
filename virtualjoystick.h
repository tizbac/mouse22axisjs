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
