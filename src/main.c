/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.quenelle
** File description:
** main
*/

#include "strace.h"

int main(int argc, char **argv, char **envp)
{
    struct data *tools = malloc(sizeof(data));
    char *file_path = args_manager(tools->pid, argc, argv);
    tools->name = malloc(sizeof(char *) * 1000);
    for (int i = 0; i < 1000; tools->name[i] = calloc(sizeof(char), 100), ++i);

    my_nm(argv[0], argv[1], tools->func, tools->name);
    tools->pid = fork();
    if (tools->pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execvp(file_path, argv + 1);
    } else {
        waitpid(tools->pid, &tools->status, 0);
        while (1) {
            if (get_regs(tools->pid, file_path, envp, tools) != 0)
                break;
            ptrace(PTRACE_SINGLESTEP, tools->pid, 0, 0);
            waitpid(tools->pid, &tools->status, 0);
        }
        print_exit_group(tools->status, argv);
    }
    return 0;
}