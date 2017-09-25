	.text
	.globl main

main:
	# check the offset of main
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	
	lui $8,0xbfe4
	ori $8,$8,0x8000

	li $9,0x57
	sb $9,($8)
	nop
	li $9,0x65
	sb $9,($8)
	nop
	li $9,0x6c
	sb $9,($8)
	nop
	li $9,0x63
	sb $9,($8)
	nop
	li $9,0x6f
	sb $9,($8)
	nop
	li $9,0x6d
	sb $9,($8)
	nop
	li $9,0x65
	sb $9,($8)
	nop
	li $9,0x20
	sb $9,($8)
	nop
	li $9,0x74
	sb $9,($8)
	nop
	li $9,0x6f
	sb $9,($8)
	nop
	li $9,0x20
	sb $9,($8)
	nop
	li $9,0x43
	sb $9,($8)
	nop
	li $9,0x48
	sb $9,($8)
	nop
	li $9,0x4f
	sb $9,($8)
	nop
	li $9,0x0d
	sb $9,($8)
	nop
	li $9,0x0a
	sb $9,($8)
	nop
	jr $31

