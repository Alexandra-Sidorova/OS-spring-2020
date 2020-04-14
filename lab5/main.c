#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t p1, p2;
    int fd1[2], fd2[2];
    int status1, status2;
    
    status1 = pipe(fd1);
    status2 = pipe(fd2);
    
    if((status1 < 0) || (status2 < 0))
    {
        printf("Error. Pipes weren't created!");
        return -1;
    }
    
    p1 = fork();
    
    if (p1 < 0)
    {
        printf("Error. First fork wasn't created!);
        _exit(-1);
    }
    
    if (p1 > 0)
    {
        close(1);
        dup2(fd1[1], 1);
        close(fd1[1]);
        close(fd1[0]);
        execl("/bin/ls", "ls", "-la", "/dev", 0);
    }
    
    if (p1 == 0)
    {
        close(0);
        dup2(fd1[0], 0);
        close(fd1[0]);
        close(fd1[1]);
        
        p2 = fork();
        
        if (p2 > 0)
        {
            close(1);
            dup2(fd2[1], 1);
            close(fd2[1]);
            close(fd2[0]);
            execl("/bin/sort", "sort", 0);
        }
        
        if (p2 == 0)
        {
            close(0);
            dup2(fd2[0], 0);
            close(fd2[0]);
            close(fd2[1]);
            execl("/bin/more", "more", 0);
            _exit(0);
        }
        
        wait();
        _exit(0);
    }
    
    return 0;
}