#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    char line[100];
    char command[20];
    char args[60];
    int exit = 0, ch, cmd_len, args_len, bg, i, len;
    pid_t pid;
    while (1) {
        printf("osh> ");
        len = 0;
        while ((ch = getchar()) != '\n')
            line[len++] = ch;
        line[len] = '\0';

        cmd_len = 0;
        i = 0;
        while (i < len && line[i] != ' ')
            command[cmd_len++] = line[i++];
        command[cmd_len] = '\0';

        args_len = 0;
        while (i < len && line[i] == ' ') i++;
        while (i < len)
            args[args_len++] = line[i++];
        args[args_len] = '\0';

        if (strcmp(command, "exit") == 0)
            break;

        if (cmd_len > 0) {
            bg = 0;
            for (i = args_len - 1; i >= 0; i--) {
                if (args[i] == '&') {
                    bg = 1;
                    args[i] = ' ';
                    break;
                }
            }

            pid = fork();
            if (pid == 0) {
                if (args_len > 0) 
                    execlp(command, command, args, NULL);
                else
                    execlp(command, command, NULL);

            } else {
                if (bg == 0)
                    wait(NULL);
            }
        }
    }
    return 0;
}
