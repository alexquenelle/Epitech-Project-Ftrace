/*
** EPITECH PROJECT, 2021
** B-PSU-402-BDX-4-1-strace-alexandre.quenelle
** File description:
** display_sys_calls
*/

#include "sys_calls.h"
#include "strace.h"

void print_sys_call_params(struct user_regs_struct regs, int pid, bool flag_s)
{
    for (int i = 0; i != sym_table[regs.orig_rax].nb_arg;) {
        print_registers(regs, i, pid);
        i++;
        if (i != sym_table[regs.orig_rax].nb_arg)
            printf(", ");
    }
    printf(") = 0x%lx\n", regs.rax);
}

int get_regs(int pid, char *file_path, char **envp, struct data *tools)
{
    struct user_regs_struct regs;
    bool flag_s = false;

    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) != 0)
        return -1;
    for (int inc = 0; tools->func[inc]; inc++) {
        if (regs.rip == tools->func[inc]) {
            printf("Entering function %s at %p\n", tools->name[inc],
                tools->func[inc]);
            printf("Leaving function %s\n", tools->name[inc]);
        }
    }
    if (regs.orig_rax != -1) {
        printf("Syscall %s(", sym_table[regs.orig_rax].str);
        if (regs.orig_rax == 59) {
            print_execve(file_path, envp);
        } else
            print_sys_call_params(regs, pid, flag_s);
    }
    return 0;
}