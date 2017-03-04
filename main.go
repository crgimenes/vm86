package main

import (
	"bufio"
	"fmt"
	"io"
	"os"

	"github.com/crgimenes/goConfig"
)

type config struct {
	FileName string `cfg:"name"`
}

func main() {
	cfg := config{}

	goConfig.PrefixEnv = "R86"
	err := goConfig.Parse(&cfg)
	if err != nil {
		println(err.Error())
		os.Exit(1)
	}

	f, err := os.Open(cfg.FileName)
	if err != nil {
		println(err.Error())
		os.Exit(1)
	}

	defer func() {
		err = f.Close()
		if err != nil {
			println(err.Error())
			os.Exit(1)
		}
	}()

	buff := bufio.NewReader(f)

	var c byte
	for {

		c, err = buff.ReadByte()
		if err != nil {
			if err == io.EOF {
				return
			}
			println(err.Error())
		}

		fmt.Printf("%02x ", c)

	}
}
