            .include "apple2.mac" ; AC, AR, AS and AT macros

        TEXT        = $0400
        KEYBOARD    = $C000
        KEYSTROBE   = $C010

            __MAIN  = $0800
            .org    __MAIN
            .byte   $01         ; Disk Drive PROM # of sectors to read

            LDX #end - message - 1
printchar:  LDA message,X   ; load initial char
            STA TEXT,X
            DEX
            BPL printchar
wait:
            LDA KEYBOARD
            BPL wait
            STA KEYSTROBE
RTS
reboot:     JMP $C600

message:
            AS "Hello text screen @ $400"
end:

