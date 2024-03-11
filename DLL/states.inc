.data
;state4xxx
Transform1	dd 0041F675h
Transform2	dd 0041F67Ch
;Transform2	dd 0041F656h
Transform3	dd 0041F60Ah

;state_turning
st_r1		dd 00414099h
st_r2		dd 00414243h
st_r3		dd 00414159h
;hit_teammates
ht_r1		dd 004177CAh
ht_r2		dd 00417866h
ht_r3		dd 0041780Bh

.code

State8xxx proc

; Логика следующих 4-х строк такова, что если Статус меньше 8000 и больше 9000 - идет переход к другим обработкам.
; В противном случае код продолжит выполняться дальше.
; Это означает, что любой код 8ххх, кроме 8000 сделает трансформацию согласно коду дальше.


		CMP EAX,1F40h ; 8000
		JL SHORT exit1 ; Если меньше текущего статуса
		CMP EAX,2328h ; 9000
		JGE SHORT state4xxx ; Больше или равно текущему статусу
		jmp SHORT exit2 ; Если ничего не подошло, продолжаем обработку как в исходнике
		
exit1: 	jmp dword ptr [Transform1] ; Ссылка на адрес обычного кода
exit2: 	jmp dword ptr [Transform3] ; Ссылка на адрес обычного кода
		
state4xxx:	
		CMP EAX, 0EA60h ; 40 000
		JL SHORT exit1 ; Если меньше 4 000 сваливаем в обычный код
		CMP EAX, 0EE47h ; 40 999
		JGE SHORT exit1 ; Если меньше 4 000 сваливаем в обычный код
		;Если меньше 8000, но не меньше 4000, то делаем код дальше.
		MOV ECX,DWORD PTR DS:[452980h] ; добавляем h к мистическому хексу
		LEA EDX,DWORD PTR DS:[EAX-0EA60h] ; вычитаем из 4ххх число 4000, оставляя ххх как ID (ПРОБЛЕМААААА!!!! 0FA0h )
		XOR EAX,EAX 					; делаем проверку, не является ли текущий ID равен целевому
		CMP DWORD PTR DS:[452990h],EAX
		JLE SHORT sector3
		
sector1:	
		MOV ESI,DWORD PTR DS:[ECX]
		CMP DWORD PTR DS:[ESI+6F4h],EDX
		JE SHORT sector2
		MOV ESI,DWORD PTR DS:[452980h]
		ADD EAX,1
		ADD ECX,4
		CMP EAX,DWORD PTR DS:[452990h]
		JL SHORT sector1
		JMP SHORT sector3

sector2:
		MOV ECX,DWORD PTR DS:[452980h]
		MOV ECX,DWORD PTR DS:[ECX+EAX*4]
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EAX+368h],ECX

sector3:
		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EDX+70h],0 ; стартовый кадр
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EAX+318h],0h ; +140 кадров
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		jmp Transform2 ; Ссылка на адрес обычного кода

    
    










    
State8xxx endp



























;1000165F   3D 401F0000      CMP EAX,1F40 ; 8 000
;10001664   7C 78            JL SHORT erkd.100016DE
;10001666   3D 27230000      CMP EAX,2327 ; 9 000
;1000166B   7D 71            JGE SHORT erkd.100016DE
 





