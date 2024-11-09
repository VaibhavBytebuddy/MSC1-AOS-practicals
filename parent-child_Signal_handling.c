#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

//Single handler function
void alarm_handler(int signum)
{
    printf("Alarm fired ! signal %d received by parent process\n",signum);

}

int main()
{
    pid_t pid;

    if(signal(SIGALRM,alarm_handler)==-1)
    {
        perror("signal");
        exit(1);
    }

    pid=fork();

    if(pid<0)
    {
        perror("fork");
        exit(1);

    }

    if(pid==0)
    {
        //child process
        printf("Child process (PID: %d) sending SIGNAMRM to parent (PID: %d)\n",getpid(),getppid());

        sleep(2);

        //send SIGALARM to parent

        if(kill(getppid(),SIGALRM)==-1)
        {
            perror("Kill");
            exit(1);
        }
        exit(0);
    }
    else
    {//parent process

         printf("Parent process (PID: %d) waiting for signal.......\n",getpid());

         for(int i=0;i<5;i++)
         {
            sleep(1);
         }
   }

   return 0;
}