; This is where the Assembly magic happens.
; We need to execute VMXON, VMCLEAR, VMPTRLD, etc.
.code
VmExitHandler PROC
    ; TODO: Handle VM-Exits and trap TPM MMIO
    ret
VmExitHandler ENDP
END