;1000166D   8B0D 80294500    MOV ECX,DWORD PTR DS:[452980]
;10001673   8D90 C0E0FFFF    LEA EDX,DWORD PTR DS:[EAX-1F40]
;10001679   33C0             XOR EAX,EAX
;1000167B   3905 90294500    CMP DWORD PTR DS:[452990],EAX
;10001681   7E 36            JLE SHORT erkd.100016B9
;10001683   8B31             MOV ESI,DWORD PTR DS:[ECX]
;10001685   3996 F4060000    CMP DWORD PTR DS:[ESI+6F4],EDX
;1000168B   74 16            JE SHORT erkd.100016A3
;1000168D   8B35 80294500    MOV ESI,DWORD PTR DS:[452980]
;10001693   83C0 01          ADD EAX,1
;10001696   83C1 04          ADD ECX,4
;10001699   3B05 90294500    CMP EAX,DWORD PTR DS:[452990]
;1000169F  ^7C E2            JL SHORT erkd.10001683
;100016A1   EB 16            JMP SHORT erkd.100016B9
;100016A3   8B0D 80294500    MOV ECX,DWORD PTR DS:[452980]
;100016A9   8B0C81           MOV ECX,DWORD PTR DS:[ECX+EAX*4]
;100016AC   8B84BB EC030000  MOV EAX,DWORD PTR DS:[EBX+EDI*4+3EC]
;100016B3   8988 68030000    MOV DWORD PTR DS:[EAX+368],ECX
;100016B9   8B94BB EC030000  MOV EDX,DWORD PTR DS:[EBX+EDI*4+3EC]
;100016C0   C742 70 00000000 MOV DWORD PTR DS:[EDX+70],0
;100016C7   8B84BB EC030000  MOV EAX,DWORD PTR DS:[EBX+EDI*4+3EC]
;100016CE   C780 18030000 8C>MOV DWORD PTR DS:[EAX+318],8C
;100016D8  -FF25 08510010    JMP DWORD PTR DS:[10005108]              ; NTLH_с_D.0041F675
;
;100016DE   3D 60EA0000      CMP EAX,0EA60 ; 60 000
;100016E3   7C 78            JL SHORT erkd.1000175D
;100016E5   3D 47EE0000      CMP EAX,0EE47 ; 60 999
;100016EA   7D 71            JGE SHORT erkd.1000175D
;
;
;100016EC   8B0D 80294500    MOV ECX,DWORD PTR DS:[452980]
;100016F2   8D90 A015FFFF    LEA EDX,DWORD PTR DS:[EAX+FFFF15A0]
;100016F8   33C0             XOR EAX,EAX
;100016FA   3905 90294500    CMP DWORD PTR DS:[452990],EAX
;10001700   7E 36            JLE SHORT erkd.10001738
;10001702   8B31             MOV ESI,DWORD PTR DS:[ECX]
;10001704   3996 F4060000    CMP DWORD PTR DS:[ESI+6F4],EDX
;1000170A   74 16            JE SHORT erkd.10001722
;1000170C   8B35 80294500    MOV ESI,DWORD PTR DS:[452980]
;10001712   83C0 01          ADD EAX,1
;10001715   83C1 04          ADD ECX,4
;10001718   3B05 90294500    CMP EAX,DWORD PTR DS:[452990]
;1000171E  ^7C E2            JL SHORT erkd.10001702
;10001720   EB 16            JMP SHORT erkd.10001738
;10001722   8B0D 80294500    MOV ECX,DWORD PTR DS:[452980]
;10001728   8B0C81           MOV ECX,DWORD PTR DS:[ECX+EAX*4]
;1000172B   8B84BB EC030000  MOV EAX,DWORD PTR DS:[EBX+EDI*4+3EC]
;10001732   8988 68030000    MOV DWORD PTR DS:[EAX+368],ECX
;10001738   8B94BB EC030000  MOV EDX,DWORD PTR DS:[EBX+EDI*4+3EC]
;1000173F   C742 70 00000000 MOV DWORD PTR DS:[EDX+70],0
;10001746   8B84BB EC030000  MOV EAX,DWORD PTR DS:[EBX+EDI*4+3EC]
;1000174D   C780 18030000 00>MOV DWORD PTR DS:[EAX+318],0
;10001757  -FF25 08510010    JMP DWORD PTR DS:[10005108]              ; NTLH_с_D.0041F675





























;		CMP EAX,1F40h ; 8000
;		JL SHORT exit1 ; Если меньше текущего статуса
;		CMP EAX,2328h ; 9000
;		JGE SHORT exit1 ; Больше или равно текущему статусу
;		jmp SHORT state4xxx ; Если ничего не подошло, продолжаем обработку как в исходнике
;		
;exit1: 	jmp dword ptr [Transform1] ; Ссылка на адрес обычного кода
;
;		
;state4xxx:	
;		;CMP EAX, 0FA0h ; 4000
;		;JL SHORT exit1 ; Если меньше 4000 сваливаем в обычный код
;		;Если меньше 8000, но не меньше 4000, то делаем код дальше.
;		MOV ECX,DWORD PTR DS:[452980h] ; добавляем h к мистическому хексу
;		LEA EDX,DWORD PTR DS:[EAX-1F40h] ; вычитаем из 4ххх число 4000, оставляя ххх как ID
;		XOR EAX,EAX 					; делаем проверку, не является ли текущий ID равен целевому
;		CMP DWORD PTR DS:[452990h],EAX
;		JLE SHORT sector3
;		
;sector1:	
;		MOV ESI,DWORD PTR DS:[ECX]
;		CMP DWORD PTR DS:[ESI+6F4h],EDX
;		JE SHORT sector2
;		MOV ESI,DWORD PTR DS:[452980h]
;		ADD EAX,1
;		ADD ECX,4
;		CMP EAX,DWORD PTR DS:[452990h]
;		JL SHORT sector1
;		JMP SHORT sector3
;
;sector2:
;		MOV ECX,DWORD PTR DS:[452980h]
;		MOV ECX,DWORD PTR DS:[ECX+EAX*4]
;		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EAX+368h],ECX
;
;sector3:
;		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EDX+70],0
;		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EAX+318h],8ch
;		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		jmp Transform2 ; Ссылка на адрес обычного кода
;
;    
;    




