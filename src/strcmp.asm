section .text
global   comP

comP:
    push rbx

    mov    rax, QWORD [rsi]     ;// now we have 8 symbs of value in rax
    mov    rbx, QWORD [rdi]     ;// now we have 8 symbs of elem in rbx
    cmp    rax, rbx
    jne    not_eq
    add    rdi, 8
    add    rsi, 8
    mov    rax, QWORD [rsi]     ;// now we have 8 symbs of value in rax
    mov    rbx, QWORD [rdi]     ;// now we have 8 symbs of elem in rbx
    cmp    rax, rbx
    jne    not_eq
    add    rdi, 8
    add    rsi, 8
    mov    rax, QWORD [rsi]     ;// now we have 8 symbs of value in rax
    mov    rbx, QWORD [rdi]     ;// now we have 8 symbs of elem in rbx
    cmp    rax, rbx
    add    rdi, 8
    add    rsi, 8
    mov    rax, QWORD [rsi]     ;// now we have 8 symbs of value in rax
    mov    rbx, QWORD [rdi]     ;// now we have 8 symbs of elem in rbx
    cmp    rax, rbx
    jne    not_eq
    xor    rax, rax
    jmp    eq
    ;jne    not_eq
    ;add    rdi, 8
    ;add    rsi, 8

not_eq:
    mov   rax, 1
eq:
    pop rbx

    ret