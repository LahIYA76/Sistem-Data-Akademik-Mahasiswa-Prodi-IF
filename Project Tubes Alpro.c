#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NORMAL  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define CYAN  "\x1B[36m"

struct data{
    char nim[10];
    char nama[30];
    char kelas[10];
};

typedef struct data data;

int directoryInfo() 
{
    FILE *fptr;

    fptr = fopen("dataMahasiswa", "r"); 
    fseek(fptr, 0, SEEK_END);   

    if(fptr==NULL)return 0;
    return ftell(fptr)/sizeof(data); 
}

void display(bool isAscending)
{
    system("cls");
    int pilihMenu, count=1, directory;
    FILE *fptr;
    data dt;
    fptr = fopen("dataMahasiswa", "r"); 

    directory = directoryInfo();   

    printf(NORMAL);
    printf("\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t| Total Data : %2d                                   |\n", directory);
    printf("\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t|"YELLOW"%-4s"NORMAL"| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", " No", "NIM", "Nama", "Kelas");
    printf("\t\t\t-----------------------------------------------------\n");

    if(isAscending){       
        while(fread(&dt, sizeof(data), 1, fptr))   
        {
            printf("\t\t\t| "YELLOW"%-3d"NORMAL"| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", count++, dt.nim, dt.nama, dt.kelas);
        }
    }else                   
    {
        fseek(fptr, -(sizeof(dt)), SEEK_END); 
        for(int i=1; i<=directory; i++){
            fread(&dt, sizeof(data), 1, fptr);  
            printf("\t\t\t| "YELLOW"%-3d"NORMAL"| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", count++, dt.nim, dt.nama, dt.kelas);
            fseek(fptr, -2*sizeof(data), SEEK_CUR); 
        }                                           
    }
    printf("\t\t\t-----------------------------------------------------\n");
    printf(NORMAL);
    fclose(fptr);
}

void editData()
{
    system("cls");
    FILE *fptr, *fptr1;     
    data dt;
    char nim[10];
    char temp;
    int found=0;

    fptr = fopen("dataMahasiswa", "r");     
    fptr1 = fopen("helper", "w");           
    printf("\n\t\t\t"YELLOW"Ubah Data"NORMAL);
    printf("\n\t\t\tMasukan NIM data yang akan diubah : ");
    scanf("%s", &nim);
    fflush(stdin);

    while(fread(&dt, sizeof(data), 1, fptr))    
    {
        if(strcmp(strlwr(dt.nim), strlwr(nim))==0)  
        {
            found=1;
            printf("\t\t\tEdit NIM? <y/n> : ");     
            scanf("%c", &temp);                     
            fflush(stdin);
            if(temp=='y' || temp=='Y')
            {
                printf(CYAN"\t\t\tMasukan NIM baru : ");
                scanf("%s", &dt.nim);
                fflush(stdin);
            }

            printf(NORMAL"\t\t\tEdit Nama? <y/n> : ");
            scanf("%c", &temp);
            fflush(stdin);
            if(temp=='y' || temp=='Y')
            {
                printf(CYAN"\t\t\tMasukan Nama baru : ");
                scanf("%s", &dt.nama);
                fflush(stdin);
            }

            printf(NORMAL"\t\t\tEdit Kelas? <y/n> : ");
            scanf("%c", &temp);
            fflush(stdin);
            if(temp=='y' || temp=='Y')
            {
                printf(CYAN"\t\t\tMasukan kelas baru : ");
                scanf("%s", &dt.kelas);
                fflush(stdin);
            }
        }
        fwrite(&dt, sizeof(data), 1, fptr1);        
    }
    fclose(fptr);
    fclose(fptr1);

    if(found==1)    
    {
        fptr1 = fopen("helper", "r");
        fptr = fopen("dataMahasiswa", "w");

        while(fread(&dt, sizeof(data), 1, fptr1)) fwrite(&dt, sizeof(data), 1, fptr);   
        printf("\n\t\t\t"GREEN"Data berhasil diubah"NORMAL);
    }else
    {
        printf("\n\t\t\t"RED"Data tidak ditemukan"NORMAL);
    }

    fclose(fptr);
    fclose(fptr1);
}

