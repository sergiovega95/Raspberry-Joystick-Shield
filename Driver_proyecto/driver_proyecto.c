#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/delay.h>
#define ioaddress_SIE_BASE 0x3F200000 //Direc. base GPIO raspberry PI3
#define ioaddress_BSC1_BASE 0x3F804000 //Direc. base I2C
#define ioaddress_BSC1_SIZE 0x20 //Espacio que ser utilizado para I2C
#define ioaddress_SIZE 0x38 //Espacio que ser utilizado
#define address_LED_on 0x1C //Direc. del registro del led para escribir
#define address_LED_off 0x28 //Direc. del registro del led para borrar
#define address_LED_estado 0x34 //Direc. del registro de estado del led
#define address_Rpull 0x94 //Direc. del registro R-pull up/down
#define address_Pinpull 0x98 //Direc. del registro R-pull up/down
#define address_gpsel2 0x00 // Direccion de registro para usar pines 0-9
#define I2C_C 0x0
#define I2C_S 0x4
#define I2C_DLEN 0x8
#define I2C_A 0xc
#define I2C_FIFO	0x10
#define I2C_DIV 0x14
#define I2C_DEL 0x18
#define I2C_CLKT	0x1c
#define I2C_SLAVE 0x48

MODULE_LICENSE("Dual BSD/GPL");

static char *nombre="led";
static unsigned int PrimerMenor=0;
static unsigned int cuenta=1;
static dev_t led_dev_numero;
char *buffer;
int on_off=0;
int leido,stado=0;
static void __iomem *ioaddress_SIE;
static void __iomem *ioaddress_BSC1_SIE; // para I2C
struct led_dev *led_dev_puntero;
struct led_dev{
	struct cdev led_cdev;};

int led_open(struct inode *puntero_inode, struct file *puntero_file){
	struct led_dev *led_dev_puntero;
	printk(KERN_INFO "joystick: se ha abierto el dispositivo\n");
	led_dev_puntero=container_of(puntero_inode->i_cdev, struct led_dev, led_cdev);
	puntero_file->private_data=led_dev_puntero;
	return 0;}

int led_release(struct inode *puntero_inode, struct file *puntero_file){
	
	printk(KERN_INFO "joystick: se ha liberado el dispositivo\n");	
	iowrite32(0X00000000, ioaddress_BSC1_SIE+I2C_C);
	iowrite32(0X00000030, ioaddress_BSC1_SIE+I2C_C);
	iowrite32(0X00000000, ioaddress_BSC1_SIE+I2C_C);
	return 0;}

static ssize_t led_read(struct file *puntero_file, char *buffer_user, size_t tamano, loff_t *puntero_offset){
	unsigned int estado;
	unsigned int leer_i2c;
	unsigned int bandera;
	unsigned long prueba;	
	char buffer1[5];
	printk(KERN_INFO "Botones joystick: leyendo el dispositivo\n");
	estado = ioread32(ioaddress_SIE+ address_LED_estado);	
	printk("Estado GPIOS: -> 0x%X \n", estado);

	iowrite32(0x00000000, ioaddress_BSC1_SIE+I2C_C); // Activate i2c protocol
	iowrite32(I2C_SLAVE, ioaddress_BSC1_SIE+I2C_A); //Setup Slave addres
	iowrite32(0x00000001, ioaddress_BSC1_SIE+I2C_DLEN); // Number of bytes to read	
	iowrite32((1<<9)|(1<<8)|(1<<1), ioaddress_BSC1_SIE+I2C_S); // Restart Status Register
	iowrite32(0x00000030, ioaddress_BSC1_SIE+I2C_C); // Clear FIFO	
	iowrite32(0x00008081, ioaddress_BSC1_SIE+I2C_C); //Empezar transferencia de lectura
	iowrite32(0x00000002, ioaddress_BSC1_SIE+I2C_S); //Limpiar el bit I2CDONE
	do{
		bandera=ioread32(ioaddress_BSC1_SIE+I2C_S); //Lectura del registro de estado I2C
	}while(!(bandera & ((1<<1)|(1<<3))));
	leer_i2c =ioread32(ioaddress_BSC1_SIE+I2C_FIFO); //lectura del registro FIFO - Datos transmitidos
	iowrite32((1<<9)|(1<<8)|(1<<1), ioaddress_BSC1_SIE+I2C_S); // Restart Status Register	
	printk(KERN_ALERT "Valor leido I2C: %X",leer_i2c);
	iowrite32(0X00000000, ioaddress_BSC1_SIE+I2C_C); //deshabilitar comunicacion i2c

	buffer1[0]=(char)(estado>>0);
	buffer1[1]=(char)(estado>>8);
	buffer1[2]=(char)(estado>>16);
	buffer1[3]=(char)(estado>>24);	
	buffer1[4]=(char)(leer_i2c);
	prueba=copy_to_user(buffer_user, buffer1, 5); //Enviar informacion del kernel al espacio del usuario
	return tamano;}

