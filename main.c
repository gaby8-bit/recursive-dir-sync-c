#include "tema.h"

int main(int argc, char *argv[])
{
    struct stat stare_sursa;
    if (argc != 4)
    {
        printf("Directorul sursa, destinatie si numarul natural trebuie introduse in linia de comanda \n");
        exit(0);
    }
    if (stat(argv[1], &stare_sursa) == -1)
    {
        perror("Eroare la stat pe sursa");
        exit(1);
    }
    struct stat stare_destinatie;
    if (stat(argv[2], &stare_destinatie) == -1)
    {
        mkdir(argv[2], 0777);
        chmod(argv[2], stare_sursa.st_mode);
    }
    parcurg_rec(argv[1], argv[2],argv[3]);
    return 0;
}