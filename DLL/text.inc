.data
loadingText db "lfforever.ru",0
Load dd 004243B1h

.code


Loading proc
	
	PUSH 3Ch   ; Y cord
	PUSH 260h  ; X cord
	CMP EDX,2
	MOV DWORD PTR DS:[4511BCh],EDX
	JGE a
	
	;MOV EDX,DWORD PTR SS:[ESP+1Ch]  original text
	LEA EDX,DWORD PTR SS:[loadingText]
	MOV EAX,DWORD PTR DS:[455608h]
	PUSH 0FF6464h  ; text color
	PUSH 00601B0Dh ;background color
	PUSH EDX
	PUSH EAX
	JMP return

a:	ADD EDX,-5
	CMP EDX,2
	JA b
	
	;MOV ECX,DWORD PTR SS:[ESP+1Ch]  original text
	LEA ECX,DWORD PTR SS:[loadingText]
	MOV EDX,DWORD PTR DS:[455608h]
	PUSH 0FFFFFFh   ;text color
	PUSH 00601B0Dh  ; background color
	PUSH ECX
	PUSH EDX
	JMP return
	
b:	;MOV EAX,DWORD PTR SS:[ESP+1Ch]   original text
	LEA EAX,DWORD PTR SS:[loadingText]
	MOV ECX,DWORD PTR DS:[455608h]
	PUSH 0FFB4B4h  ;text color
	PUSH 00601B0Dh ;background color
	PUSH EAX
	PUSH ECX
	
return:
	JMP Load
	
Loading endp
