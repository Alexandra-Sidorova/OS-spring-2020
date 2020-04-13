#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t p;
    int status = 0;
    char* arg[] = { "/bin/ls", "-la", "/tmp", NULL};
    
    p = fork();
    
    if (p > 0)
    {
        printf("Program starts in parent. 
                Parent pid = %d, child process = %d\n", getpid(), p);
        wait(&status);
        if (WIFEXITED(status))
            printf("Child process exited with code %d\n", WEXITSTATUS(status));
        _exit(status);
    }
    
    if (p < 0)
    {
        printf("Error");
        _exit(-1);
    }
    
    if (p == 0)
    {
        printf("Execution starts in child process. 
                Child process pid = %d, ppid = %d\n", getpid(), getppid());
        execv(arg[0], arg);
    }
    
    printf("Execution continues in parent process...\n);
    
    return 0;
}