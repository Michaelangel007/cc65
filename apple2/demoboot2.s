            .include "apple2.mac" ; AC, AR, AS and AT macros

        KEYBOARD    = $C000
        KEYSTROBE   = $C010

        COUT        = $FDED
        HOME        = $FC58

            __MAIN  = $0800
            .org    __MAIN
            .byte   $01         ; Disk Drive PROM # of sectors to read
                                ;
            JSR     HOME
            LDX     #0
            LDA     message,X   ; load initial char
printchar:  JSR     COUT
            INX
            LDA     message,X
            BNE     printchar
wait:
            LDA     KEYBOARD
            BPL     wait
            STA     KEYSTROBE
reboot:     JMP     $C600

message:
            AS "Hello world, Apple!"
            .byte $8D           ; CR with high-bit set
            .byte $00

