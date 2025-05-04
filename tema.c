#include "tema.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int copyfiles(const char *sname, const char *dname, struct stat *s)
{
   int sursa_fd= open(sname, O_RDONLY);
   if (sursa_fd < 0)
   {
      perror("eroare la open sursa");
      return -1;
   }
    int destinatie_fd = open(dname, O_WRONLY | O_CREAT | O_TRUNC, s->st_mode & 0777);
    if (destinatie_fd < 0)
    {
        perror("eroare la open destinatie");
        return -1;
    }
    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(sursa_fd, buffer, sizeof(buffer))) > 0)
    {
       
        if (write(destinatie_fd, buffer, bytes_read) != bytes_read)
        {
            perror("eroare la scriere");
            close(sursa_fd);
            close(destinatie_fd);
            return -1;
        }
    }
    if (bytes_read < 0)
    {
        perror("eroare la citire");
        close(sursa_fd);
        close(destinatie_fd);
        return 0;
    }
    close(sursa_fd);
    close(destinatie_fd);
    return 1;
    
}
int gasesc_extensia(const char *nume_fisier)
{
    
    char *extensia=strrchr(nume_fisier,'.');
    struct stat stare;
    if(strcmp(extensia,".txt")==0)
    {
        return 1;
    }
    else
    return 2;

}
void parcurg_rec(const char *nume_sursa, const char *nume_dest, char *param)
{

    DIR *dr;
    struct dirent *entryData;
    struct stat stare;
    char path[1000]="\0", path_destinatie[1000]="\0";
    dr = opendir(nume_sursa);
    while ((entryData = readdir(dr)) != NULL)
    {
        if (strcmp(entryData->d_name, ".") == 0 || strcmp(entryData->d_name, "..") == 0)
            continue;
        strcpy(path, nume_sursa);
        strcat(path, "/");
        strcat(path, entryData->d_name);

        strcpy(path_destinatie, nume_dest);
        strcat(path_destinatie, "/");
        strcat(path_destinatie, entryData->d_name);

        if (stat(path, &stare) == -1)
        {
            
            continue;
        }
        if (S_ISDIR(stare.st_mode))
        {
            printf("%s \n", path);
            mkdir(path_destinatie, 0777);
            chmod(path_destinatie, stare.st_mode);
            parcurg_rec(path, path_destinatie,param);
        }
        if (S_ISREG(stare.st_mode))
        {
            printf("%s ", entryData->d_name);
            if (gasesc_extensia(entryData->d_name) == 1)
            {
                printf("Este fisier .txt\n");
                FILE *f = fopen(path, "r");
                int nr_spatii = 0;
                char c;
                if (f == NULL)
                {
                    perror("eroare la fopen");
                    continue;
                }
               while((c=fgetc(f))!=EOF)
               {
                if(c==' ')
                {
                    nr_spatii++;
                }
               }
               printf("Numarul de spatii este: %d\n", nr_spatii);
               if(nr_spatii > atoi(param))
               {
                printf("Fisierul %s  are mai mult de %s spatii\n",entryData->d_name, param);
                char nume_legatura[1000];
                strcpy(nume_legatura, nume_sursa);  
                strcat(nume_legatura, "/spaces_");  
                strcat(nume_legatura, entryData->d_name);  
                symlink(path, nume_legatura);
               printf("S-a creat legatura simbolica %s\n", nume_legatura);
                fclose(f);
                
               }
               else
               {
                printf("Fisierul %s are mai putin de %s spatii\n",entryData->d_name, param);
                fclose(f);
               }
                

            }
         if(gasesc_extensia(entryData->d_name)!=1)
         {
            if (copyfiles(path, path_destinatie, &stare) == -1)
            {
                printf("Eroare la copierea fisierului: %s\n", path);
            }
            else
            {
                chmod(path_destinatie, stare.st_mode & 0444);
            }
         
        }
    }
    if(S_ISLNK(stare.st_mode))
{
    printf("%s ", entryData->d_name);
         printf("Este legatura simbolica\n");
}
    }
    
    closedir(dr);
}