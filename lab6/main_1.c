#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

char* RandomValue()
{
    char* value = (char*)malloc(10);
    int i;
    
    for(i = 0; i < 10; i++)
        value[i] = rand() % 10;
    
    return value;
}

void SignalInt(int s)
{
    char* param1 = RandomValue();
    char* param2 = RandomValue();
    int check1 = setenv("PARAM1", param1, 1);
    int check2 = setenv("PARAM2", param2, 1);
    pid_t p;
    char* argv[] = {"program2", 0};
    
    if ((check1 == -1) || (check2 == -1))
    {
        printf("Error. Setenv!\n");
        return;
    }
    
    printf("Parent. PARAM1 = %s, PARAM2 = %s\n", param1, param2);
    
    p = fork();
    
    if (p == -1)
    {
        printf("Error. Fork wasn't created!\n");
        return;
    }
    
    if (p == 0)
        execv(argv[0], argv);
}

int main()
{
    printf("My pid = %d\n", getpid();
    signal(SIGINT, SignalInt);
    signal(SIGQUIT, SIG_DFL);
    return 0;
}