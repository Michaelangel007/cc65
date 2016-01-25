            .include "apple2.mac" ; AC, AR, AS and AT macros

            COUT = $FDED
            HOME = $FC58

            __MAIN = $1000
            .org __MAIN

            JSR    HOME
            LDX    #0
            LDA    MSG,X          ; load initial char
PRINTCHAR:  JSR    COUT
            INX
            LDA    MSG,X
            BNE    PRINTCHAR
WAIT:
            LDA    KEYBOARD
            BPL    WAIT
REBOOT:     JMP    $C600

            AS "Hello world, Apple!"
            .byte $8D            ; CR with high-bit set
            .byte $00


