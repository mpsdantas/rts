/**
 * Autor: Tiago Fernandes de Miranda
 * Universidade Federal do Rio Grande do Norte
 */

// Digitais que funcionam: 61, 22, 27, 65, 46, 47, 26, 23, 44, 45, 67, 66, 69, 68

#include <iostream>
#include <pthread.h>
#include "./BlackGPIO/BlackGPIO.h"
#include "./ADC/Adc.h"
#include <stdlib.h> 
#include <time.h>   
#include <unistd.h>
// Inclua as classes que achar necessario

using namespace BlackLib;
using namespace std;

void *tem1(void *arg);
void *tem2(void *arg);
void *tem3(void *arg);
void *tem4(void *arg);


pthread_mutex_t work_mutex1;
pthread_mutex_t work_mutex2;
pthread_mutex_t work_mutex3;
pthread_mutex_t work_mutex4;
pthread_mutex_t work_mutex5;

int main(int argc, char * argv[]){

    int res;    
 
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

    res = pthread_mutex_init(&work_mutex3, NULL);

    if (res != 0) {
        perror("A Craição do mutex3");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&work_mutex4, NULL);

    if (res != 0) {
        perror("A Craição do mutex4");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&work_mutex5, NULL);

    if (res != 0) {
        perror("A Craição do mutex5");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, tem1, NULL);
    if (res != 0) {
        perror("A Craição da Thread 1 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, tem2, NULL);
    if (res != 0) {
        perror("A Craição da Thread 2 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, tem3, NULL);
    if (res != 0) {
        perror("A Craição da Thread 3 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, tem4, NULL);
    if (res != 0) {
        perror("A Craição da Thread 4 falhou");
        exit(EXIT_FAILURE);
    }
    
    while (true)
    {

    }
    return 0;
}

void *tem1(void *arg) {
    ADC leitura = ADC(AIN6);
    // trem 2

    
    BlackGPIO saida1(GPIO_46, output);
    BlackGPIO saida2(GPIO_65, output);
    BlackGPIO saida3(GPIO_47, output);
    BlackGPIO saida4(GPIO_26, output);
    while (true)
    {
        int p = int(leitura.getPercentValue())/10;
        int tempo = 100000 * p;
        saida4.setValue(low);
        saida1.setValue(high);
        pthread_mutex_unlock(&work_mutex5);
        saida2.setValue(low);
        saida3.setValue(low);
        usleep(tempo);

        pthread_mutex_lock(&work_mutex4);
        saida1.setValue(low);
        saida2.setValue(high);
        saida3.setValue(low);
        saida4.setValue(low);
        usleep(tempo);

        pthread_mutex_lock(&work_mutex2);
        saida2.setValue(low);
        saida3.setValue(high);
        pthread_mutex_unlock(&work_mutex4);
        saida1.setValue(low);
        saida4.setValue(low);
        usleep(tempo);

        pthread_mutex_lock(&work_mutex5); 
        saida3.setValue(low);
        saida4.setValue(high);
        pthread_mutex_unlock(&work_mutex2);
        saida2.setValue(low);
        saida1.setValue(low);
        usleep(tempo);
    }
}

void *tem2(void *arg) {
    //trem 1
    ADC leitura = ADC(AIN5);
    BlackGPIO saida1(GPIO_22, output);
    BlackGPIO saida2(GPIO_61, output);
    BlackGPIO saida3(GPIO_27, output);
    while (true)
    {
        int p = int(leitura.getPercentValue())/10;
        int tempo = 100000 * p;

        saida3.setValue(low);
        saida1.setValue(high);
        pthread_mutex_unlock(&work_mutex4);
        saida2.setValue(low);
        usleep(tempo);

        pthread_mutex_lock(&work_mutex3);
        saida1.setValue(low);
        saida2.setValue(high);
        saida3.setValue(low);
        usleep(tempo);

        pthread_mutex_lock(&work_mutex4);
        saida2.setValue(low);
        saida3.setValue(high);
        pthread_mutex_unlock(&work_mutex3);
        saida1.setValue(low);
        usleep(tempo);
    }
}

void *tem3(void *arg) {
    ADC leitura = ADC(AIN0);
    BlackGPIO saida1(GPIO_44, output);
    BlackGPIO saida2(GPIO_23, output);
    BlackGPIO saida3(GPIO_45, output);
    while (true)
    {
        int p = int(leitura.getPercentValue())/10;
        int tempo = 100000 * p;
        saida3.setValue(low);
        saida1.setValue(high);
        pthread_mutex_unlock(&work_mutex1);
        saida2.setValue(low);
        usleep(tempo);
        
        pthread_mutex_lock(&work_mutex5);
        saida1.setValue(low);
        saida2.setValue(high);
        saida3.setValue(low);
        usleep(tempo);


        pthread_mutex_lock(&work_mutex1);
        saida2.setValue(low);
        saida3.setValue(high);
        pthread_mutex_unlock(&work_mutex5);      
        saida1.setValue(low);
        usleep(tempo);
    }
}

void *tem4(void *arg) {
    ADC leitura = ADC(AIN1);

    BlackGPIO saida1(GPIO_69, output);
    BlackGPIO saida2(GPIO_66, output);
    BlackGPIO saida3(GPIO_67, output);
    BlackGPIO saida4(GPIO_68, output);
    while (true)
    {
        int p = int(leitura.getPercentValue())/10;
        int tempo = 100000 * p;
        saida4.setValue(low);
        saida1.setValue(high);
        pthread_mutex_unlock(&work_mutex3);
        saida2.setValue(low);
        saida3.setValue(low);
        usleep(tempo);

        pthread_mutex_lock(&work_mutex3);
        pthread_mutex_lock(&work_mutex2);
        pthread_mutex_lock(&work_mutex1);
        saida1.setValue(low);
        saida2.setValue(high);
        saida3.setValue(low);
        saida4.setValue(low);
        usleep(tempo);

        saida2.setValue(low);
        saida3.setValue(high);
        pthread_mutex_unlock(&work_mutex1);
        saida1.setValue(low);
        saida4.setValue(low);
        usleep(tempo);

        saida3.setValue(low);
        saida4.setValue(high);
        pthread_mutex_unlock(&work_mutex2);
        saida2.setValue(low);
        saida1.setValue(low);
        usleep(tempo);
    }
}