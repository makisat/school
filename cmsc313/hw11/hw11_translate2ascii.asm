; Convert each byte in inputBuf into two ASCII hex digits plus a space,
; put the result in outputBuf, replace the final space with a newline,
; and write the whole line to stdout.
;
; bulid: nasm -f elf32  hw11_translate2ascii.asm
; link: LD   -m elf_i386 -o hw11translate2Ascii hw11_translate2ascii.o
; run: ./hw11translate2Ascii

    global  _start

    section .data
    inputBuf   db 0x83, 0x6A, 0x88, 0xDE, 0x9A, 0xC3, 0x54, 0x9A
    inputLen   equ $ - inputBuf

    hexTable   db '0123456789ABCDEF'

    section .bss
    outputBuf  resb 80

    section .text

; Convert a 4‑bit value in AL into its ASCII character.
; Values 0–9 become '0'–'9'; 10–15 become 'A'–'F'.

nibble2ascii:
    cmp     AL, 9
    jbe     .digit
    add     AL, 0x37
    ret
    .digit: add     AL, 0x30
    ret

_start:
    ;; Initialise source/destination pointers and loop counter.
    mov     ESI, inputBuf
    mov     EDI, outputBuf
    mov     ECX, inputLen
    ;; Main loop
    .loop:
    lodsb
    mov     BL, AL

    shr     AL, 4
    call    nibble2ascii
    stosb

    mov     AL, BL
    and     AL, 0x0F
    call    nibble2ascii
    stosb

    mov     AL, ' '
    stosb

    loop    .loop

    ;; After the loop, overwrite the trailing space with newline
    dec     EDI
    mov     byte [EDI], 0x0A

    ;; write(1, outputBuf, length)
    mov     EAX, 4
    mov     EBX, 1
    mov     ECX, outputBuf
    sub     EDI, outputBuf
    mov     EDX, EDI
    int     0x80

    ;; exit(0)
    mov     EAX, 1
    xor     EBX, EBX
    int     0x80
