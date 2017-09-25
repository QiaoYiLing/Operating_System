#include <assert.h>
#include <elf.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEG_SIZE 0x200

int file_size(FILE *fp)
{
    if(!fp) return -1;
    fseek(fp,0L,SEEK_END);
    int size=ftell(fp);
    
    return size;
}

void write_bootblock(FILE *image_file, FILE *boot_file)
{
    int i;
    uint8_t seg_buf[SEG_SIZE];
    uint8_t elf_buf[4096];
    fread(elf_buf, 4096, 1, boot_file);
    Elf32_Phdr *ph = NULL;
    Elf32_Ehdr *elf = (void *)elf_buf;

    printf("\n-----------------bootblock---------------\n");
    printf("length=%d\n",file_size(boot_file));

    for(i = 0, ph =(void *)elf_buf + elf->e_phoff; i < elf->e_phnum; i ++) 
    {
	if(ph[i].p_type == PT_LOAD) 
	{
            memset(seg_buf,0,SEG_SIZE);

	    fseek(boot_file,ph[i].p_offset,SEEK_SET);
	    fread(seg_buf,1,ph[i].p_filesz,boot_file);

            fwrite(seg_buf,1,SEG_SIZE,image_file);

            printf("p_offset=%d\n",ph[i].p_offset);
            printf("p_size=%d\n",ph[i].p_filesz);
	}
    }
}

void write_kernel(FILE *image_file, FILE *kernel_file)
{
    int i;
    int seg_count = 0;
    uint8_t seg_buf[SEG_SIZE];
    uint8_t elf_buf[4096];

    Elf32_Phdr *ph = NULL;
    fread(elf_buf, 4096, 1, kernel_file);
    Elf32_Ehdr *elf = (void *)elf_buf;

    printf("\n-----------------kernel---------------\n");
    printf("length=%d\n",file_size(kernel_file));

    for(i = 0, ph =(void *)elf_buf + elf->e_phoff; i < elf->e_phnum; i ++) 
    {
	if(ph[i].p_type == PT_LOAD) 
	{
            seg_count++;
            memset(seg_buf,0,SEG_SIZE);

	    fseek(kernel_file,ph[i].p_offset,SEEK_SET);
	    fread(seg_buf,1,ph[i].p_filesz,kernel_file);

            fwrite(seg_buf,1,SEG_SIZE,image_file);

            printf("p_offset[%d]=%d\n",seg_count,ph[i].p_offset);
            printf("p_size[%d]=%d\n",seg_count,ph[i].p_filesz);
	}
    }
    printf("sectors=%d\n",seg_count);

    fseek(image_file,SEG_SIZE-4,SEEK_SET);
    fwrite(&seg_count,1,sizeof(int),image_file);
}


int main(int argc, char *argv[])
{
// create image file; open boot and kernel file.
    FILE *image_file   = fopen("./image", "wb");
    FILE *boot_file    = fopen("./bootblock", "rb");
    FILE *kernel_file  = fopen("./kernel", "rb");
    
//read boot, and put it in image
    write_bootblock(image_file, boot_file);

//read kernel, and put it in image
    write_kernel(image_file, kernel_file);

    fclose(image_file);
    fclose(boot_file);
    fclose(kernel_file);

}
