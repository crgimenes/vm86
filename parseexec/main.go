package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"log"
	"os"
)

/*
notes

#define FAT_MAGIC   0xcafebabe
#define FAT_CIGAM   0xbebafeca

#define MH_MAGIC 0xfeedface
#define MH_CIGAM 0xcdfaedfe

#define MH_OBJECT       0x1
#define MH_EXECUTE      0x2
#define MH_FVMLIB       0x3
#define MH_CORE         0x4
#define MH_PRELOAD      0x5
#define MH_DYLIB        0x6
#define MH_DYLINKER     0x7
#define MH_BUNDLE       0x8
#define MH_DYLIB_STUB   0x9
#define MH_DSYM         0xa
#define MH_KEXT_BUNDLE  0xb

#define LC_SEGMENT 0x1
#define LC_SYMTAB  0x2
#define LC_THREAD  0x4

*/

type fatHeader struct {
	Magic    uint32
	NfatArch uint32
}

type fatArch struct {
	cputype    uint32
	cpusubtype uint32
	offset     uint32
	size       uint32
	align      uint32
}

type machHeader struct {
	Magic      uint32
	Cputype    uint32
	Cpusubtype uint32
	Filetype   uint32
	Ncmds      uint32
	Sizeofcmds uint32
	Flags      uint32
}

type loadCommand struct {
	cmd     uint32
	cmdsize uint32
}

type segmentCommand struct {
	cmd      uint32
	cmdsize  uint32
	segname  [16]byte
	vmaddr   uint32
	vmsize   uint32
	fileoff  uint32
	filesize uint32
	maxprot  uint32
	initprot uint32
	nsects   uint32
	flags    uint32
}

type section struct {
	sectname  [16]byte
	segname   [16]byte
	addr      uint32
	size      uint32
	offset    uint32
	align     uint32
	reloff    uint32
	nreloc    uint32
	flags     uint32
	reserved1 uint32
	reserved2 uint32
}

func readNextBytes(file *os.File, number int) []byte {
	bytes := make([]byte, number)

	_, err := file.Read(bytes)
	if err != nil {
		log.Fatal(err)
	}

	return bytes
}

func main() {

	path := "../vm"

	file, err := os.Open(path)
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	fmt.Printf("%s opened\n", path)

	header := machHeader{}
	data := readNextBytes(file, 100)

	for _, v := range data {
		fmt.Printf("%02X ", v)
	}
	fmt.Println("\n-------------")
	buffer := bytes.NewBuffer(data)
	err = binary.Read(buffer, binary.LittleEndian, &header)
	if err != nil {
		log.Fatal("binary.Read failed ", err)
	}

	fmt.Printf("Parsed data:\n%+v\n", header)

}
