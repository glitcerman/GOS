section .multiboot
align 4
    dd 0xE85250D6        ; magic
    dd 0                 ; architecture (i386)
    dd end - start       ; header length
    dd -(0xE85250D6 + 0 + (end - start))

start:
end: