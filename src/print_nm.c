/*
** EPITECH PROJECT, 2021
** B-PSU-402-BDX-4-1-ftrace-alexandre.quenelle
** File description:
** print_nm
*/

#include "strace.h"

void print_sym(void *shdr, Elf64_Shdr *test, size_t *func, char **name)
{
    static int inc = 0;
    void *buffer = *my_buffer();
    for (size_t i = 0;
        i < GET_ELF_SHDR(shdr, sh_size); i += GET_ELF_SHDR(shdr, sh_entsize)) {
        void *sym = (buffer + GET_ELF_SHDR(shdr, sh_offset) + i);
        size_t nm = GET_ELF_SYM(sym, st_name);
        size_t value = GET_ELF_SYM(sym, st_value);
        if (!IS64ARCH ? ELF32_ST_TYPE(GET_ELF_SYM(sym, st_info)) :
            ELF64_ST_TYPE(GET_ELF_SYM(sym, st_info)) == STT_FILE ||
                !strlen(get_symbol_name(buffer, nm)))
            continue;
        if ((GET_ELF_SYM(sym, st_shndx) == SHN_UNDEF && value) ||
            ((test[GET_ELF_SYM(sym, st_shndx)].sh_type == SHT_PROGBITS &&
                test[GET_ELF_SYM(sym, st_shndx)].sh_flags ==
                    (SHF_ALLOC | SHF_EXECINSTR) && value) &&
                GET_ELF_SYM(sym, st_info) > 0)) {
            func[inc] = value;
            name[inc] = strdup(get_symbol_name(buffer, nm));
            inc++;
        }
    }
}

void **my_buffer(void)
{
    static void *buffer = NULL;
    return &buffer;
}