/* 
 * File:   main.cpp
 * Author: jannis
 *
 * Created on 7. Juni 2014, 20:24
 */

#include <cstdlib>
#include <stdio.h>
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

using namespace std;

queue<char> x;
pthread_mutex_t mtx;

void* fillQuenue(void*) {
    long counter = 0;
    while (1) {
        if (x.size() > 500) {
            pthread_yield();

        } else {
            pthread_mutex_lock(&mtx);

            for (int i = 0; i < 100; i++) {
                if (counter % 16 == 0) {
                    x.push(0x00);
                    printf("%x ", x.back());

                    counter++;
                } else {
                    char character = rand() % 127 + 1;
                    //char character = 0;
                    if (character == 0) {
                        x.push(0x1B);
                        //printf("%x ", x.back());

                        x.push(character);
                        //printf("%x ", x.back());

                        x.push(0x30);
                        //printf("%x ", x.back());

                    } else {
                        x.push(character);
                        //printf("%x ", x.back());

                    }
                    counter++;
                }

            }
            //printf("\n");

            pthread_mutex_unlock(&mtx);
            //sleep(1);
            pthread_yield();
        }
    }

}

void* receive(void*) {

    while (1) {
        char chararr[100];
        if (x.size() < 20) {
          //  printf("Que leer \n");
            pthread_yield();
        } else {
            //printf("Que länge %l \n", x.size());
            cout << x.size() << endl;
            pthread_mutex_lock(&mtx);
            for (int i = 0; i < 16; i++) {
                char c = x.front();
                x.pop();
                chararr[i] = c;

                if (c == 0x1b) {
                    c = x.front();
                    x.pop();
                    chararr[i] = c;
                    x.pop();
                }
            }
            printf("Output ");
            for (int i = 0; i < 16; i++) {
                printf("%x ", chararr[i]);
            }
            printf(" \n");
            pthread_mutex_unlock(&mtx);

        }

    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    pthread_t t1, t2;
    pthread_mutex_init(&mtx, NULL);
    pthread_create(&t1, NULL, fillQuenue, NULL);
    pthread_create(&t2, NULL, receive, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    return 0;
}

