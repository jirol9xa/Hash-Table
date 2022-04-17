section .text
global   comP

comP:
    push rbx

    mov    rax, QWORD [rsi]     ;// now we have 8 symbs of value in rax
    mov    rbx, QWORD [rdi]     ;// now we have 8 symbs of elem in rbx
    cmp    rax, rbx
    jnz    finish
    add    rdi, 8
    add    rsi, 8

    mov    rax, QWORD [rsi]     ;// now we have 8 symbs of value in rax
    mov    rbx, QWORD [rdi]     ;// now we have 8 symbs of elem in rbx
    cmp    rax, rbx
    jnz    finish
    add    rdi, 8
    add    rsi, 8

    mov    rax, QWORD [rsi]     ;// now we have 8 symbs of value in rax
    mov    rbx, QWORD [rdi]     ;// now we have 8 symbs of elem in rbx
    sub    rax, rbx
    ;jne    finish
    ;add    rdi, 8
    ;add    rsi, 8
    ;
    ;mov    rax, QWORD [rsi]     ;// now we have 8 symbs of value in rax
    ;mov    rbx, QWORD [rdi]     ;// now we have 8 symbs of elem in rbx
    ;cmp    rax, rbx

finish:
    pop rbx

    ret