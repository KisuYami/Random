section .data:

    succ_string db 'success', 10    ; 8
    fail_string db 'fail', 10       ; 5
    info_string db 'input: '        ; 7

section .bss
    input_string resb 5

section .text:
    global _start

_start:
    ; print 'input: '
    mov eax, 4
    mov ebx, 1
    mov ecx, info_string
    mov edx, 7
    int 80h

    ; read user input
    mov eax, 3
    mov ebx, 2
    mov ecx, input_string
    mov edx, 5
    int 80h

    ; convert string to int
    movzx rax, byte[input_string]
    sub rax, 48
    mov rbx, 0

    cmp rax, rbx    ; if(rax != rbx)
    je _success_msg

    cmp rax, 0      ; if(rax == 0)
    je _success_msg

    jmp _fail_msg   ; else

_success_msg:
    mov ecx, succ_string
    mov edx, 8
    jmp _write

_fail_msg:
    mov ecx, fail_string
    mov edx, 5
    jmp _write

_write:
    mov ebx, 1
    mov eax, 4
    int 80h

_end:
    mov eax, 1
    int 80h
