/**
 * Autor: Tiago Fernandes de Miranda
 * Universidade Federal do Rio Grande do Norte
 */

#include <iostream>
#include <pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <stdlib.h> 
#include <time.h>   
#include <unistd.h>
// Inclua as classes que achar necessario

using namespace std;

int getRandomNumber(){
    srand(time(NULL));
    return rand() % 2;
}

bool canBeRunning(bool loser, int round){
    return !loser && round != 16
}

void displaySequenceOfLeds(BlackGPIO saida1, BlackGPIO saida2, int round, int *numbers){
    for(int i = 0; i<round; i++){
        if(numbers[i]==0){
            saida1.setValue(high);
        }
        if(numbers[i]==1){
            saida2.setValue(high);
        }
        sleep(1);
    }
}

void displayGamerOver(BlackGPIO saida1, BlackGPIO saida2){
    saida1.setValue(high);
    saida2.setValue(high);
}

void displayLed(int led, BlackGPIO saida1, BlackGPIO saida2){
    if(led == 0){
        saida1.setValue(high);
    }
    if(led == 1){
        saida2.setValue(high); 
    }
}

bool validateInputData(std:string entrada1Value, std:string entrada2Value){
    if(entrada1Value == "1" && entrada2Value == "1"){
        displayGamerOver(saida1, saida2);
        return false;
    }
    return true;
}

int castingValuesOfInput(std:string entrada1Value, std:string entrada2Value){
    if(entrada1Value == "1"){
        return 0;
    }
    if(entrada2Value == "1"){
        return 1;
    }
}

void clearDataReadInput(std:string &entrada1Value, std:string &entrada2Value){
    entrada1Value = "0";
    entrada2Value = "0";
}   

int main(int argc, char * argv[]){
    BlackGPIO saida1(GPIO_66, output);
    BlackGPIO saida2(GPIO_69, output);
    BlackGPIO entrada1(GPIO_67, input);
    BlackGPIO entrada2(GPIO_68, input);
    std:string entrada1Value = "0";
    std:string entrada2Value = "0";
    int numbers[16];
    int round = 1;
    bool loser = false;
    
    while (canBeRunning(loser, round)){
        numbers[round-1] = getRandomNumber();
        displaySequenciOfLeds(saida1, saida2, round, numbers);
        
        for(int i = 0; i<round; i++){
            while(entrada1Value == "0" && entrada1Value == "0"){
                entrada1Value = entrada1.getValue();
                entrada2Value = entrada2.getValue();
            }

            bool validInputData = validateInputData(entrada1Value, entrada2Value);
            if(!validInputData){
                displayGamerOver(saida1, saida2);
                loser = true;
                break;
            }

            int inputData = castingValuesOfInput(entrada1Value, entrada2Value); 
            displayLed(inputData, saida1, saida2);

            if(inputData != numbers[i]){
                displayGamerOver(saida1, saida2);
                loser = true;
                break;
            }
            clearDataReadInput(entrada1Value, entrada2Value);
        }
        round++;
    }

    if(!loser){
        while(1){
            displayLed(0, saida1, saida2);
            displayLed(1, saida1, saida2);
            sleep(1);
        }
    }
}
