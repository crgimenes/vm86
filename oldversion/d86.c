#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decompile(const char *s,unsigned int i) {
	unsigned char v;
	unsigned char par_count; 
	for (unsigned int c=0;c<i;c++) {
		v = (unsigned char)(*(s+c));
		printf("%04xh %02x ",c,v);
		if(par_count>0) {
			par_count--;
			printf("%02xh ",v);
		} else {
			switch (v) {
                case 0xB4:
                    printf("mov ah");
                    par_count=1;
                    break;
                case 0xB9:
                    printf("mov cx");
                    par_count=2;
                    break;
                case 0xBA:
                    printf("mov dx");
                    par_count=2;
                    break;
				case 0xBB:
                    printf("mov bx");
                    par_count=2;
                    break;
                case 0xCC:
                    printf("int 3");
                    par_count=0;
                    break;
				case 0xCD:
					printf("int");
					par_count=1;
					break;
				default:
					printf("%02xh",v);
		            if (v>=32) {
				        printf(" \"%c\"",v);
					}
					break;
			}
		}
		
		printf("\r\n");
	}
}

unsigned int fsize(FILE *fd) {
	fseek(fd, 0, SEEK_END);
	unsigned int size = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	return size;
}

int main(int argc, char *argv[]) {
	char memory[1024];
	FILE *fp;

	if(argc==1) {
		printf("%s filename.com\r\n",argv[0]);
		exit(1);
	}

	memset(memory, 0, sizeof(memory)); 	
	fp = fopen(argv[1] , "rb");
    if(fp == NULL) {
		printf("Error opening file");
		return(-1);
	}
	
	unsigned int size = fsize(fp);

	fread(memory, size, 1, fp);
	decompile(memory,size);

	fclose(fp);
	return 0;
}
