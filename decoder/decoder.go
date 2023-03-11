package decoder

func DecodeByte(b []byte) (displiment int, opcode int, d bool, w bool, mod int, reg int, rm int) {
	/*
		decode 8086 opcode

		765432 1 0
		000000 0 0| 00  000 000 00000000 00000000 00000000
		opcode d w| mod reg r/m

		r/m:	REGISTER OPERAND/REGISTERS TO USE IN EA CALCULATION
		reg:	REGISTER OPERAND/EXTENSION OF OPCODE
		mod:	REGISTER MODE/MEMORY MODE WITH DISPLACEMENT LENGTH
		w:		WORD/BYTE OPERATION
		d:		DIRECTION ISTO REGISTER/DIRECTION IS FROM REGISTER
		opcode: OPERATION(INSTRUCTION) CODE


	*/

	displiment = 0
	opcode = int(b[0] & 0xFC) // 1111 1100
	d = (b[0] & 0x02) != 0    // direction, 0 = reg to mem, 1 = mem to reg
	w = (b[0] & 0x01) != 0    // wide, 0 = 8bit, 1 = 16bit
	mod = int(b[1] & 0xC0)    // 1100 0000
	reg = int(b[1] & 0x38)    // 0011 1000
	rm = int(b[1] & 0x07)     // 0000 0111

}
