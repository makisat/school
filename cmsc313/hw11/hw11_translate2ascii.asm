; Convert each byte in inputBuf into two ASCII hex digits plus a space,
; put the result in outputBuf, replace the final space with a newline,
; and write the whole line to stdout.
;
; bulid: nasm -f elf32  hw11_translate2ascii.asm
; link: ld   -m elf_i386 -o hw11translate2Ascii hw11_translate2ascii.o
; run: ./hw11translate2Ascii

global  _start

section .data
inputBuf   db 0x83, 0x6A, 0x88, 0xDE, 0x9A, 0xC3, 0x54, 0x9A
inputLen   equ $ - inputBuf

hexTable   db '0123456789ABCDEF'

section .bss
outputBuf  resb 80

section .text

nibble2ascii:
        cmp     AL, 9
        jbe     .digit
        add     AL, 0x37
        ret
.digit: add     AL, 0x30
        ret
; ---------------------------------------------------------------------

_start:
        mov     ESI, inputBuf
        mov     EDI, outputBuf
        mov     ECX, inputLen

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

        dec     EDI
        mov     byte [EDI], 0x0A

        mov     EAX, 4
        mov     EBX, 1
        mov     ECX, outputBuf
        sub     EDI, outputBuf
        mov     EDX, EDI
        int     0x80

        mov     EAX, 1
        xor     EBX, EBX
        int     0x80
