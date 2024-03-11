.Data

mp_back		dd 0041FB28h
hp_back		dd 0041F9E8h
hp_back2	dd 0041FA48h
stage_fix	dd 00437108h


.Code

mana_regen proc

	PUSH EBX
	MOV EBX,DWORD PTR DS:[ESI+190h]
	TEST EBX,EBX
	JLE [done]

		CMP DWORD PTR DS:[ESI+2FCh],0
		JLE [dont_regen]
		CMP DWORD PTR DS:[ESI+304h],0
		JLE [dont_regen]
		
					CMP DWORD PTR DS:[EBX+0DCh],0 ; если есть время отката от полученного урона
					JLE [do_regen1]
					DEC DWORD PTR DS:[EBX+0DCh]
					JMP [dont_regen]
					do_regen1:
		

			MOV EAX,1F4h
			MOV ECX,DWORD PTR DS:[ESI+308h]
			CMP DWORD PTR DS:[ESI+2F4h],-1
			JE SHORT [not_clone]
			MOV EAX,96h
			CMP ECX,EAX
			JGE [dont_regen]
			
		not_clone:	
			CMP DWORD PTR DS:[ESI+8h],0 ; invincible
			JL  [dont_regen]
			
			MOV EAX, DWORD PTR DS:[EBX+70h] ; mana cap
			CMP EAX,0
			JLE [can_regen]
			CMP DWORD PTR DS:[ESI+308h],EAX
			JGE [dont_regen]
		
		can_regen:
		
			MOV EDX, DWORD PTR DS:[EBX+0C0h] ; Cooldown
			ADD EDX, 2 					 	 ; standard value (original cooldown)
			CMP EDX, DWORD PTR DS:[EBX+0C4h] ; Timer
			JNE [add_count_then_dont_regen]
			MOV DWORD PTR DS:[EBX+0C4h], 0 ; reset
			
			MOV EAX,DWORD PTR DS:[ESI+304h]				
			MOV EDX,DWORD PTR DS:[ESI+2FCh]
			CMP EAX,EDX
			JLE [smth_hp]
			MOV EAX,EDX
			
		smth_hp:
			MOV ECX,DWORD PTR DS:[ESI+368h]
			MOV EDX,DWORD PTR DS:[ECX+6F4h]
			CMP EDX,51
			JE [boss_mp]
			CMP EDX,52
			JNZ [usual_mp]
			
		boss_mp:
			SAR EAX,1

		usual_mp:
			MOV ECX,DWORD PTR DS:[ESI+304h] ; here must be a max hp	 	
			IMUL EAX,EAX,5
			CDQ
			IDIV ECX
			TEST EDX,EDX
			JNZ [dec_skip]
			DEC EAX
		dec_skip:
			MOV ECX,5
			SUB ECX,EAX
			
					; code that makes "mp_regen_type:" work
					CMP DWORD PTR DS:[EBX+0C8h],0 ; mp_regen_type
					JLE [mana_plus_mp_regen]
					MOV ECX, DWORD PTR DS:[EBX+64h] ; mp regen
					JMP [add_mana]
					
		mana_plus_mp_regen:
			ADD ECX, DWORD PTR DS:[EBX+64h]
					
		add_mana:
			ADD DWORD PTR DS:[ESI+308h],ECX ; regen moment
			
			MOV EAX, DWORD PTR DS:[EBX+70h] ; mana cap
			CMP EAX,0
			JLE [dont_regen]
			CMP EAX, DWORD PTR DS:[ESI+308h] ; current mana
			JGE [dont_regen] ; it's done regen already :)
			MOV DWORD PTR DS:[ESI+308h],EAX ; fixes if current mana is too much for cap

		dont_regen:
			CMP DWORD PTR DS:[EBX+60h],0	; max mana
			MOV ECX,1F4h					; max mp - original
			JE [no_custom_max_mana]
			MOV ECX,DWORD PTR DS:[EBX+60h]  ; max mp - neora				
			
			no_custom_max_mana:
			MOV EAX,DWORD PTR DS:[ESI+308h] ; mp current
			CMP EAX,ECX
			JG [fix_mp]
			TEST EAX,EAX
			JGE [skip]
			XOR ECX,ECX
			
		fix_mp:
			MOV DWORD PTR DS:[ESI+308h],ECX


skip:
					; code that makes "limit_mp:" work
				    MOV EAX, DWORD PTR DS:[ESI+368h]
					MOV EAX, DWORD PTR DS:[EAX+0B0h]
					CMP EAX, 0						
					JLE [done]	
					
					CMP DWORD PTR DS:[EBX+0CCh],0 ; limit_mp
					JLE [done]
					MOV EDX,DWORD PTR DS:[EBX+60h] ; max mana
					CMP DWORD PTR DS:[EBX+0CCh],EDX
					JGE[done]
					MOV EAX, DWORD PTR DS:[EBX+0CCh] 
					MOV DWORD PTR DS:[EBX+60h],EAX ; max mana can't be higher than limit_mp			
done:
			POP EBX
			JMP [mp_back]


add_count_then_dont_regen:
			ADD DWORD PTR DS:[EBX+0C4h],1
			JMP [dont_regen]


mana_regen endp


hp_regen proc

	PUSH EBX	
;	CMP DWORD PTR DS:[ESI+190h],0
;	JLE [skip_dead]
	MOV EBX,DWORD PTR DS:[ESI+190h]
	TEST EBX,EBX
	JLE [skip_dead]

	MOV EDX,DWORD PTR DS:[ESI+2FCh]
	TEST EDX,EDX
	JLE [skip_dead]
	
					CMP DWORD PTR DS:[EBX+0D4h],0 ; если есть время отката от полученного урона
					JLE [do_regen2]
					DEC DWORD PTR DS:[EBX+0D4h]
					JMP [skip_dead]
					do_regen2:
	
	
    		; code that makes "limit_hp:" work
    		
;		    MOV EAX, DWORD PTR DS:[ESI+368h]
;			MOV EAX, DWORD PTR DS:[EAX+0B0h]
;			CMP EAX, 0						
;			JLE [dark_hp]	

			
			CMP DWORD PTR DS:[EBX+0D0h],0 ; limit_hp
			JLE [check_regen_type]
			MOV EDX, DWORD PTR DS:[ESI+304h] ; max hp
			CMP DWORD PTR DS:[EBX+0D0h],EDX ; limit_hp
			JGE[check_regen_type]
			MOV EAX, DWORD PTR DS:[EBX+0D0h] ; limit_hp
			MOV DWORD PTR DS:[ESI+304h],EAX ; max hp
			
						
	check_regen_type:
	CMP DWORD PTR DS:[EBX+0D8h],1 ; regen type
	JNE [dark_hp]
	
	MOV EDX, DWORD PTR DS:[ESI+2FCh] ; HP
	
	CMP DWORD PTR DS:[EBX+68h],0 	; hp_regen_min
	JLE [hp_regen_max_check]
	CMP EDX, DWORD PTR DS:[EBX+68h] ; hp_regen_min
	JLE [skip_fix]
	
	CMP DWORD PTR DS:[EBX+68h],0	; hp_regen_max
	JLE [dark_hp]
	hp_regen_max_check:
	CMP EDX, DWORD PTR DS:[EBX+6Ch] ; hp_regen_max
	JGE [skip_fix]	
	

; dark hp regen section
	dark_hp:

	MOV EDX, DWORD PTR DS:[EBX+0B8h] ; Cooldown
	CMP EDX, DWORD PTR DS:[EBX+0BCh] ; Timer
	JNE [add_dark_timer_then_proceed]
	MOV DWORD PTR DS:[EBX+0BCh], 0 ; reset
	
	MOV EDX, DWORD PTR DS:[EBX+74h] ; dark hp regen value
	ADD DWORD PTR DS:[ESI+300h],EDX ; dark hp
	MOV EDX, DWORD PTR DS:[ESI+304h] ; max hp
	CMP EDX, DWORD PTR DS:[ESI+300h] ; dark hp
	JGE [light_hp]
	MOV DWORD PTR DS:[ESI+300h], EDX ; fix dark hp
	JMP [light_hp]
	
	add_dark_timer_then_proceed:
	ADD DWORD PTR DS:[EBX+0BCh],1

; light hp regen section
	light_hp:
	
	MOV EDX, DWORD PTR DS:[EBX+0B0h] ; Cooldown
	ADD EDX, 11 					 ; standard value (original cooldown)
	CMP EDX, DWORD PTR DS:[EBX+0B4h] ; Timer
	JNE [skip_regen]
	MOV DWORD PTR DS:[EBX+0B4h], 0 ; reset
	

	MOV EDX, DWORD PTR DS:[EBX+5Ch] ; hp_regen
	INC EDX ; standart regen value 1
	
	
	ADD DWORD PTR DS:[ESI+2FCh],EDX ; standart regen
	
		; this code doesn't allow negative hp value kill character
		CMP DWORD PTR DS:[EBX+0D8h],2 	; hp_regen_type
		JL [all_is_fine]
		CMP DWORD PTR DS:[EBX+68h],0 	; hp_regen_min
		JLE [all_is_fine]
		CMP DWORD PTR DS:[ESI+2FCh],0
		JG [all_is_fine]
		MOV DWORD PTR DS:[ESI+2FCh],1
		all_is_fine:
	
	MOV EDX,DWORD PTR DS:[ESI+300h] ; dark red hp 
	CMP EDX,DWORD PTR DS:[ESI+2FCh] ; current hp
	JGE [skip_fix]
	MOV DWORD PTR DS:[ESI+2FCh], EDX ; fixes light HP over dark HP
	
	skip_fix:
	POP EBX
    JMP [hp_back]
    
    skip_regen:
    ADD DWORD PTR DS:[EBX+0B4h],1
    
    skip_dead:
    POP EBX
    JMP [hp_back2]
    
hp_regen endp


bottle_limit proc

	PUSH EAX
	MOV EAX,DWORD PTR SS:[EBP+EDI*4+3ECh]
	MOV EAX,DWORD PTR DS:[EAX+190h] ; max mana
	CMP DWORD PTR DS:[EAX+60h],0
	JLE [skip]
	MOV ECX, DWORD PTR DS:[EAX+60h]
	JMP [finish]

skip:
	MOV ECX,1F4h

finish:
	POP EAX
	RET


bottle_limit endp


stage_refill proc

		PUSH EDX
		
		MOV EDX,DWORD PTR DS:[EAX+190h]
		CMP DWORD PTR DS:[EDX+70h],0 ; mana cap
		MOV ECX,DWORD PTR DS:[EDX+60h] ; max mana
		JLE [no_cap]
		MOV ECX,DWORD PTR DS:[EDX+70h] ; mana cap
		CMP ECX,DWORD PTR DS:[EAX+308h]
		JLE [done]
		
		no_cap:
		TEST ECX,ECX
		JNZ [max_is_set]
		MOV ECX,500
		max_is_set:
		MOV DWORD PTR DS:[EAX+308h],ECX

		POP EDX
done:	JMP [stage_fix]

stage_refill endp













