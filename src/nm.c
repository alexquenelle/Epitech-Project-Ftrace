/*
** EPITECH PROJECT, 2021
** B-PSU-402-BDX-4-1-ftrace-alexandre.quenelle
** File description:
** nm
*/

#include "strace.h"

bool *is64architecture(void)
{
    static bool arch = 1;
    return &arch;
}

char *get_symbol_name(void *buffer, size_t index)
{
    for (int i = 1; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        char *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        if (GET_ELF_SHDR(shdr, sh_type) == SHT_STRTAB &&
            GET_ELF_SHDR(shdr, sh_flags) == 0) {
            char *tab = buffer + GET_ELF_SHDR(shdr, sh_offset);
            return &tab[index];
        }
    }
    return NULL;
}

int error_check(size_t size, void *buffer)
{
    if (!size)
        return 1;
    if (GET_ELF_EHDR(buffer, e_ident[EI_VERSION]) != EV_CURRENT)
        return 1;
    return 0;
}

size_t parse_file(char *prog_name, char *path, void **buff)
{
    int fd;
    struct stat s;
    if ((fd = open(path, O_RDONLY)) < 0)
        return 0;
    fstat(fd, &s);
    *buff = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    int class = GET_ELF_EHDR(*buff, e_ident[EI_CLASS]);
    int data = GET_ELF_EHDR(*buff, e_ident[EI_DATA]);
    IS64ARCH = GET_ELF_EHDR(*buff, e_ident[EI_CLASS]) == 1 ? 0 : 1;
    if ((class != ELFCLASS64 && class != ELFCLASS32) ||
        (data != ELFDATA2LSB && data != ELFDATA2MSB) ||
        (GET_ELF_EHDR(*buff, e_shnum) * GET_ELF_EHDR(*buff, e_shentsize) +
            GET_ELF_EHDR(*buff, e_shoff) != s.st_size) ||
        strncmp((char *) *buff, "\x7f\x45\x4c\x46", 4) != 0) {
        return 0 * fprintf(stderr, "%s: %s: %s\n", prog_name, path,
            "file format not recognized");
    }
    IS64ARCH = GET_ELF_EHDR(*buff, e_ident[EI_CLASS]) == 1 ? 0 : 1;
    return s.st_size;
}

int my_nm(char *prog_name, char *path, size_t *func, char **name)
{
    void *buffer;

    size_t size = parse_file(prog_name, path, &buffer);
    if (error_check(size, buffer)) {
        munmap(buffer, size);
        return 84;
    }
    *my_buffer() = buffer;
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *) (buffer);
    Elf64_Shdr *test = (Elf64_Shdr *) (buffer + GET_ELF_EHDR(ehdr, e_shoff));
    for (int i = 1; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        void *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        if (GET_ELF_SHDR(shdr, sh_type) == SHT_SYMTAB) {
            print_sym(shdr, test, func, name);
        }
    }
    munmap(buffer, size);
    return (0);
}