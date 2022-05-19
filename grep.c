
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

bool grep(FILE *stream, char* match){
    char buffer[BUFSIZ];
    bool found = false;

    while(fgets(buffer, BUFSIZ, stream)){
        if(strstr(buffer, match) != NULL){
            fputs(buffer, stdout);
            found = true;
        }
    }
    return found;
}

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);                                    
    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;

    if(argc == 1){
        usage(1);
    }

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];                                                         
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {   
        char *arg = argv[argind++];
       
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }
    }

    char* match = argv[argc -1];
    return !grep(stdin, match);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
