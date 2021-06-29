/*
** EPITECH PROJECT, 2021
** B-PSU-402-BDX-4-1-strace-alexandre.quenelle
** File description:
** test
*/

#ifndef TEST_H_
#define TEST_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <sys/user.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <stddef.h>
#include <string.h>

struct data {
    size_t func[1000];
    char **name;
    pid_t pid;
    int status;
} typedef data;

bool *is64architecture(void);

#define GET_ELF_EHDR(__buff, __var_name)        (IS64ARCH ?         \
                            ((Elf64_Ehdr *)__buff)->__var_name      \
                        :   ((Elf32_Ehdr *)__buff)->__var_name)

#define GET_ELF_SHDR(__buff, __var_name)        (IS64ARCH ?         \
                            ((Elf64_Shdr *)__buff)->__var_name      \
                        :   ((Elf32_Shdr *)__buff)->__var_name)

#define GET_ELF_SYM(__buff, __var_name)        (IS64ARCH ?         \
                            ((Elf64_Sym *)__buff)->__var_name      \
                        :   ((Elf32_Sym *)__buff)->__var_name)

#define IS64ARCH        (*is64architecture())

char *args_manager(int pid, int argc, char **argv);

void display_usage(void);

void print_sys_call_params(struct user_regs_struct regs, int pid, bool flag_s);

int get_regs(int pid, char *file_path, char **envp, struct data *tools);

void check_file(char *file_path);

void print_registers(struct user_regs_struct regs, int i, int pid);

void print_execve(char *file_path, char **envp);

void print_exit_group(int status, char **argv);

int my_nm(char *prog_name, char *path, size_t *func, char **name);

size_t parse_file(char *prog_name, char *path, void **buff);

int error_check(size_t size, void *buffer);

char *get_symbol_name(void *buffer, size_t index);

bool *is64architecture(void);

void print_sym(void *shdr, Elf64_Shdr *test, size_t *func, char **name);

void **my_buffer(void);

#endif /* !TEST_H_ */