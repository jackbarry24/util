
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int walk(const char *root) {
    /* Open directory handle */
    DIR *d = opendir(root); //open
    if (!d) {
    	fprintf(stderr, "%s\n", strerror(errno)); //error
    	return EXIT_FAILURE;
    }

    for (struct dirent *e = readdir(d); e; e = readdir(d)) {
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) {
            continue;
        }

      
	if (e->d_type != DT_REG) {
	    continue;
        }

        
        char path[BUFSIZ];
        sprintf(path, "%s/%s", root, e->d_name );

	struct stat s;
	if (stat(path, &s) < 0) {
	    fprintf(stderr, "%s\n", strerror(errno));
	    continue;
        }

    
	printf("%s %lu\n", e->d_name, s.st_size);
    }

    
    closedir(d);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    char *path = ".";
    if (argc > 1) {
        path = argv[1];
    }

    return walk(path);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
