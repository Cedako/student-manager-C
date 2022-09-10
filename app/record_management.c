#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>

//struct for the record
struct record{
    char name[20];
    short record;
    int deleted;
};

void write_record(FILE *record, struct record u){
    record = fopen("../record.bin", "ab+");
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
    u.deleted = 0;

    //stores the struct in the binary file
    printf("%d\n",ftell(record));
    fwrite(&u, sizeof(struct record), 1, record);
    printf("%d\n",ftell(record));
    printf("Done\n");
    system("pause");
    fclose(record);
}

void delete_record(FILE *record, struct record u,char name_s[20],short record_s){
    rewind(record);
    if(name_s!="nothing"){
       while (fread(&u, sizeof(struct record), 1, record)){
            if(strcmp(name_s,u.name) == 0 && !u.deleted){
                struct record t;
                strcpy(t.name,u.name);
                t.record = u.record;
                t.deleted = 1;
                printf("Name is: %s\nAge is: %d\nStatus: %d\n", t.name,t.record,t.deleted);
                printf("%d\n",ftell(record));
                fseek(record, -(long)sizeof(t), SEEK_CUR);
                printf("%d\n",ftell(record));
                fwrite(&t, sizeof(t), 1, record); //Problem: file is not overwritten, therefore, it doesn't change.
                printf("%d\n",ftell(record));
                fread(&u, sizeof(struct record), 1, record);
                printf("%d\n",ftell(record));
                printf("Name is: %s\nAge is: %d\nStatus: %d\n", u.name,u.record,u.deleted);
                break;
            }
        }
    } else if (record_s){
        while (fread(&u, sizeof(struct record), 1, record)){
            if(u.record==record_s && !u.deleted){
                u.deleted = 1;
                printf("%d has been deleted\n",record_s);
            }
        }
    }
    
    printf("record removed succesfully\n");
    
}

void wipe_file(FILE *record, struct record u){
    FILE* temp;
    char newname[] = "../record.bin";
    char oldname[] = "../temp.bin";
    record = fopen("../record.bin","rb");
    rewind(record);
    temp = fopen("../temp.bin","wb");

    while (fread(&u, sizeof(struct record), 1, record)){
        if(!u.deleted){
            fwrite(&u, sizeof(struct record), 1, temp);
        }
    }
    printf("Succesfully removed\n");
    fclose(temp);
    rename(oldname, newname);
    remove(oldname);
}

void search_record(FILE *record, struct record u){
    record = fopen("../record.bin","rb");
    if(record == NULL){
        printf("Archivo no encontrado\n");
    }

    int type,found=0;short record_s;char name_s[20];

    while (type != 0)
    {
        system("cls");
        rewind(record);
        printf("Search...\n(1)By name\n(2)By record\n(3)Retrieve all\n(0)Go to main menu\n");
        printf("Type of search => "); scanf(" %d",&type);

        switch (type)
        {
        case 1: //Search by name
            system("cls");
            printf("Search\n");
            printf("Enter the name: "); scanf(" %s", &name_s);
            while (fread(&u, sizeof(struct record), 1, record)){
                if(strcmp(name_s,u.name) == 0 ){
                    printf("Name is: %s\nAge is: %d\nStatus: %d\n", u.name,u.record,u.deleted);
                    printf("-------------------------\n");
                    found+=1;
                }
            }
            if (found == 0)
            {
                printf("No coincidences\n");
            } else {
                printf("%d Coincidences\n",found);
                printf("What do you want to do?\n"); int option;
                printf("(1) Edit record\n(2) Delete record\n(0) Back to search menu\nOperation => ");
                scanf(" %d",&option);
                switch (option)
                {
                case 1:
                    printf("not aviable yet\n");
                    break;
                case 2:
                    system("cls");
                    delete_record(record,u,name_s,0);
                    break;
                case 0:
                    printf("Exiting to search menu...\n");
                    break;
                default:
                    printf("Error, invalid input");
                    break;
                }
            }
            
            
            system("pause");
            break;
        case 2: //Search by record
            printf("Enter the record: "); scanf(" %d", &record_s);
            while (fread(&u, sizeof(struct record), 1, record)){
                if(u.record==record_s && !u.deleted){
                    printf("Name is: %s\nAge is: %d\n", u.name,u.record);
                    printf("-------------------------\n");
                }
            }
            type = 2;/*For some reason, type becomes 0 when in case 2, idk why, but this is the temporary fix*/
            printf("Done\n");
            system("pause");
            break;
        case 3: //Retrieve all
            //prints records until reaching the end of the file (EOF)
            while (fread(&u, sizeof(struct record), 1, record)){
                if(!u.deleted){
                    printf("Name is: %s\nAge is: %d\nStatus is: %d\n", u.name,u.record,u.deleted);
                    printf("-------------------------\n");
                }
            }
            printf("Done\n");
            system("pause");
            break;
        case 0: //Exit search
            printf("Exiting to main menu...\n");
            break;
        default:
            printf("Error\n");
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
    

    //Asks the user what to do
    while (operation!=0){
        system("cls");
        printf("0 - Close system\n1 - Search\n2 - Add\n");
        printf("Operation => ");
        scanf(" %d",&operation);
        if(operation==1){
            search_record(record_manager, usuario); //searching
        } else if (operation==2){
            system("cls");
            write_record(record_manager, usuario); //adding
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
