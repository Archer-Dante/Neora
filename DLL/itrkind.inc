.data
	;itr/kind8
	ik8_pos1	dd 00430C8Ch ;???
	ik8_pos2	dd 0043002Dh ;fixed
	ik8_pos3	dd 0043087Ch ;fixed
	ik8_pos4	dd 00447A08h ;match
	;itr/kind8_2
	;ik8_other1	dd 004176CBh
	ik8_other1	dd 00417535h ;fixed?
	;ik8_other2	dd 00417F59h
	ik8_other2	dd 00417A10h ;fixed?
.code
itr_kind8 proc

	CMP EDX,8
	JE kind8
;	CMP EDX,85
;	JE kind85
	JMP ik8_pos2

kind8:

	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h]
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX
	FLD DWORD PTR DS:[EAX+14h]
	FISTP DWORD PTR DS:[EBX+70h]
	FLD QWORD PTR DS:[EDI+58h]
	FSTP QWORD PTR DS:[EBX+58h]
	FLD QWORD PTR DS:[EDI+68h]
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h]
	JMP ik8_pos3
	
 
itr_kind8 endp

itr_kind8_2 proc
 
	CMP EDX,8
	JE kind8
	CMP EDX,85
	JE kind8
	JMP ik8_other1
 
kind8:
	MOV ECX,DWORD PTR DS:[EDI*4+ESI+194h]
	MOV EAX,DWORD PTR DS:[ECX+368h]
	CMP DWORD PTR DS:[EAX+6F8h],0
	JNE skip
	JMP ik8_other1

 
kind85:
	MOV ECX,DWORD PTR DS:[EDI*4+ESI+194h]
	MOV EAX,DWORD PTR DS:[ECX+368h]
	CMP DWORD PTR DS:[EAX+6F8h],0
	JMP ik8_other1

skip:
	JMP ik8_other2
	
	
itr_kind8_2 endp