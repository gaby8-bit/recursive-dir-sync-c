#include <sys/stat.h>

int copyfiles(const char *sname, const char *dname, struct stat *s);
int gasesc_extensia(const char *nume_fisier);
void parcurg_rec(const char *nume_sursa, const char *nume_dest, char *param);