void deleteData()
{
    system("cls");          
    FILE *fptr, *fptr1;     
    data dt;
    char nim[10];
    bool isDeleted=false;   

    fptr = fopen("dataMahasiswa", "r"); 
    fptr1 = fopen("helper", "w+");      

    printf(YELLOW"\n\t\t\tHapus Data"NORMAL);
    printf(CYAN"\n\t\t\tMasukan NIM data yang akan dihapus : ");
    scanf("%s", &nim);
    fflush(stdin);

    while(fread(&dt, sizeof(data), 1, fptr)){   
        if(strcmp(dt.nim, nim)!=0){                 
            fwrite(&dt, sizeof(data), 1, fptr1);    
        }
        if(strcmp(dt.nim, nim)==0){                 
            isDeleted = true;                       
        }
    }
    fclose(fptr);
    fclose(fptr1);

    if(isDeleted){                                  
        fptr1 = fopen("helper", "r");            
        fptr = fopen("dataMahasiswa", "w");
        while(fread(&dt, sizeof(data), 1, fptr1)){  
            fwrite(&dt, sizeof(data), 1, fptr);
        }
        printf(GREEN"\n\t\t\tData berhasil dihapus"NORMAL);
    }else
    {
        printf(RED"\n\t\t\tData tidak ditemukan"NORMAL);
    }
    fclose(fptr);
    fclose(fptr1);
}

void tambahData()
{

    system("cls");
    FILE *fptr;
    data dt;                       
    fptr = fopen("dataMahasiswa","a");      
    printf(YELLOW"\n\t\t\tMasukan data\n"NORMAL);

    printf("\t\t\tMasukan NIM : ");
    scanf("%s", &dt.nim);
    fflush(stdin);

    printf("\t\t\tMasukan nama : ");
    gets(dt.nama);

    printf("\t\t\tMasukan kelas : ");
    scanf("%s", &dt.kelas);

    printf("\n\n\t\t\t"GREEN"Data berhasil ditambahkan"NORMAL);
    fwrite(&dt, sizeof(data), 1, fptr);     
    fclose(fptr);
}

void cariData()
{
    system("cls");
    FILE *fptr;
    data dt;
    int pilihMenu;
    bool isFound=false;     
    char nim[10], nama[30]; 
    fptr = fopen("dataMahasiswa", "r"); 

    printf(YELLOW"\n\t\t\tCari data berdasarkan?"NORMAL);
    printf("\n\t\t\t1) NIM");
    printf("\n\t\t\t2) Nama");
    printf(CYAN"\n\t\t\tMasukan pilihan : ");
    scanf("%d", &pilihMenu);
    fflush(stdin);
    system("cls");

    if(pilihMenu==1){
        printf(YELLOW"\n\t\t\tCari berdasarkan NIM"NORMAL);
        printf(CYAN"\n\t\t\tMasukan NIM : ");
        scanf("%s", &nim);

        while(fread(&dt, sizeof(data), 1, fptr)){       
            if(strcmp(strlwr(dt.nim), strlwr(nim))==0){ 
                isFound=true;                           
                printf(NORMAL);                                                         
                printf("\t\t\t------------------------------------------------\n");
                printf("\t\t\t| Searching by NIM                             |\n");
                printf("\t\t\t------------------------------------------------\n");
                printf("\t\t\t| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", "NIM", "Nama", "Kelas");
                printf("\t\t\t------------------------------------------------\n");
                printf("\t\t\t| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", dt.nim, dt.nama, dt.kelas);
                printf("\t\t\t------------------------------------------------\n");
            }
        }
        if(!isFound) printf(RED"\n\t\t\tData tidak ditemukan!"NORMAL);
    }else
    if(pilihMenu==2){
        printf(YELLOW"\n\t\t\tCari berdasarkan Nama"NORMAL);
        printf(CYAN"\n\t\t\tMasukan Nama : "NORMAL);
        fflush(stdin);
        gets(nama);

        while(fread(&dt, sizeof(data), 1, fptr)){           
            if(strcmp(strlwr(dt.nama), strlwr(nama))==0){
                isFound=true;
                printf(NORMAL);
                printf("\t\t\t------------------------------------------------\n");
                printf("\t\t\t| Searching by Nama                            |\n");
                printf("\t\t\t------------------------------------------------\n");
                printf("\t\t\t| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", "NIM", "Nama", "Kelas");
                printf("\t\t\t------------------------------------------------\n");
                printf("\t\t\t| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", dt.nim, dt.nama, dt.kelas);
                printf("\t\t\t------------------------------------------------\n");
            }
        }
        if(!isFound) printf(RED"\n\t\t\tData tidak ditemukan!"NORMAL);      
    }
    fclose(fptr);
}

