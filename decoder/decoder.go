package decoder

func DecodeByte(b []byte) (shift int, opcode int, d bool, w bool, mod int, reg int, rm int) {
	/*
			decode 8086 opcode
			get opcode, d, w, mod, reg, rm
			opcode := b & 0x07
			d := (b & 0x08) != 0
			w := (b & 0x01) != 0
			mod := (b & 0x30) >> 4
			reg := (b & 0x38) >> 3
			rm := (b & 0x07)

			000000 0 0| 00000000 00000000 00000000 00000000
		    opcode d w| mod reg rm
	*/

	shift = 0
	opcode = int(b[0] & 0x07)
	d = (b[0] & 0x02) != 0
	w = (b[0] & 0x01) != 0
	if w {
		shift = 1
	}

	return
}
