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
	
        lui $11,0xa080
        ori $11,$11,0x1fc

        lw  $9, ($11)
        mul $9, $9, 0x200
     
	lui $8,0x8007
	ori $8,$8,0xb1a8
	
	lui $4,0xa080
	ori $4,$4,0x0200

	li $5,0x200

	move $6, $9
			
	jal $8
	
	lui $8,0xa080
	ori $8,$8,0x026c

        jal $8

        jr  $31
		
	#need add code
	#read kernel