void sortingData(bool isAscending)
{
    system("cls");
    int pilihMenu, count=1;
    int banyakData=directoryInfo(); 
    FILE *fptr;
    data dt;
    data dt2[banyakData];   
    data temp[1];           
    fptr = fopen("dataMahasiswa", "r");

    while(fread(&dt, sizeof(data), 1, fptr))    
    {
        dt2[count] = dt;    
        count++;            
    }

    if(isAscending){    
        for(int x=1; x<=banyakData; x++){           
            for(int y=1; y<=banyakData-x; y++){
                if(atoi(dt2[y].nim) > atoi(dt2[y+1].nim)){  
                    temp[1] = dt2[y];                 
                    dt2[y] = dt2[y+1];
                    dt2[y+1] = temp[1];
                }
            }
        }
    }else          
    {
        for(int x=1; x<=banyakData; x++){
            for(int y=1; y<=banyakData-x; y++){
                if(atoi(dt2[y].nim) < atoi(dt2[y+1].nim)){
                    temp[1] = dt2[y];
                    dt2[y] = dt2[y+1];
                    dt2[y+1] = temp[1];
                }
            }
        }
    }

    printf(NORMAL);         
    printf("\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t| Total Data : %2d                                   |\n", banyakData);
    printf("\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t|"YELLOW"%-4s"NORMAL"| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", " No", "NIM", "Nama", "Kelas");
    printf("\t\t\t-----------------------------------------------------\n");
    for(int x=1; x<=banyakData; x++){
        printf("\t\t\t| "YELLOW"%-3d"NORMAL"| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", x, dt2[x].nim, dt2[x].nama, dt2[x].kelas);
    }
    printf("\t\t\t-----------------------------------------------------\n");
}

int main()
{

    int pilihMenu;
    bool isClose = true;
    while(isClose){
        system("cls");
        printf("\n\t\t\t---------------------------------");
        printf("\n\t\t\t|] "YELLOW"Data Akademik Kemahasiswaan"NORMAL" [|");
        printf("\n\t\t\t|]  "YELLOW"program studi informatika"NORMAL"  [|");
        printf("\n\t\t\t---------------------------------\n");
        printf("\n\t\t\t1) Data Mahasiswa");
        printf("\n\t\t\t2) Pengelompokan Data");
        printf(RED"\n\t\t\t3) Keluar"NORMAL);
        printf(CYAN);
        printf("\n\t\t\tMasukan pilihan ");
        scanf("%d", &pilihMenu);
        printf(NORMAL);

        if(pilihMenu==1){
            system("cls");
            printf("\n\t\t\t------------------------------");
            printf(YELLOW"\n\t\t\t| Data Mahasiswa Informatika |"NORMAL);
            printf("\n\t\t\t------------------------------");

            display(true);
            printf("\n\t\t\t1) Tambah Mahasiswa");
            printf("\n\t\t\t2) Edit Data Mahasiswa");
            printf("\n\t\t\t3) Delete Data Mahasiswa");
            printf("\n\t\t\t4) Cari Mahasiswa");
            printf(RED"\n\t\t\t5) Kembali"NORMAL);
            printf(CYAN);

            printf("\n\t\t\tMasukan pilihan ");
            scanf("%d", &pilihMenu);
            printf(NORMAL);

            if(pilihMenu==1){
                tambahData();
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==2){
                editData();
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==3){
                deleteData();
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==4){
                cariData();
                printf("\n\t\t\t");
                system("pause");
            }else{

            }

        }else
        if(pilihMenu==2){
            system("cls");
            printf("\n\t\t\t----------------------");
            printf(YELLOW"\n\t\t\t| Pengelompokan Data |"NORMAL);
            printf("\n\t\t\t----------------------");

            printf("\n\t\t\t1) Berdasarkan data terbaru");
            printf("\n\t\t\t2) Berdasarkan data terlama");
            printf("\n\t\t\t3) NIM terendah");
            printf("\n\t\t\t4) NIM tertinggi");
            printf(RED"\n\t\t\t5) Kembali"NORMAL);
            printf(CYAN);

            printf("\n\t\t\tMasukan pilihan ");
            scanf("%d", &pilihMenu);
            printf(NORMAL);

            if(pilihMenu==1){
                display(false);
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==2){
                display(true);
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==3){
                sortingData(true);
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==4){
                sortingData(false);
                printf("\n\t\t\t");
                system("pause");
            }else{

            }
        }else
        {
            exit("0");
        }
    }

return 0;
}