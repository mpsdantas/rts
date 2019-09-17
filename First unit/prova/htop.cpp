#define _GNU_SOURCE
#include <assert.h>
#include <signal.h>
#include <sched.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/time.h>
#include <stdbool.h>


using namespace std;

// void setAffinity(int pid, int cpu) {
//     cpu_set_t  mask;
//     CPU_ZERO(&mask);
//     CPU_SET(cpu, &mask);
//     sched_setaffinity(pid, sizeof(mask), &mask);
// }

void breakLines(){
    cout << "_______________________\n\n";
}

void showOptionsUser(){
    cout << "Escolha uma opção:" << endl;
    cout << "1 - Processos em execução." << endl;
    cout << "2 - Pausar processo." << endl;
    cout << "3 - Continuar processo." << endl;
    cout << "4 - Mudar prioridade do processo." << endl;
    cout << "5 - Escolher a cpu para um processo." << endl;
}

void monitorProcess(string filter){
    char sys[150];
    char text[17] = "ps -af -U $USER ";
    char cstr[filter.size() + 1];
    strcpy(sys, text);
    if(filter.length() > 0){
        strcpy(cstr, filter.c_str());
        strcat(sys, "| grep ");
        strcat(sys, cstr);
    }
    system(sys);
    sleep(3);
}

void stopProcess(int pid){
    kill(pid, SIGSTOP);
}

void continueProcess(int pid){
    kill(pid, SIGCONT);
}

void configuratePriorite(int pid, int priorite){
    setpriority(PRIO_PROCESS, pid, priorite);
}

int getPid(){
    int pid = 0;
    cout << "Informe o PID do processo:" << endl;
    cin >> pid;
    return pid;
}

int getPriorite(){
    int priorite = 0;
    cout << "Informe a nova prioridade do processo:" << endl;
    cin >> priorite;
    return priorite;
}

int getCpu(){
    int cpu = 0;
    cout << "Informe a nova cpu do processo:" << endl;
    cin >> cpu;
    return cpu;
}

int main(){
    int option = 0;
    int pid = 0;
    int priorite = 0;
    int cpu = 0;
    string filter;

    while(true){
        showOptionsUser();
        cin >> option;
        
        if(option == 1){
            cout << "Digite seu filtro: " << endl;
            cin >> filter;
            monitorProcess(filter);
        }
        if(option == 2){
            pid = getPid();
            cout << "Pausando processo " << pid;
            breakLines();
            stopProcess(pid);
        }
        if(option == 3){
            pid = getPid();
            cout << "Continuando processo " << pid << endl;
            breakLines();
            continueProcess(pid);
        }
        if(option == 4){
            pid = getPid();
            priorite = getPriorite();
            cout << "Setando a prioridade do processo " << pid << endl;
            configuratePriorite(pid, priorite);
            cout << "Nova prioridade do processo: " << getpriority(PRIO_PROCESS, pid) << endl;
            breakLines();
        }
        if(option == 5){
            pid = getPid();
            cpu = getCpu();
            cout << "Setando o processo para nova cpu " << pid << endl;
            //setAffinity(pid, cpu);
        }
    }
}