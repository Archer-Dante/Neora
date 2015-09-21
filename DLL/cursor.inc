.Data

Cursor_Back1 dd 00425EB9h
Cursor_Back2 dd 00428746h
Cursor_Back3 dd 0043B4F4h
Cursor_Back4 dd 0043D050h


.Code

CursorFix1 proc
		JMP [Cursor_Back1]
CursorFix1 endp

CursorFix2 proc
		JMP [Cursor_Back2]
CursorFix2 endp

CursorFix3 proc
		JMP [Cursor_Back3]
CursorFix3 endp

CursorFix4 proc

		PUSH 7F00h
		PUSH 0
		CALL DWORD PTR DS:[4471DCh]
		PUSH EAX
		CALL DWORD PTR DS:[4471F8h]

		JMP [Cursor_Back4]
		
CursorFix4 endp