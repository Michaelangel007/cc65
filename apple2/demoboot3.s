            TEXT        = $0400
            KEYBOARD    = $C000
            KEYSTROBE   = $C010

            .org    $800
            .byte   $01         ; Disk Drive PROM # of sectors to read

            LDA #'*' & $3F
            STA TEXT
wait:
            LDA KEYBOARD
            BPL wait
            STA KEYSTROBE
reboot:     JMP $C600

