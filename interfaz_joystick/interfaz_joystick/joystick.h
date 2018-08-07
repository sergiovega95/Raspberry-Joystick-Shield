#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QMainWindow>

namespace Ui {
class Joystick;
}

class Joystick : public QMainWindow
{
    Q_OBJECT

public:
    explicit Joystick(QWidget *parent = 0);
    ~Joystick();

private slots:
    void prueba();

private:
    Ui::Joystick *ui;
};

#endif // JOYSTICK_H
