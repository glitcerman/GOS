global irq1_handler
global irq_default_handler
global exception_handler

extern keyboard_handler

irq1_handler:
    pusha
    mov ax, 0x10    ; segment de données du kernel
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call keyboard_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret

irq_default_handler:
    pusha
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov al, 0x20
    out 0x20, al
    out 0xA0, al
    popa
    iret
    
exception_handler:
    cli
    hlt