#!/bin/sh
modulo="driver_proyecto" # Nombre del modulo
dispositivo="joystick" # Nombre del dispositivo
/sbin/rmmod ./$modulo.ko $* || exit 1
rm -f /dev/${dispositivo}
