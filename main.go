package main

import (
	"bufio"
	"fmt"
	"io"
	"os"

	"crg.eti.br/go/config"
)

type Config struct {
	FileName string `cfg:"name"`
}

var memory [640000]byte

func closer(f io.Closer) {
	err := f.Close()
	if err != nil {
		fmt.Println(err.Error())
	}
}

func main() {
	cfg := Config{}

	config.PrefixEnv = "VM86"
	err := config.Parse(&cfg)
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}

	if cfg.FileName == "" {
		if len(os.Args) > 1 {
			cfg.FileName = os.Args[len(os.Args)-1]
		}
	}

	f, err := os.Open(cfg.FileName)
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}

	defer closer(f)

	buff := bufio.NewReader(f)

	var c byte
	var count int
	var col int
	//var row int

	count = 0x100
	for {

		c, err = buff.ReadByte()
		if err != nil {
			if err == io.EOF {
				break
			}
			fmt.Println(err.Error())
			os.Exit(1)
		}

		memory[count] = c

		if col >= 16 || col == 0 {
			col = 0
			fmt.Println(err.Error())
		}

		fmt.Printf("%02X ", c)
		col++
		count++
	}

	fmt.Println(err.Error())
}
