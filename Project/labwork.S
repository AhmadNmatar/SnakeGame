  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.
  #
  # Please keep the two macros PUSH and POP unchanged
  #
.data
.align 2
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line

.data
.align 2

# declare function as global so they can called    
.global delay
.global hexasc 
.global time2string
.global enable_interrupt

mytime:    .word 0x5957
timstr:    .ascii "text more text lots of text\0"
.text
main:
        # print timstr
        la    $a0,timstr
        li    $v0,4
        syscall
        nop
        # wait a little
        li    $a0,2
        jal    delay
        nop
        # call tick
        la    $a0,mytime
        jal    tick
        nop
        # call your function time2string
        la    $a0,timstr
        la    $t0,mytime
        lw    $a1,0($t0)
        jal    time2string
        nop
        # print a newline
        li    $a0,10
        li    $v0,11
        syscall
        nop
        # go back and do it all again
        j    main
        nop
        # tick: update time pointed to by $a0
        tick:    lw    $t0,0($a0)    # get time
        addiu    $t0,$t0,1    # increase
        andi    $t1,$t0,0xf    # check lowest digit
        sltiu    $t2,$t1,0xa    # if digit < a, okay
        bnez    $t2,tiend
        nop
        addiu    $t0,$t0,0x6    # adjust lowest digit
        andi    $t1,$t0,0xf0    # check next digit
        sltiu    $t2,$t1,0x60    # if digit < 6, okay
        bnez    $t2,tiend
        nop
        addiu    $t0,$t0,0xa0    # adjust digit
        andi    $t1,$t0,0xf00    # check minute digit
        sltiu    $t2,$t1,0xa00    # if digit < a, okay
        bnez    $t2,tiend
        nop
        addiu    $t0,$t0,0x600    # adjust digit
        andi    $t1,$t0,0xf000    # check last digit
        sltiu    $t2,$t1,0x6000    # if digit < 6, okay
        bnez    $t2,tiend
        nop
        addiu    $t0,$t0,0xa000    # adjust last digit
        tiend:    sw    $t0,0($a0)    # save updated result
        jr    $ra        # return
        nop

hexasc:
        andi $a0, 0x0000000F # bitwise-and with 0000000F as other bits are to be ignored. a0 can be changed freely
        li $t0, 0x30 # load an initial offset of 0x30
        ble $a0, 9, hexasc_done # if less or equal to 9, return
        nop
hexasc_letter:
        addi $t0, $t0, 7 # add 7 to change offset to characters
hexasc_done:
        add $v0, $a0, $t0 # add $a0 + $t0 and store in return parameter
        jr $ra # return
        nop
delay:
        PUSH $ra
        li $t1, 4711
       
    while:
            ble  $a0, $0, done
            nop
            sub $a0,$a0, 1  # ms = ms - 1
            li $t2, 0  # int i = 0
            
    for:
            beq  $t2, $t1, while   # i < 4711
            nop
            addi $t2, $t2, 1    # i = i + 1
            j for
            nop
    
done:

        POP $ra
        jr $ra
        nop
## note: store and restore s0-s7, even if they are not used by time2string.
time2string:
    # before doing anything, store registers on stack
    PUSH $s0
    PUSH $s1
    PUSH $s2
    PUSH $s3
    PUSH $s4
    PUSH $s5
    PUSH $s6
    PUSH $s7
    PUSH $gp
    PUSH $sp
    PUSH $fp
    PUSH $ra
    # let's initialize some variables
    move $s5, $a0
    andi $t0, $a1, 0xFFFF # t0 - temporary,  might be unnecessary
    andi $t5, $t0,0x00FF
    beq  $t5, 0x0000, DING
    nop
    andi $s1,$t0,0xF000
    srl $s1, $s1, 12
    andi $s2,$t0,0x0F00
    srl $s2, $s2, 8
    andi $s3,$t0,0x00F0
    srl $s3, $s3, 4
    andi $s4,$t0,0x000F
    # Now, feed them to hexasc (don't care if t0 is lost)
    # store letter 1
    move $a0, $s1 # load parameter
    jal hexasc ## call function
    nop
    sb $v0, 0($s5)
    # store letter 2
    move $a0, $s2 # load parameter
    jal hexasc ## call function
    nop
    sb $v0, 1($s5)
    ## store ':'
    li $t0, 0x3A
    sb $t0, 2($s5)
    # store letter 3
    move $a0, $s3 # load parameter
    jal hexasc ## call function
    nop
    sb $v0, 3($s5)
    # store letter 4
    move $a0, $s4 # load parameter
    jal hexasc ## call function
    nop
    sb $v0, 4($s5)
    ## store nullbyte
    sb $0, 5($s5)
    # restore the state of registers from when the function was called
end:
    POP $ra
    POP $fp
    POP $sp # this one is kind of weird but it's going to have the same state when it returns nontheless
    POP $gp
    POP $s7
    POP $s6
    POP $s5
    POP $s4
    POP $s3
    POP $s2
    POP $s1
    jr $ra
    nop
    
DING:
    li $t0, 0x44
    sb $t0,0($s5)
    li $t1, 0x49
    sb $t1,1($s5)
    li $t3, 0x4E
    sb $t3,2($s5)
    li $t4, 0x47
    sb $t4,3($s5)
    li $t5,0x00
    sb $t5,4($s5)
    j end
    nop
    
# this function enables interrupts
enable_interrupt:
    ei 
    jr $ra
    nop
