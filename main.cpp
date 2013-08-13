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
    strftime (buff, 80, "logs/DNN-%Y-%m-%d-%H-%M-%S.log", timeinfo);
    if (LOGGING)
        file = fopen (buff, "w");

    numNeurons = 0;

    NeuralNetwork* net = NULL;

    printf("> ---------------------\n"
			"> 1) Train OR gate behaviour\n"
			"> 2) Train AND gate behaviour\n"
			"> 3) Train XOR gate behaviour\n"
			"> 4) Train MNIST\n"
			"> 5) Empty\n"
			"> 6) Exit\n"
			"> 7) Load settings and create neural network\n"
			"> 8) Load new settings from config file\n"
			"> 9) Reset/Remake neural network\n"
			"> Press '0' to display menu\n"
			"> ---------------------\n"
			">Please enter your selection: ");

    int input = 0;
    scanf("%d", &input);
	while (input != 6) {
		switch (input) {
            case 1:
                if (net == NULL) {
                    printf ("You do not have an active Neural Network running.\n");
                }
                else {
                    net->trainOR();
                }
                break;
            case 2:
                if (net == NULL) {
                    printf ("You do not have an active Neural Network running.\n");
                }
                else {
                    net->trainAND();
                }
                break;
            case 3:
                if (net == NULL) {
                    printf ("You do not have an active Neural Network running.\n");
                }
                else {
                    net->trainXOR();
                }
                break;
            case 4:
                if (net == NULL) {
                    printf ("You do not have an active Neural Network running.\n");
                }
                else {
                    net->trainMNIST(200, 50);
                }
                break;
            case 5:

                break;
            case 7:
                read_config("settings.config");
                printf ("Settings successfully loaded.\n");
                if (net != NULL) {
                    printf ("Ending current Neural Network.\n");
                    delete net;
                    printf ("Neural Network successfully ended.\n");
                    logger (file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                }
                printf ("Starting new Neural Network:\n");
                net = new NeuralNetwork("reservoir_settings.config");
                printf ("New Neural Network successfully created.\n");
                break;
            case 8:
                read_config("settings.config");
                printf ("Settings successfully loaded.\n");
                break;
            case 9:
                if (net != NULL) {
                    printf ("Ending current Neural Network.\n");
                    delete net;
                    printf ("Neural Network successfully ended.\n");
                    logger (file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                }
                printf ("Starting new Neural Network:\n");
                net = new NeuralNetwork();
                printf ("New Neural Network successfully created.\n");
                break;
            case 0:
                printf("> ---------------------\n"
                        "> 1) Train OR gate behaviour\n"
                        "> 2) Train AND gate behaviour\n"
                        "> 3) Train XOR gate behaviour\n"
                        "> 4) Train MNIST\n"
                        "> 5) Empty\n"
                        "> 6) Exit\n"
                        "> 7) Load settings and create neural network\n"
                        "> 8) Load new settings from config file\n"
                        "> 9) Reset/Remake neural network\n"
                        "> Press '0' to display menu\n"
                        "> ---------------------\n"
                        ">Please enter your selection: ");
                break;
            default:
                printf("> Invalid input. Please try again.\n");
                break;
		}
		printf("\n>Please enter your selection: ");
		scanf("%d", &input);
	}
	printf ("Exiting...\n");
	if (net != NULL) {
        printf ("Ending current Neural Network.\n");
        delete net;
        printf ("Neural Network successfully ended.\n");
	}
    if (LOGGING)
        fclose (file);
    return 0;
}
