/* 
 * File:   main.cpp
 * Author: jannis
 *
 * Created on 7. Juni 2014, 20:24
 */

#include <cstdlib>
#include <stdio.h>

using namespace std;
void stuff(const char* input);
void destuff(const char* input);
char* prepareString(const char* input);


void stuff(const char* input) {


}

void destuff(const char* input) {


}

char* prepareString(const char* input){
    int length = 0;
    char * buffer;
    while(input[length] != 0){
        length++;
    }
    printf("Streamlength: %i \n", length);
    buffer = (char*) malloc (length+1);
    
    int i = 0;
    //TODO: add 0x00 + length + postfix decrease malloc
    while(i < length){
        buffer[i] = input[i];
        i++;
    }
    return buffer;
}



/*
 * 
 */
int main(int argc, char** argv) {
    const char* progName = argv[0];
    const char* stream = argv[1];

    // handle input parameters
    if (argc != 2) {
        printf("Zu wenige Parameter");
        exit(EXIT_FAILURE);
    }
    printf("Prog: %s \nInput: %s", progName, stream);
    char* output = prepareString(stream);
    printf("Output: %s", output);

    return 0;
}

