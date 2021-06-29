/*
** EPITECH PROJECT, 2021
** B-PSU-402-BDX-4-1-strace-alexandre.quenelle
** File description:
** args_manager
*/

#include "strace.h"

void display_usage(void)
{
    printf("USAGE: ./ftrace [file_to_inspect]\n");
    exit(0);
}

void check_file(char *file_path)
{
    struct stat sb;

    if (stat(file_path, &sb) == 0 && sb.st_mode & S_IXUSR) {
        return;
    } else
        exit(84);
}

char *args_manager(int pid, int argc, char **argv)
{
    char *file_path;

    if (argc < 2 || pid == -1)
        exit(1);

    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0)
            display_usage();
    }
    return (argv[1]);
}