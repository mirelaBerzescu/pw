#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    int fis;
    int lit=0, cif=0;
    char buff;
    
    if(argc < 2)
    exit(1);
    
    fis = open(argv[1],O_RDONLY);
    
    while(read(fis,&buff,sizeof(char)))
    {
        if(isalpha(buff))
            lit++;
        else if(isdigit(buff))
                cif++;
    }
    close(fis);
    
    char newpath[100];
    strcpy(newpath,argv[2]);
    strcat(newpath,"/");
    strcat(newpath,argv[1]);
    
    char litS[10];
    char cifS[10];
    sprintf(litS,"%d",lit);
    sprintf(cifS,"%d",cif);
    
    char total[50] = "Litere: ";
    strcat(total,litS);
    strcat(total,"\nCifre: ");
    strcat(total,cifS);
    
    struct stat st;
    stat(newpath,&st);
    char uid[20];
    sprintf(uid,"%u",st.st_uid);
    printf("\n UID : %u",st.st_uid);
    
    strcat(total,"\nUser id: ");
    strcat(total, uid);
    
    
    int fis2;
    fis2 = creat(newpath,S_IRUSR | S_IWUSR);
    write(fis2,total,sizeof(total));
    close(fis2);
    
    return 0;
}