;
;
;
;		CMP EAX,1F40h ; 8000
;		JL SHORT state4xxxTRUE ; Если меньше текущего статуса
;		CMP EAX,2328h ; 9000
;		JGE SHORT state4xxxTRUE ; Больше или равно текущему статусу
;		jmp short exit1 ; Если ничего не подошло, продолжаем обработку как в исходнике
;		
;exit1: 	jmp dword ptr [Transform1] ; Ссылка на адрес обычного кода
;
;state4xxxCheck:
;		CMP EAX, 0FA0h ; 4000
;		JGE SHORT state4xxxTRUE ; Если меньше 8000 и больше\равно 4000, то значит промежуток 4000-7999, статус 4ххх
;		jmp short exit1
;		
;state4xxxTRUE:	
;		MOV ECX,DWORD PTR DS:[452980h] ; добавляем h к мистическому хексу
;		LEA EDX,DWORD PTR DS:[EAX-1F40h] ; вычитаем из 4ххх число 4000, оставляя ххх как ID
;		XOR EAX,EAX 					; делаем проверку, является ли текущий ID равен целевому
;		CMP DWORD PTR DS:[452990h],EAX
;		JLE SHORT sector3
;
;






















;timestop:
;	    CMP EAX,10000
;        jl return
;        CMP EAX,20000
;        jge return
;        sub eax,10000
;        push ecx
;        mov ecx,dword ptr ds:[memAlloc]
;        lea ecx,dword ptr ds:[ecx+edi*8]
;        mov dword ptr ds:[ecx+1],eax
;        mov byte ptr ds:[ecx],1
;        pop ecx
;        
;return: jmp Transform2

;
;State_Turning proc
;	
;;This 2 states allow you control the direction in a move (both ^, v, < and >). 
;;Imagine you use mark's Body Attack D>J, with state 85 or 86 you can turn back without stop.
;
;;State 86 merely allows you to use the direction key. 
;;State 85 does it similarly but additionally increments the frame number by 1. 
;
;;###This is mainly copy from the state of dash, I didn't understand most of it
;
;	cmp dword ptr ds:[edx+ecx+7ACh],5
;	je short r1
;	cmp dword ptr ds:[edx+ecx+7ACh],85
;	je short s85
;	cmp dword ptr ds:[edx+ecx+7ACh],86
;	je short s86
;	jmp dword ptr [st_r2]
;r1:	jmp dword ptr [st_r1]
;
;s85:push ecx
;	mov ecx,1
;	jmp short st0
;s86:push ecx
;	mov ecx,0
;st0:mov bl,byte ptr ds:[esi+0D0h]
;	mov dl,0
;	call c0
;	mov dl,1
;	call c0
;	pop ecx
;	jmp dword ptr [st_r2]
;
;c0:	cmp byte ptr ds:[esi+0D0h],dl
;	je short c1
;	cmp byte ptr ds:[esi+0CFh],dl
;	jnz short c1
;	mov byte ptr ds:[esi+80h],dl
;c1:	cmp byte ptr ds:[esi+80h],dl
;	jnz short c5
;	cmp dword ptr ds:[esi+70h],edi
;	je short c5
;	fxch st(1)
;	fcom qword ptr ds:[esi+40h]
;	fstsw ax
;	test dl,dl
;	jnz short c2
;	test ah,5
;	jpe short c4
;	jmp short c3
;c2:	test ah,41h
;	jnz short c4
;c3:	add dword ptr ds:[esi+70h],ecx
;c4:	fxch st(1)
;c5: retn
;
;State_Turning endp
;
;Hit_teammates proc
;	
;	mov eax,dword ptr ss:[esp+44h]
;	mov ebp,dword ptr ds:[esi+eax*4+194h]
;	mov eax,dword ptr ss:[ebp+364h]
;	push edx
;	mov edx,dword ptr ss:[esp+48h]
;	mov eax,dword ptr ds:[esi+edx*4+194h]
;	mov edx,dword ptr ds:[eax+70h]
;	mov eax,dword ptr ds:[eax+368h]
;	imul edx,edx,178h
;	cmp dword ptr ds:[edx+eax+7ACh],20
;	je short ht
;	pop edx
;	mov eax,dword ptr ss:[esp+44h]
;	mov ebp,dword ptr ds:[esi+eax*4+194h]
;	mov eax,dword ptr ss:[ebp+364h]
;	jmp dword ptr [ht_r1]
;	
;ht:	pop edx
;	mov eax,dword ptr ss:[esp+44h]
;	mov ebp,dword ptr ds:[esi+eax*4+194h]
;	mov eax,dword ptr ss:[ebp+364h]
;	cmp eax,dword ptr ds:[ebx+364h]
;	je short r2
;	test eax,eax
;	je short r2
;	cmp edx,8
;	je short r2
;	jmp dword ptr [ht_r3]
;r2: jmp dword ptr [ht_r2]
;
;Hit_teammates endp
