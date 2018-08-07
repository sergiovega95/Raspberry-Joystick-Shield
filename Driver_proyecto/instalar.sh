#!/bin/sh
modulo="driver_proyecto" # Nombre del modulo
dispositivo="joystick" # Nombre del dispositivo
mode="664" # Numero del nodo
/sbin/insmod ./$modulo.ko $* || exit 1
mayor=$(awk '{if($2=="led") print $1 ; else print No_existe}' /proc/devices)
mknod /dev/${dispositivo} c $mayor 0
