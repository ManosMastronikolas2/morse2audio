#include <stdio.h>
#include <stdlib.h>
#include "morse2audio.h"

int main(int argc, char* argv[]){

    if(argc<2){
        printf("Usage: ./morse2audio <filename>\n");
        return -1;
    }

    if(openFile(argv[1])!=0){
        printf("Could not open file! Exiting\n");
        return -1;
    }
    openEngine();
    playFile();

    return 0;
}