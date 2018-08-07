#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

FILE *archivo;
FILE *fp;

archivo=fopen("/dev/joystick", "w"); //apertura del archivo
if (archivo==NULL){fputs("No existe el archivo", stderr); exit(1);} //verifica que el driver exista
fwrite(argv[1],1,1,archivo);	
printf("se escribio en el archivo : %s \n", argv[1]);
fclose(archivo);	

return 0;
}
