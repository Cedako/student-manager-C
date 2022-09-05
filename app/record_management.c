#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void write_record(FILE *record){
    record = fopen("../record.txt", "a+");
    if(record == NULL){
        printf("Archivo no encontrado\n");
    }

    char mensaje[100] = "Hola mundo!\n";
    float numero = 3.14;
    fputc('G', record);
    fputc('o', record);
    fputc('l', record);
    fputc('\n', record);
    fputs(mensaje, record);
    fprintf(record,"Esto es un numero con formato %3.3f\n%3.3f\n",numero,numero);
    fclose(record);
}

void read_record(FILE *record){
    record = fopen("../record.txt","r");
    if(record == NULL){
        printf("Archivo no encontrado\n");
    }

    float numero = 0.0;
    char buffer[100] = "";
    char letra;
    int i;
    for(i = 0; i<4;i++){
    letra = fgetc(record);
    printf("%c",letra);
    }
    fgets(buffer,100,record);
    printf("%s\n",buffer);//segunda linea del documento
    fgets(buffer,100,record);
    printf("%s\n",buffer);//tercera linea del documento
    fscanf(record, "%f", &numero);
    printf("%f\n",numero);//lee el vaor numerico y lo guarda en un float
    fclose(record);
}

int main(){
    //Crea un puntero para almacenar un archivo.
    FILE *record_manager;
    char operation;
    printf("Welcome to the student grade system\nWhat will you do? ");
    scanf(" %c",&operation);
    if(operation=='r'){
        read_record(record_manager);
    } else if (operation=='a'){
        write_record(record_manager);
    } else {
        printf("error\n");
    }

    system("pause");
    return 0;
}
/*
r — abre el archivo en modo de solo lectura.
w — abre el archivo para escritura (si no existe lo crea, si existe lo destruye).
a — abre el archivo para agregar información (si no existe lo crea).
r+ — abre el archivo para lectura/escritura (comienza al principio del archivo).
w+ — abre el archivo para lectura/escritura, sobre-escribe el archivo si este ya existe o lo crea si no).
a+ — abre el archivo para lectura/escritura (se sitúa al final del archivo).
Si vamos a trabajar con archivos binarios usamos la letra b así que los modos de acceso quedan “rb”, “wb”, “ab”, “rb+”, “wb+”, “ab+”.
*/

//Rebobina el cursor del archivo, lo devuelve al inicio.
    //rewind(record_manager);

    //Coloca el cursor a 300 bits del inicio.
    //fseek(record_manager, 300, SEEK_SET);

    //Coloca el cursor a 200 bits del final.
    //fseek(record_manager, 200, SEEK_END);

    //Coloca el cursor a 5 bits de la posicion anterior.
    //fseek(record_manager, 5, SEEK_CUR);

    //Devuelve 1 si nos encontramos al final del archivo, 0 si no.
    //feof(record_manager);

    //Cierra el archivo
    //fclose(record_manager);

    //fgetc() permite leer un carácter desde el archivo, recibe un parámetro y es la variable del archivo. Devuelve el carácter leído.
    //fgets() lee cadenas completas desde el archivo, hasta que encuentra un retorno de carro \n o un eof. Acepta tres parámetros el nombre de el arreglo de caracteres donde se va a guardar lo leído, cantidad de bytes a leer y variable de archivo.
    //fscanf() funciona de la misma forma que un scanf() tradicional pero con un parámetro al principio que indica el archivo a leer.
    
    //fprintf() funciona de la misma forma que printf() pero su primer parámetro es la variable de archivo.
    //fputc() escribe un carácter en el archivo, recibe dos parámetros, el carácter a escribir y la variable de archivo.
    //fputs() escribe una cadena en el archivo, recibe dos parámetros, la cadena a escribir, y la variable de archivo.

    //fputc() escribe un carácter en el archivo, recibe dos parámetros, el carácter a escribir y la variable de archivo.
    //fputs() escribe una cadena en el archivo, recibe dos parámetros, la cadena a escribir, y la variable de archivo.
    //fprintf() funciona de la misma forma que printf() pero su primer parámetro es la variable de archivo.
