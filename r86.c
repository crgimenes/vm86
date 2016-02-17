#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int print_asm;
int use_curses;
int cursor_x;
int cursor_y;
WINDOW *mainwin;

void setCursorPos(int x, int y) {
    cursor_x = x;
    cursor_y = y;
    wmove(mainwin, y, x);
    refresh();
}

void setChar(const unsigned char c) {
    mvwaddch(mainwin, cursor_y, cursor_x, c);
    refresh();
}

void init_ncurses(void) {
    if (!use_curses) return;

	if ( (mainwin = initscr()) == NULL ) {
		printf("Error initialising ncurses.\n");
		exit(1);
    }
}

void end_ncurses(void) {
    if (!use_curses) return;

	delwin(mainwin);
	endwin();
    refresh();
}

void run(const char *s) {
	unsigned char v;
	unsigned char par_count=0; 

	unsigned char ah;
	unsigned char al;
	int16_t cx;
    int16_t bx;
    int16_t dx;

	unsigned char lbyte;
	unsigned char hbyte;

	for (unsigned int c=0;c<1024;c++) {
		v = (unsigned char)(*(s+c));
		if(print_asm==1) printf("%04xh %02x ",c,v);
		if(par_count>0) {
			par_count--;
			printf("%02xh ",v);
		} else {
			switch (v) {
                case 0xB0:
                    c++;
                    v = (unsigned char)(*(s+c));
                    al = v;
                    if(print_asm==1) printf("mov al, %4Xh",al);
                    break;
                case 0xB4:
                    c++;
					v = (unsigned char)(*(s+c));
					ah = v;
					if(print_asm==1) printf("mov ah, %4Xh",ah);
                    break;
                case 0xB9:
					c++;
                    lbyte = (unsigned char)(*(s+c));
					c++;
                    hbyte = (unsigned char)(*(s+c));
					cx = (int16_t)(hbyte << 8 | lbyte);
                    if(print_asm==1) printf("mov cx, %4Xh",cx);
                    break;
                case 0xBA:
					c++;
                    lbyte = (unsigned char)(*(s+c));
                    c++;
                    hbyte = (unsigned char)(*(s+c));
                    dx = (int16_t)(hbyte << 8 | lbyte);
                    if(print_asm==1) printf("mov dx, %4Xh",dx);
                    break;
				case 0xBB:
                    c++;
                    lbyte = (unsigned char)(*(s+c));
                    c++;
                    hbyte = (unsigned char)(*(s+c));
                    bx = (int16_t)(hbyte << 8 | lbyte);
                    if(print_asm==1) printf("mov bx, %4Xh",bx);
                    break;
                case 0xCC:
                    printf("int 3 debug...");
                    par_count=2;
                    break;
				case 0xCD:
					c++;
                    v = (unsigned char)(*(s+c));
                    if(print_asm==1) printf("int %2Xh",v);
					if(v==0x20) { // return to "DOS" :D
						exit(0);
					}
					if(v==0x21) { // DOS
						if(ah == 0x4C) { // exit program
							printf("\r\n");
							exit(al);
						} 
						if(ah == 0x40) { // write to a file or device
							/*
							BX = file handle
							CX = number of bytes to write
							DS:DX -> data to write
							*/
							
							for(int i=0;i<cx;i++) {
								v = (unsigned char)(*(s+(dx-0x100)+i));
                                if (use_curses) {
                                    setChar(v);
                                    cursor_x++;
                                } else {
                                    printf("%c",v);
                                }

							}
						}
					}
					break;
				default:
					printf("%02xh",v);
		            if (v>=32) {
				        printf(" \"%c\"",v);
					}
					break;
			}
		}
		
		if(print_asm==1) printf("\r\n");
	}
}

size_t fsize(FILE *fd) {
	fseek(fd, 0, SEEK_END);
	size_t size = (size_t)ftell(fd); // warning ftell return signed long
	fseek(fd, 0, SEEK_SET);
	return size;
}

int main(int argc, char *argv[]) {
    char memory[1024];
	FILE *fp;

    int opt_flag;
    char *filename;
    extern char *optarg;
    extern int optind, optopt, opterr;
	char *file;
    
    print_asm = 0;
    use_curses = 0;
    cursor_y = 0;
    cursor_y = 0;

    while ((opt_flag = getopt(argc, argv, "acf")) != -1) {
        switch(opt_flag) {
            case 'a':
                print_asm = 1;
                break;
            case 'c':
                use_curses = 1;
                break;
            case 'f':
                filename = optarg;
                printf("filename is %s\n", filename);
                break;
            case ':':
                printf("-%c without filename\n", optopt);
                break;
            case '?':
                printf("unknown option %c\n", optopt);
                break;
            default:
                filename = optarg;
                printf("filename is %s\n", filename);
                break;
        }
    }

        //printf("optind = %i\n",optind);
    if (optind < argc) {
            file = argv[optind];
            //printf("filename is %s\n", file);
    }

	if(argc==1) {
		printf("%s filename.com\r\n",argv[0]);
		exit(1);
	}

	memset(memory, 0, sizeof(memory)); 	
	fp = fopen(file , "rb");
    if(fp == NULL) {
		printf("Error opening file %s",file);
		return(-1);
	}
	
	size_t size = fsize(fp);

	fread(memory, size, 1, fp);
	fclose(fp);
	
	init_ncurses();
	run(memory);
	end_ncurses();

	return 0;
}
