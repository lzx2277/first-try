#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if(pid==0)
    {
        int fd = open(/home/linux/myfifo,O_RDONLY);
        
        write(fd,argv[1],sizeof(argv[1]));

        close(fd);
    }
    else if (pid > 0)
    {
        while(1)
        {
            pid_t pid=waitpid(-1,NULL,WNOHANG);
            if(pid > 0)
            {
                printf("子进程%d退出了\n",pid);
            }
            else if(pid == 0)
            {
                continue;
            }
            else if(pid == -1)
            {
                break;
            }
        }
    }
    else
    {
        perror("fork");
    }
    
    return 0;
}
