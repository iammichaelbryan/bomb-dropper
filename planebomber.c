//author Michael Bryan
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define FUEL 100
#define FUEL_CONSUMPTION_RATE 5
#define FUEL_REPORT_RATE 3

volatile sig_atomic_t fuel = FUEL;
volatile sig_atomic_t in_flight = 0; // false = 0, true = 1 // Decided to have a variable to track the state of whether any planes were launched

void handle_bomb(int sig) {
    printf("\nBomber %d to base, bombs away!\n\n", getpid());
    printf("Enter command (l)aunch, (r)efuel, (b)omb, (q)uit: ");
}

void refuel(int sig) {
    fuel = FUEL;
    printf("\nPlane %d has been refueled\n\n", getpid());
    printf("Enter command (l)aunch, (r)efuel, (b)omb, (q)uit: ");

}

void plane() {
    in_flight = 1;
    printf("\nPlane %d was launched\n\n", getpid());
    printf("Enter command (l)aunch, (r)efuel, (b)omb, (q)uit: ");

    signal(SIGUSR1, handle_bomb);
    signal(SIGUSR2, refuel);

    while (fuel > 0) {
        sleep(1);
        fuel -= FUEL_CONSUMPTION_RATE;
        if(fuel % FUEL_REPORT_RATE == 0) {
            printf("\nBomber %d to base, %d%% of fuel left\n", getpid(), fuel);
        }
        if(fuel <= 0) {
            printf("SoS! Plane %d is going to crash\n", getpid());
            in_flight = 0;  
            exit(0);
        }
    }
}


int main() {
    char commands[10];
    int pid = -1;
    int refuel_pid;
    int bomb_pid;

    
    while(1) {
        printf("\nEnter a command (l)aunch, (r)efuel, (b)omb, (q)uit: ");
        fflush(stdout); 
        scanf("%s", commands);

        if (strcmp(commands, "l") == 0) {
            pid = fork();
            if(pid < 0) {
                perror("Fork failed");
                exit(1);
            } else if(pid == 0) {
                plane();
                exit(0);
            }
        } else if(strcmp(commands, "r") == 0) {
            if(waitpid(pid, NULL, WNOHANG) == 0) {  
                printf("Which plane to refuel:  ");
                scanf("%d", &refuel_pid);
                kill(refuel_pid, SIGUSR2);
            } else {
                printf("No planes were launched, none to refuel!\n");
            }
        } else if(strcmp(commands, "b") == 0) {
            if(waitpid(pid, NULL, WNOHANG) == 0) {  
                printf("Which plane should drop a bomb: ");
                scanf("%d", &bomb_pid);
                kill(bomb_pid, SIGUSR1);
            } else {
                printf("No planes were launched, can't drop a bomb!\n");
            }
        } else if(strcmp(commands, "q") == 0) {
            if(pid > 0) {
                kill(pid, SIGKILL);
                wait(NULL);
            }
            exit(0);
        } else {
            printf("Invalid command\n");
        }
    }


    return 0;
}