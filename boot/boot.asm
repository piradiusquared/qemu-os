; Interact with BIOS
mov ah, 0x0e ; Switch to teletype mode
mov al, 65
int 0x10 ; Interrupt

loop:
        inc al
        cmp al, 'Z' + 1
        je exit
        int 0x10
        jmp loop

exit:
        jmp $ ; Jump to certain byte
; db sets bytes to 0 from start to location of using jmp
times 510-($-$$) db 0 ; Repeats instruction.
db 0x55, 0xaa ; Set these bytes
