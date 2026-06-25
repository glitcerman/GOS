global gdt_load

gdt_load:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]  ; pointeur vers gdt_ptr
    lgdt [eax]          ; charger la GDT

    ; Recharger tous les registres de segment données
    mov ax, 0x10        ; 0x10 = segment données (entrée 2)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Recharger CS avec un far jump vers entrée 1 (code kernel)
    jmp 0x08:.flush
.flush:
    pop ebp
    ret
