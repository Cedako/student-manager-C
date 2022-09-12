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
    scanf(" %s", &name); //Error, only can enter 1 name
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
                //prints the new record, which copies the one to be deleted and changes .deleted to 1
                printf("Name is: %s\nAge is: %d\nStatus: %d\n", t.name,t.record,t.deleted);
                //prints current position inside the file
                printf("%d\n",ftell(record));
                //rolls back to the start of the deleted record
                fseek(record, -(long)sizeof(t), SEEK_CUR);
                //prints current position inside the file
                printf("%d\n",ftell(record));
                //overwrites the file, in order to make it "deleted"
                fwrite(&t, sizeof(t), 1, record);
                //prints current position inside the file
                printf("%d\n",ftell(record));
                //rolls back to the start of the now deleted record
                fseek(record, -(long)sizeof(t), SEEK_CUR);
                //reads the deleted record
                fread(&u, sizeof(struct record), 1, record);
                //prints current position inside the file
                printf("%d\n",ftell(record));
                //prints the name, record and status of the deleted file, if status is one, file will not appear in search
                printf("Name is: %s\nAge is: %d\nStatus: %d\n", u.name,u.record,u.deleted);
                printf("%s has been deleted",u.name);
                break;
            }
        }
    } else if (record_s){
        while (fread(&u, sizeof(struct record), 1, record)){
            if(u.record==record_s && !u.deleted){
                struct record t;
                strcpy(t.name,u.name);
                t.record = u.record;
                t.deleted = 1;
                fseek(record, -(long)sizeof(t), SEEK_CUR);
                fwrite(&t, sizeof(t), 1, record);
                printf("%d has been deleted\n",record_s);
                break;
            }
        }
    }
    
    printf("record removed succesfully\n");
    system("pause");
}

void wipe_file(FILE *record, struct record u){
    FILE* temp;
    char newname[] = "../record.bin";
    char oldname[] = "../temp.bin";
    record = fopen("../record.bin","rb+");
    temp = fopen("../temp.bin","wb");

    while (fread(&u, sizeof(struct record), 1, record)){
        if(!u.deleted){
            printf("%s\n",u.name);
            fwrite(&u, sizeof(struct record), 1, temp);
        } else {
            printf("%s deleted\n",u.name);
        }
    }
    printf("File has been wiped clean\n");
    fclose(record);
    fclose(temp);
    remove(newname);
    rename(oldname, newname);
    system("pause");
    
}

void search_record(FILE *record, struct record u){
    record = fopen("../record.bin","rb+"); //rb+ allows to overwrite the file
    if(record == NULL){
        printf("Archivo no encontrado\n");
    }

    int type,found;short record_s;char name_s[20];

    while (type != 0)
    {
        found=0;
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
                if(strcmp(name_s,u.name) == 0 && !u.deleted){
                    printf("Name is: %s\nAge is: %d\nStatus: %d\n", u.name,u.record,u.deleted);
                    printf("-------------------------\n");
                    found+=1;
                }
            }
            if (found == 0)
            {
                printf("No coincidences\n");
                system("pause");
            } else {
                printf("%d Coincidences\n",found);
                printf("What do you want to do?\n"); int option;
                printf("(1) Edit record\n(2) Delete record\n(0) Back to search menu\nOperation => ");
                scanf(" %d",&option);
                switch (option)
                {
                case 1:
                    printf("not aviable yet\n"); //next on the list
                    break;
                case 2:
                    system("cls");
                    delete_record(record,u,name_s,0);
                    break;
                case 0:
                    printf("Exiting to search menu...\n");
                    break;
                default:
                    printf("Error, invalid input\n");
                    break;
                }
            }
            break;
        case 2: //Search by record
            printf("Enter the record: "); scanf(" %d", &record_s);
            while (fread(&u, sizeof(struct record), 1, record)){
                if(u.record==record_s && !u.deleted){
                    printf("Name is: %s\nAge is: %d\n", u.name,u.record);
                    printf("-------------------------\n");
                    found+=1;
                }
            }
            if (found == 0)
            {
                printf("No coincidences\n");
                system("pause");
            } else {
                printf("%d Coincidences\n",found);
                printf("What do you want to do?\n"); int option;
                printf("(1) Edit record\n(2) Delete record\n(0) Back to search menu\nOperation => ");
                scanf(" %d",&option);
                switch (option)
                {
                case 1:
                    printf("not aviable yet\n"); //next on the list
                    break;
                case 2:
                    system("cls");
                    delete_record(record,u,"nothing",record_s); //Error:records that .record equals to 0 cant be deleted
                    break;
                case 0:
                    printf("Exiting to search menu...\n");
                    break;
                default:
                    printf("Error, invalid input\n");
                    break;
                }
            }
            type = 2;/*For some reason, type becomes 0 when in case 2, idk why, but this is the temporary fix*/
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
        printf("0 - Close system\n1 - Search\n2 - Add\n3 - Wipe stash\n");
        printf("Operation => ");
        scanf(" %d",&operation);
        if(operation==1){
            search_record(record_manager, usuario); //searching
        } else if (operation==2){
            system("cls");
            write_record(record_manager, usuario); //adding
        } else if (operation==3) {
            system("cls");
            printf("Wiping deleted records...\n"); //wiping records that have status 1 (deleted)
            wipe_file(record_manager, usuario);
            system("pause");
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

/* Things to do:
    change struct, record shall be ID
    while adding ID's shall be all different
    generate incremental ID's > 0 to solve the problem
    change struct, names shall be nicknames
    nicknames cannot be repeated, add validations
    since nicknames cannot be repeated, change the variable found
    ---------------------------------------------
    add the edit function
    users can edit the name
    ---------------------------------------------
    change terminology
    "deleted" users should be named different
    ---------------------------------------------
    consider removing some of the "pauses" in the system
*/
