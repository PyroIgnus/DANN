/*
    Dynamic Artificial Neural Network
    Created by Jonathon Wong
    Contributors: Rose Li, Adam Suban-Loewen, Andrew Pelegris, Michael Chiou
    Date: 2013
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "NeuralNetwork.h"
#include "utils.h"
#include "global.h"

int main(int argc, char *argv[]) {

    char buff[50];
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime (buff, 80, "DNN-%Y-%m-%d-%H-%M-%S.log", timeinfo);
    if (LOGGING)
        file = fopen (buff, "w");

    printf ("Starting Neural Network:\n");
    NeuralNetwork* net = new NeuralNetwork();

    net->trainOR();
    net->trainAND();

    printf ("Ending Neural Network.\n");
    delete net;
    printf ("Neural Network successfully ended.\n");
    if (LOGGING)
        fclose (file);
    return 0;
}
