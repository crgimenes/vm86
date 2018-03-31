# r86
Emulate old DOS .com files in the console. It is a simple proof of concept, not a complete emulator.


```bash
nasm -f bin test.asm -o test.com
```

```bash
go run main.go test.com
hello world
echo $?
```

```bash
go run main.go -a teste.com
```
