/**
 * Autor: Tiago Fernandes de Miranda
 * Universidade Federal do Rio Grande do Norte
 */

#include <iostream>
#include <pthread.h>
#include "./BlackGPIO/BlackGPIO.h"
#include "./ADC/Adc.h"
#include <stdlib.h> 
#include <time.h>   
#include <unistd.h>
// Inclua as classes que achar necessario

using namespace BlackLib;

void *tem1(void *arg);
void *tem2(void *arg);
void *tem3(void *arg);


pthread_mutex_t work_mutex1;
pthread_mutex_t work_mutex2;

int main(int argc, char * argv[]){

    int res;
    // ADC teste = ADC(AIN5);
    // ADC teste1 = ADC(AIN1);
    // ADC teste2 = ADC(AIN0);

    // int pot[3] = {2, 2, 2};

    // pot[0] = int(teste.getPercentValue())/10;
    // pot[1] = int(teste1.getPercentValue())/10;
    // pot[2] = int(teste2.getPercentValue())/10;
    /* code */


    
 
    pthread_t a_thread;
    res = pthread_mutex_init(&work_mutex1, NULL);

    if (res != 0) {
        perror("A Craição do mutex1");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&work_mutex2, NULL);

    if (res != 0) {
        perror("A Craição do mutex2");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, tem1, NULL);
    if (res != 0) {
        perror("A Craição da Thread falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, tem2, NULL);
    if (res != 0) {
        perror("A Craição da Thread falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, tem3, NULL);
    if (res != 0) {
        perror("A Craição da Thread falhou");
        exit(EXIT_FAILURE);
    }
    
    while (true)
    {
    }
    return 0;
}

void *tem1(void *arg) {
    ADC leitura = ADC(AIN1);

    
    BlackGPIO saida1(GPIO_66, output);  // direita
    BlackGPIO saida2(GPIO_67, output);  // baixo
    BlackGPIO saida3(GPIO_68, output);  // esquerda
    BlackGPIO saida4(GPIO_69, output);  // cima
    while (true)
    {
        int p = int(leitura.getPercentValue())/10;
        int tempo = 100000 * p;
        // std::cout << p << endl;
        saida1.setValue(high);
        saida2.setValue(low);
        saida3.setValue(low);
        saida4.setValue(low);
        pthread_mutex_lock(&work_mutex2);
        usleep(tempo);
        saida2.setValue(high);
        saida1.setValue(low);
        pthread_mutex_unlock(&work_mutex2);
        saida3.setValue(low);
        saida4.setValue(low);
        usleep(tempo);
        saida3.setValue(high);
        saida1.setValue(low);
        saida2.setValue(low);
        saida4.setValue(low);
        pthread_mutex_lock(&work_mutex1);
        usleep(tempo);
        saida4.setValue(high);
        saida3.setValue(low);
        pthread_mutex_unlock(&work_mutex1);
        saida2.setValue(low);
        saida1.setValue(low);
        usleep(tempo);
    }
}

void *tem2(void *arg) {
    ADC leitura = ADC(AIN0);
    BlackGPIO saida1(GPIO_44, output);
    BlackGPIO saida2(GPIO_45, output); // cima
    while (true)
    {
        int p = int(leitura.getPercentValue())/10;
        int tempo = 100000 * p;
        saida1.setValue(high);
        saida2.setValue(low);
        pthread_mutex_lock(&work_mutex2);
        usleep(tempo);
        saida2.setValue(high);
        pthread_mutex_unlock(&work_mutex2);
        saida1.setValue(low);
        usleep(tempo);
    }
}

void *tem3(void *arg) {
    ADC leitura = ADC(AIN5);
    BlackGPIO saida1(GPIO_27, output); // cima
    BlackGPIO saida2(GPIO_65, output);
    while (true)
    {
        int p = int(leitura.getPercentValue())/10;
        int tempo = 100000 * p;
        saida2.setValue(high);
        saida1.setValue(low);
        pthread_mutex_lock(&work_mutex1);
        usleep(tempo);
        saida1.setValue(high);
        saida2.setValue(low);
        pthread_mutex_unlock(&work_mutex1);
        usleep(tempo);
    }
}