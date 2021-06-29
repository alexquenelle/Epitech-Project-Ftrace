/*
** EPITECH PROJECT, 2021
** B-PSU-402-BDX-4-1-strace-alexandre.quenelle
** File description:
** print_registers
*/

#include "strace.h"

void print_registers(struct user_regs_struct regs, int i, int pid)
{
    switch (i) {
    case 0:
        printf("0x%lx", regs.rdi);
        break;
    case 1:
        printf("0x%lx", regs.rsi);
        break;
    case 2:
        printf("0x%lx", regs.rdx);
        break;
    case 3:
        printf("0x%lx", regs.r10);
        break;
    case 4:
        printf("0x%lx", regs.r8);
        break;
    case 5:
        printf("0x%lx", regs.r9);
        break;
    }
}

void print_execve(char *file_path, char **envp)
{
    int i = 0;

    for (i; envp[i] != NULL; i++);

    printf("\"%s\" , [\"%s\"], /* %d vars */) = ", file_path, file_path, i);
}

void print_exit_group(int status, char **argv)
{
    if (strcmp(argv[1], "-s") == 0)
        printf("exit group(%lx) = ?\n", WEXITSTATUS(status));
    else
        printf("exit group(0x%lx) = ?\n", WEXITSTATUS(status));
    printf("+++ exited with %d +++", WEXITSTATUS(status));
}