#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

//This code is modified after MBR parsing project.
//this code is late because of my dad sick.

void print_elf_header(Elf64_Ehdr *header)
 {
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
    {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");

    printf("  Class:                             ");
    switch (header->e_ident[EI_CLASS]) 
    {
        case ELFCLASS32:
        printf("ELF32\n"); 
        break;

        case ELFCLASS64:
        printf("ELF64\n");
        break;

        default: 
        printf("Invalid class\n"); 
        break;
    }

    printf("  Data:                              ");
    switch (header->e_ident[EI_DATA]) 
    {
        case ELFDATA2LSB: 
        printf("2's complement, little endian\n"); 
        break;

        case ELFDATA2MSB: 
        printf("2's complement, big endian\n"); 
        break;

        default: 
        printf("Invalid data encoding\n"); 
        break;
    }

    printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %d\n", header->e_ident[EI_OSABI]);
    printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
    printf("  Type:                              %d\n", header->e_type);
    printf("  Machine:                           %d\n", header->e_machine);
    printf("  Version:                           0x%x\n", header->e_version);
    printf("  Entry point address:               0x%lx\n", header->e_entry);
    printf("  Start of program headers:          %ld (bytes into file)\n", header->e_phoff);
    printf("  Start of section headers:          %ld (bytes into file)\n", header->e_shoff);
    printf("  Flags:                             0x%x\n", header->e_flags);
    printf("  Size of this header:               %d (bytes)\n", header->e_ehsize);
    printf("  Size of program headers:           %d (bytes)\n", header->e_phentsize);
    printf("  Number of program headers:         %d\n", header->e_phnum);
    printf("  Size of section headers:           %d (bytes)\n", header->e_shentsize);
    printf("  Number of section headers:         %d\n", header->e_shnum);
    printf("  Section header string table index: %d\n", header->e_shstrndx);
}

int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        printf("ERROR!\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) 
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    Elf64_Ehdr elf_header;
    if (fread(&elf_header, 1, sizeof(Elf64_Ehdr), file) != sizeof(Elf64_Ehdr)) 
    {
        perror("fread");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    print_elf_header(&elf_header);

    return 0;
}
