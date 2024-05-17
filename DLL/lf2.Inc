.Data
JmpByte		db 0EBh

.Data?
lgJmp 					db 5 dup(?)

.Code

WriteMem proc	MemOffset:DWORD, DataPtr:DWORD, dataLen:DWORD

	LOCAL OldProt:DWORD

	invoke VirtualProtect, MemOffset, dataLen, PAGE_EXECUTE_READWRITE, addr OldProt
	invoke RtlMoveMemory, MemOffset, DataPtr, dataLen
	invoke VirtualProtect, MemOffset, dataLen, OldProt, addr OldProt
	ret

WriteMem endp

JmpPatch proc	uses ecx ebx	from:DWORD, to:DWORD

	mov	ebx, to
	mov	ecx, from
	add	ecx, 05h
	sub	ebx, ecx
	lea	ecx, lgJmp
	mov	byte ptr [ecx], 0E9h
	mov	dword ptr [ecx+1], ebx
	invoke WriteMem, from, addr lgJmp, 5
	ret

JmpPatch endp


CallPatch proc	uses ecx ebx	from:DWORD, to:DWORD

	mov	ebx, to
	mov	ecx, from
	add	ecx, 05h
	sub	ebx, ecx
	lea	ecx, lgJmp
	mov	byte ptr [ecx], 0E8h
	mov	dword ptr [ecx+1], ebx
	invoke WriteMem, from, addr lgJmp, 5
	ret

CallPatch endp








get_memory_alloc666 MACRO arg
	PUSH EDX
	PUSH ECX

	push arg
    CALL DWORD PTR DS:[447194h]

	XOR ECX,ECX
	clean:
	MOV BYTE PTR DS:[EAX+ECX],0
	INC ECX
	CMP ECX,100
	JL [clean]

	ADD ESP,4
	POP ECX
	POP EDX
ENDM




get_memory_alloc proc	memory

	PUSH EDX
	PUSH ECX

	push memory
    CALL DWORD PTR DS:[447194h]

	XOR ECX,ECX
	clean:
	MOV BYTE PTR DS:[EAX+ECX],0
	INC ECX
	CMP ECX,memory
	JL [clean]

	ADD ESP,4
	POP ECX
	POP EDX
	RET

get_memory_alloc endp