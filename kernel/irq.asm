global irq1_handler

extern keyboard_handler

irq1_handler:
    pusha

    call keyboard_handler

    popa
    iret