#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

FILE *archivo;
FILE *fp;
char lee[5];
char valor[6];
int i=0;

for (i; i<2 ; i++){	
	archivo=fopen("/dev/joystick", "r"); //apertura del archivo
	if (archivo==NULL){fputs("No existe el archivo", stderr); exit(1);} //verifica que el driver exista
	fread(lee,1,5,archivo);	
	valor[0] = ((lee[0] & 0x10 )>>4) ; // Valor del gpio4
	valor [1]= ((lee[2]& 0x02)>>1) ; // Valor del gpio17
	valor[2] = ((lee[2]& 0x40)>>6) ; // Valor del gpio22
	valor [3]= ((lee[2] & 0x80)>>7) ; // Valor del gpio23
	valor[4] = ((lee[3] & 0x01)>>0) ; // Valor del gpio24
	valor [5]= ((lee[3]& 0x08)>>3) ; // Valor del gpio27
	valor [6]= lee[4] ; // Trama de datos i2c
	}
i=0;
fclose(archivo);	//cierre del archivo

printf("El valor leido btn Y: %X\n", valor[0] );
printf("El valor leido btn X: %X\n", valor[1] );
printf("El valor leido btn A: %X\n", valor[5] );
printf("El valor leido btn B: %X\n", valor[2] );
printf("El valor leido btn 1: %X\n", valor[3] );
printf("El valor leido btn 2: %X\n", valor[4] );
printf("El valor leido I2C: %X\n", lee[4]);

fp=fopen("temp.dat", "wb"); //apertura del archivo temporal
fprintf(fp, "%X%X%X%X%X%X%X", valor[0],valor[1],valor[2],valor[3],valor[4],valor[5],valor[6]);
fclose(fp);	//cierre del archivo

return 0;
}

