# r86
Emulate old DOS .com files in the console. It is a simple proof of concept, not a complete emulator.


```
make
nasm -f bin test.asm -o test.com
```

```
$./r86 test.com                   
hello world
$echo $?        
1
```


```
$ ./r86 -a teste.com
0000h b4 mov ah,   40h
0002h bb mov bx,    1h
0005h b9 mov cx,    Bh
0008h ba mov dx,  114h
000bh cd int 21hhello world
000dh b0 mov al,    1h
000fh b4 mov ah,   4Ch
0011h cd int 21h

```
