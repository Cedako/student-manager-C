#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>

//struct for the record
struct record{
    char name[20];
    short record;
};

void write_record(FILE *record, struct record u){
    record = fopen("../record.txt", "ab+");
    if(record == NULL){
        printf("Archivo no encontrado\n");
    }
    //variables for storing the inputs
    char name[20]; int rec;

    //record form
    printf("Enter the name: ");
    scanf(" %s", &name);
    strcpy(u.name,name); //stores variable inside the struct
    printf("Enter the record: ");
    scanf(" %d", &rec);
    u.record = rec; //stores variable inside the struct

    //stores the struct in the binary file
    fwrite(&u, sizeof(struct record), 1, record);
    printf("Done\n");
    fclose(record);
}

void search_record(FILE *record, struct record u){
    record = fopen("../record.txt","rb");
    if(record == NULL){
        printf("Archivo no encontrado\n");
    }

    int type;

    while (type != 0)
    {
        printf("Search...\n(1)By name\n(2)By record\n(3)Retrieve all\n(0)Go to main menu\n");
        printf("Type of search => "); scanf(" %d",&type);
        switch (type)
        {
        case 1: //Search by name
            /* code */
            break;
        case 2: //Search by record
            /* code */
            break;
        case 3: //Retrieve all
            //prints records until reaching the end of the file (EOF)
            while (fread(&u, sizeof(struct record), 1, record)){
                printf("Name is: %s\nAge is: %d\n", u.name,u.record);
            }
            printf("Done\n");
            break;
        case 0: //Exit search
            printf("Exiting to main menu...\n");
            break;
        default:
        printf("Error");
            break;
        }
    }
    fclose(record);
    
}

int main(){
    struct record usuario;
    //Creates pointer to store the file
    FILE *record_manager;
    int operation; //Stores the user operation
    printf("Welcome to the student grade system\nWhat will you do?\n");
    printf("0 - Nothing\n1 - Search\n2 - Add\n3 - Remove\n4 - Edit\n");

    //Asks the user what to do
    while (operation!=0){
        printf("Operation => ");
        scanf(" %d",&operation);
        if(operation==1){
            system("cls");
            search_record(record_manager, usuario); //searching
        } else if (operation==2){
            system("cls");
            write_record(record_manager, usuario); //adding
        } else if (operation==3){
            system("cls");
            write_record(record_manager, usuario); //removing
        } else if (operation==4){
            system("cls");
            write_record(record_manager, usuario); //editing
        } else if (operation==0) {
            system("cls");
            printf("Exiting...\n"); //exiting the system and closing the program
        } else {
            printf("error"); //error if operation does not exist
        }
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
