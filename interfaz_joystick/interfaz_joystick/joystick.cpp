#include "joystick.h"
#include "ui_joystick.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QChar>

//QByteArray numero;
QString numero;
QChar ejex;
QChar ejex1;
QChar ejey;
QChar ejey1;

bool i=false;
int j=0;

Joystick::Joystick(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Joystick)
{
    ui->setupUi(this);
    system("sudo chmod 777 /dev/joystick");
    system("i2cget -y 1 0x48 0x0");
    //system("xdotool search 'Filippakoc_pacman_demo' > /home/pi/id ");
    system("xdotool search 'Tetromino' > /home/pi/id ");


    QTimer *retardo=new QTimer(this);
    connect(retardo, SIGNAL(timeout()), this, SLOT(prueba()));
    retardo->start(0.0000001);

}

Joystick::~Joystick()
{
    delete ui;
}

void Joystick::prueba()
{

    for (j=0 ; j<2 ; j++){
        if(j==0){
        system("cd /home/pi/Documents/Driver_proyecto/ && sudo ./Escribir 0");
        }
        if(j==1){
        system("cd /home/pi/Documents/Driver_proyecto/ && sudo ./Escribir 1");
        }

        system("cd /home/pi/Documents/Driver_proyecto/ && sudo ./Leer");

        QFile file("/home/pi/Documents/Driver_proyecto/temp.dat");
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug()<<"No se puede abrir el archivo";
        }
        numero=file.readLine();

        if(j==0){
            ejey=numero[6];
            ejey1=numero[7];
        }

        if(j==1){
            ejex=numero[6] ;
            ejex1=numero[7] ;
        }

    }

        //Boton A
        if(numero[5]=='0'){
            ui->b_A->setPixmap(QPixmap(":/iconos/oprimidoA.png"));
        }else
        {
            ui->b_A->setPixmap(QPixmap(":/iconos/WiiU_A.png"));
        }
        //Boton 2
        if(numero[4]=='0'){
            ui->b_2->setPixmap(QPixmap(":/iconos/oprimido2.png"));
            system("xdotool key --window $(cat /home/pi/id) KP_Enter");
        }else
        {
            ui->b_2->setPixmap(QPixmap(":/iconos/WiiU_2.png"));
        }
        //Boton 1
        if(numero[3]=='0'){
            ui->b_1->setPixmap(QPixmap(":/iconos/oprimido1.png"));
            system("xdotool key --window $(cat /home/pi/id) space");
        }else
        {
            ui->b_1->setPixmap(QPixmap(":/iconos/WiiU_1.png"));
        }
        //Boton X
        if(numero[2]=='0'){
            ui->b_X->setPixmap(QPixmap(":/iconos/oprimidoX.png"));
        }else
        {
            ui->b_X->setPixmap(QPixmap(":/iconos/WiiU_X.png"));
        }
        //Boton B
        if(numero[1]=='0'){
            ui->b_B->setPixmap(QPixmap(":/iconos/oprimidoB.png"));
        }else
        {
            ui->b_B->setPixmap(QPixmap(":/iconos/WiiU_B.png"));
        }

        //Boton Y
        if(numero[0]=='0'){
            ui->b_Y->setPixmap(QPixmap(":/iconos/oprimidoY.png"));
          system("xdotool key --window $(cat /home/pi/id) w");
        }else
        {
            ui->b_Y->setPixmap(QPixmap(":/iconos/WiiU_Y.png"));
        }

        if(ejey=='7' && ejey1=='F' && ejex=='7' && ejex1=='F'){
            ui->d_pad->setPixmap(QPixmap(":/iconos/centro.png"));
        }else {
        if(ejey=='F' && ejey1=='F'){
            ui->d_pad->setPixmap(QPixmap(":/iconos/arriba.png"));
            system("xdotool key --window $(cat /home/pi/id) Up");
        }
        if(ejey=='0')
            {
            ui->d_pad->setPixmap(QPixmap(":/iconos/abajo.png"));
            system("xdotool key --window $(cat /home/pi/id) Down");
        }
        if(ejex=='F' && ejex1=='F'){
            ui->d_pad->setPixmap(QPixmap(":/iconos/derecha.png"));
            system("xdotool key --window $(cat /home/pi/id) Right");
        }
        if(ejex=='0'){
            ui->d_pad->setPixmap(QPixmap(":/iconos/izquierda.png"));
            system("xdotool key --window $(cat /home/pi/id) Left");
        }
        }

        if (i==false){
            i=true;}
        else {
            i=false;}
}