static ssize_t led_write(struct file *puntero_file, const char *buffer_user, size_t tamano, loff_t *puntero_offset){
	char buffer[tamano];
	unsigned long in;	
	unsigned int escribir=0;
	unsigned int bandera=0;
	////////////////////////////////// 
	in=copy_from_user (buffer,buffer_user, tamano) ;
	if (buffer[0]=='1'){
		escribir=0x00000001;	//bit de control para leer canal 1 ADC
		printk(KERN_ALERT "Seleccinado el canal #1: Eje X");
	}else if(buffer[0]=='0'){
		escribir=0x00000000;	//bit de control para leer canal 0 ADC
		printk(KERN_ALERT "Seleccinado el canal #0 : Eje Y");
		}else{
			printk(KERN_ALERT "La informacion enviada al kernel es erronea");
			}	
 	iowrite32(0X00000000, ioaddress_BSC1_SIE+I2C_C); // desactivar comunicacion i2c
	iowrite32(I2C_SLAVE, ioaddress_BSC1_SIE+I2C_A); //configuracion direcc. esclavo
	iowrite32(0x00000001, ioaddress_BSC1_SIE+I2C_DLEN); // Numero de bits a escribir 
	iowrite32(escribir, ioaddress_BSC1_SIE+I2C_FIFO); // dato que se desea escribir
	iowrite32((1<<9)|(1<<8)|(1<<1), ioaddress_BSC1_SIE+I2C_S); // Limpiar registro de estado
	iowrite32(0X00008080, ioaddress_BSC1_SIE+I2C_C); // Activar comunicacion i2c - comenzar una transferencia de escritura
	do{
		bandera=ioread32(ioaddress_BSC1_SIE+I2C_S)&0x3FF; // Read Status register	  	
	}while(!(bandera & (1<<1))); // Esperar a que se complete la transmision I2C_DONE=1
	bandera=ioread32(ioaddress_BSC1_SIE+I2C_S)&0x3FF;
	//printk(KERN_ALERT "valor del registro s  %X",bandera);
	iowrite32(0X00000030, ioaddress_BSC1_SIE+I2C_C); // Limpiar registro FIFO
	iowrite32((1<<9)|(1<<8)|(1<<1), ioaddress_BSC1_SIE+I2C_S); // Limpiar registro de estado
	iowrite32(0X00000000, ioaddress_BSC1_SIE+I2C_C); //deshabilitar comunicacion i2c
	
	return tamano;
}
struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.read = led_read,
	.write = led_write,  
	.open = led_open,
	.release = led_release};

static int hello_init(void){
	int resultado,error;
	printk(KERN_ALERT "Hola mundo\n");
	resultado=alloc_chrdev_region(&led_dev_numero, PrimerMenor, cuenta, nombre);

	if(resultado==0)
		printk(KERN_INFO "Se reservaron los siguientes numeros\n Mayor: %d\n Menor: %d\n\n",MAJOR(led_dev_numero), MINOR	 (led_dev_numero));
	else
		printk(KERN_INFO "Hubo un error y los numeros no se reservaron.\n Error: %d\n\n",resultado);

	led_dev_puntero=kmalloc(sizeof(struct led_dev), GFP_KERNEL);
	buffer=kmalloc(4,GFP_KERNEL);
	cdev_init(&led_dev_puntero->led_cdev, &led_fops);
	led_dev_puntero->led_cdev.owner=THIS_MODULE;
	led_dev_puntero->led_cdev.ops=&led_fops;
	error=cdev_add(&led_dev_puntero->led_cdev, led_dev_numero, cuenta);

	if(error)
		printk(KERN_INFO "error $d al añadir led_dev");
		ioaddress_SIE = ioremap(ioaddress_SIE_BASE, ioaddress_SIZE);
		ioaddress_BSC1_SIE = ioremap(ioaddress_BSC1_BASE, ioaddress_BSC1_SIZE); //Mapeo para I2C
		printk(KERN_ALERT "ioaddress_SIE_BASE fue mapeado a: %p \n",ioaddress_SIE);
		printk(KERN_ALERT "ioaddress_BSC1_BASE fue mapeado a: %p \n",ioaddress_SIE);		
		iowrite32(0x00000002, ioaddress_SIE+address_Rpull);// habilita Resistencia pull_up 
		msleep(0.016);
		iowrite32(0x09CA0013, ioaddress_SIE+address_Pinpull); //Asigna la R pull_up a los pines
		msleep(0.016);
		iowrite32(0x00000000, ioaddress_SIE+address_Rpull);// quitar la señal de control 
		iowrite32(0x00000000, ioaddress_SIE+address_Pinpull); //quitar la señal de reloj	
		iowrite32(0X00000900, ioaddress_SIE+address_gpsel2); //Activar funcion ALT0 (I2c) en gpio 2-3

	return 0;
}

module_init(hello_init);

static void hello_exit(void){

	printk(KERN_ALERT "Adios mundo cruel\n");
	unregister_chrdev_region(led_dev_numero, cuenta);
	cdev_del(&led_dev_puntero->led_cdev);
	kfree(led_dev_puntero);
	kfree(buffer);
	iowrite32(0x00000000, ioaddress_SIE);
	iowrite32(0x00000000, ioaddress_BSC1_SIE);
	iowrite32(0x00000002, ioaddress_BSC1_SIE+I2C_S);
	
	if(on_off==1){
		iowrite32(0xFFFFFFFF, ioaddress_SIE+address_LED_off);}
	iounmap(ioaddress_SIE);	
	iounmap(ioaddress_BSC1_SIE);
}

module_exit(hello_exit);
