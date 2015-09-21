.Data
JmpByte		db 0EBh
oneNOP		db 90h
doubleNOP   dw 9090h
FourNOP		dd 90909090h

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