.data
fix_hidden   			db "hidden:",00
fix_silence  			db "silence:",00
fix_slow	 			db "slow:",00
fix_slow_b   			dd 004110E0h
fix_confuse 			db "confuse:",00
fix_sound				db "sound:",0000

new_ohp					db "ohp:",00

new_start_hp 			db "start_hp:",00
new_start_mp 			db "start_mp:",00
new_start_hp_max		db "start_hp_max:",00
new_start_mp_max		db "start_mp_max:",00
new_hp_regen			db "hp_regen:",00
new_mp_regen			db "mp_regen:",00
new_hp_regen_cd			db "hp_regen_cd:",00
new_mp_regen_cd			db "mp_regen_cd:",00
new_hp_limit			db "hp_limit:",00
new_mp_limit			db "mp_limit:",00
new_start_frame			db "start_frame:",00
new_end_frame			db "end_frame:",00

new_hp_regen_min		db "hp_regen_min:",00
new_hp_regen_max		db "hp_regen_max:",00
new_hp_dark_regen		db "hp_dark_regen:",00
new_hp_dark_regen_cd	db "hp_dark_regen_cd:",00
new_hp_regen_type		db "hp_regen_type:",00
new_mp_regen_type		db "mp_regen_type:",00
new_mp_regen_cap		db "mp_regen_cap:",00

new_hp_regen_hurt_cd	db "hp_regen_hurt_cd:",00
new_mp_regen_hurt_cd	db "mp_regen_hurt_cd:",00
new_mp_regen_on_hurt	db "mp_regen_on_hurt:",00

new_stat_0				db "stat_0:",00
new_stat_1				db "stat_1:",00
new_stat_2				db "stat_2:",00
new_stat_3				db "stat_3:",00
new_stat_4				db "stat_4:",00
new_stat_5				db "stat_5:",00
new_stat_6				db "stat_6:",00
new_stat_7				db "stat_7:",00
new_stat_8				db "stat_8:",00
new_stat_9				db "stat_9:",00
new_resist_0			db "resist_0:",00
new_resist_1			db "resist_1:",00
new_resist_2			db "resist_2:",00
new_resist_3			db "resist_3:",00
new_resist_4			db "resist_4:",00
new_resist_5			db "resist_5:",00
new_resist_6			db "resist_6:",00
new_resist_7			db "resist_7:",00
new_resist_8			db "resist_8:",00
new_resist_9			db "resist_9:",00


new_crit_chance			db "crit_chance:",00
new_crit_power			db "crit_power:",00

new_stat_0_per_lvl		db "stat_0_per_lvl:",00
new_stat_1_per_lvl		db "stat_1_per_lvl:",00
new_stat_2_per_lvl		db "stat_2_per_lvl:",00
new_stat_3_per_lvl		db "stat_3_per_lvl:",00
new_stat_4_per_lvl		db "stat_4_per_lvl:",00
new_stat_5_per_lvl		db "stat_5_per_lvl:",00
new_stat_6_per_lvl		db "stat_6_per_lvl:",00
new_stat_7_per_lvl		db "stat_7_per_lvl:",00
new_stat_8_per_lvl		db "stat_8_per_lvl:",00
new_stat_9_per_lvl		db "stat_9_per_lvl:",00

new_resist_0_per_lvl	db "resist_0_per_lvl:",00
new_resist_1_per_lvl	db "resist_1_per_lvl:",00
new_resist_2_per_lvl	db "resist_2_per_lvl:",00
new_resist_3_per_lvl	db "resist_3_per_lvl:",00
new_resist_4_per_lvl	db "resist_4_per_lvl:",00
new_resist_5_per_lvl	db "resist_5_per_lvl:",00
new_resist_6_per_lvl	db "resist_6_per_lvl:",00
new_resist_7_per_lvl	db "resist_7_per_lvl:",00
new_resist_8_per_lvl	db "resist_8_per_lvl:",00
new_resist_9_per_lvl	db "resist_9_per_lvl:",00


new_crit_chance_per_lvl	db "crit_chance_per_lvl:",00
new_crit_power_per_lvl	db "crit_power_per_lvl:",00

new_hp_max_per_lvl		db "hp_max_per_lvl:",00
new_hp_regen_per_lvl	db "hp_regen_per_lvl:",00
new_mp_max_per_lvl		db "mp_max_per_lvl:",00
new_mp_regen_per_lvl	db "mp_regen_per_lvl:",00
new_hp_regen_min_per_lvl db "hp_regen_min_per_lvl:",00
new_hp_regen_max_per_lvl db "hp_regen_max_per_lvl:",00
new_mp_regen_cap_per_lvl db "mp_regen_cap_per_lvl:",00

right_data				dd 0040F2EBh
next_data 				dd 0040F79Ch
original_data			dd 0040F3BCh

Player_Stat 			dd 0042D50Ch
Com_AI_Stat 			dd 0042D400h

another_attr1			dd 004107ACh

ohp_back 				dd 00420223h



new_xp_cost				db "xp_cost:",00

template_integer		db "%d",00
template_string			db "%s",00
template_float			db "%f",00
template_double			db "%lf",00


original_itrs			dd 00410ECFh
custom_itrs				dd 00411153h
original_write_down		dd 00411143h
new_dtype				db "dtype:",00
new_scale_stat			db "scale_stat:",00
new_scale_value			db "scale_value:",00
new_aframe	 			db "aframe:",00
new_vframe	 			db "vframe:",00
new_sframe	 			db "sframe:",00

bdy_finished			dd 0041127Fh
bdy_original_write		dd 00411257h
bdy_original_read		dd 004111E6h
new_untouchable 		db "untouchable:",00
new_repulse 			db "repulse:",00
new_dmg_owner			db "dmg_owner:",00
new_dmg_dec				db "dmg_dec:",00


.code


Loading_Rework proc
	
	weapon_hp:
			LEA EDX,DWORD PTR SS:[EBP+90h]
			MOV EDI,004486D8h           	; заменяем MOV на LEA, т.к. нам нужен адрес переменной, а не она сама
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,11
			REPE CMPSB [EDI],[ESI]
			; если не оно, переходим к проверке наших атрибутов
			JNZ [weapon_drop_hurt]
			JMP [right_data]
	weapon_drop_hurt:
			MOV EDI,004486C4h 
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [hp]
			ADD EDX,4h
			JMP [right_data]
	hp:
			MOV EDI,004486DFh 
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,4
			REPE CMPSB [EDI],[ESI]
			JNZ [recmp]
			ADD EDX,8h
			JMP [right_data]
	recmp:
			MOV EDI,00447E98h 
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,7
			REPE CMPSB [EDI],[ESI]
			JNZ [ratio]
			ADD EDX,0Ch
			JMP [right_data]
	ratio:
			MOV EDI,00447B58h
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,7
			REPE CMPSB [EDI],[ESI]
			JNZ [memory_allocation_in_ID_section]
			ADD EDX,10h 
			JMP [right_data]








		memory_allocation_in_ID_section:
			MOV EAX,DWORD PTR DS:[EBP+0B0h] ; проверка, есть ли поинтер
			TEST EAX,EAX
			JNZ [already_alloced]
			
			PUSH 512						; биты
			CALL DWORD PTR DS:[447194h] 	; mAlloc
			ADD ESP,4h
			MOV DWORD PTR DS:[EBP+0B0h],EAX ; записываем указатель
			
				; ниже маленькая процедура очиски выделенной памяти от мусора
				XOR ECX,ECX
				cleaning:
				MOV BYTE PTR DS:[EAX+ECX],0
				INC ECX
				CMP ECX,512
				JL [cleaning]

		already_alloced:


















	start_hp:
			LEA EDI,[new_start_hp]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10						; размер строки
			REPE CMPSB [EDI],[ESI]
			JNZ [start_hp_max]
			MOV EDX,0h						; смещение по +байту
			JMP [proceed_decimal]
	start_hp_max:
			LEA EDI,[new_start_hp_max]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,14
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_]
			MOV EDX,4h
			JMP [proceed_decimal]
 	hp_regen_:
			LEA EDI,[new_hp_regen]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_cd]
			MOV EDX,8h
			JMP [proceed_decimal]
	hp_regen_cd:
			LEA EDI,[new_hp_regen_cd]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,13
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_dark_regen]
			MOV EDX,0Ch
			JMP [proceed_decimal]
	hp_dark_regen:
			LEA EDI,[new_hp_dark_regen]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_dark_regen_cd]
			MOV EDX,10h
			JMP [proceed_decimal]
	hp_dark_regen_cd:
			LEA EDI,[new_hp_dark_regen_cd]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_limit]
			MOV EDX,14h
			JMP [proceed_decimal]
	hp_limit:
			LEA EDI,[new_hp_limit]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_type]
			MOV EDX,18h
			JMP [proceed_decimal]
	hp_regen_type:
			LEA EDI,[new_hp_regen_type]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_min]
			MOV EDX,1Ch
			JMP [proceed_decimal]
	hp_regen_min:
			LEA EDI,[new_hp_regen_min]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,14
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_max]
			MOV EDX,20h
			JMP [proceed_decimal]
	hp_regen_max:
			LEA EDI,[new_hp_regen_max]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,14
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_hurt_cd_check]
			MOV EDX,24h
			JMP [proceed_decimal]
	hp_regen_hurt_cd_check:
			LEA EDI,[new_hp_regen_hurt_cd]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [start_mp]
			MOV EDX,28h
			JMP [proceed_decimal]
			
			

	start_mp:
			LEA EDI,[new_start_mp]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10						; размер строки
			REPE CMPSB [EDI],[ESI]
			JNZ [start_mp_max]
			MOV EDX,40h						; смещение по +байту
			JMP [proceed_decimal]
	start_mp_max:
			LEA EDI,[new_start_mp_max]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,14
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_regen]
			MOV EDX,44h
			JMP [proceed_decimal]
	mp_regen:
			LEA EDI,[new_mp_regen]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_regen_cd]
			MOV EDX,48h
			JMP [proceed_decimal]
	mp_regen_cd:
			LEA EDI,[new_mp_regen_cd]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,13
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_limit]
			MOV EDX,4Ch
			JMP [proceed_decimal]
	mp_limit:
			LEA EDI,[new_mp_limit]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_regen_type]
			MOV EDX,50h
			JMP [proceed_decimal]
	mp_regen_type:
			LEA EDI,[new_mp_regen_type]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_regen_cap]
			MOV EDX,54h
			JMP [proceed_decimal]
	mp_regen_cap:
			LEA EDI,[new_mp_regen_cap]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,14
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_regen_hurt_cd_check]
			MOV EDX,58h
			JMP [proceed_decimal]
	mp_regen_hurt_cd_check:
			LEA EDI,[new_mp_regen_hurt_cd]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_regen_on_hurt_check]
			MOV EDX,5Ch
			JMP [proceed_decimal]
	mp_regen_on_hurt_check:
			LEA EDI,[new_mp_regen_on_hurt]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [xp_cost]
			MOV EDX,60h
			JMP [proceed_decimal]


	xp_cost:
			LEA EDI,[new_xp_cost]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,9
			REPE CMPSB [EDI],[ESI]
			JNZ [start_frame]
			MOV EDX,70h
			JMP [proceed_decimal]





	start_frame:
			LEA EDI,[new_start_frame]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,13
			REPE CMPSB [EDI],[ESI]
			JNZ [end_frame]
			MOV EDX,80h
			JMP [proceed_decimal]
	end_frame:
			LEA EDI,[new_end_frame]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,11
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_0]
			MOV EDX,84h
			JMP [proceed_decimal]
			







	stat_0:
			LEA EDI,[new_stat_0]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_1]
			MOV EDX,90h
			JMP [proceed_decimal]
	stat_1:
			LEA EDI,[new_stat_1]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_2]
			MOV EDX,94h
			JMP [proceed_decimal]
	stat_2:
			LEA EDI,[new_stat_2]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_3]
			MOV EDX,98h
			JMP [proceed_decimal]
	stat_3:
			LEA EDI,[new_stat_3]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_4]
			MOV EDX,9Ch
			JMP [proceed_decimal]
	stat_4:
			LEA EDI,[new_stat_4]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_5]
			MOV EDX,0A0h
			JMP [proceed_decimal]
	stat_5:
			LEA EDI,[new_stat_5]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_6]
			MOV EDX,0A4h
			JMP [proceed_decimal]
	stat_6:
			LEA EDI,[new_stat_6]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_7]
			MOV EDX,0A8h
			JMP [proceed_decimal]
	stat_7:
			LEA EDI,[new_stat_7]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_8]
			MOV EDX,0ACh
			JMP [proceed_decimal]
	stat_8:
			LEA EDI,[new_stat_8]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_9]
			MOV EDX,0B0h
			JMP [proceed_decimal]
	stat_9:
			LEA EDI,[new_stat_9]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_0]
			MOV EDX,0B4h
			JMP [proceed_decimal]



	resist_0:
			LEA EDI,[new_resist_0]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_1]
			MOV EDX,0B8h
			JMP [proceed_decimal]
	resist_1:
			LEA EDI,[new_resist_1]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_2]
			MOV EDX,0BCh
			JMP [proceed_decimal]
	resist_2:
			LEA EDI,[new_resist_2]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_3]
			MOV EDX,0C0h
			JMP [proceed_decimal]
	resist_3:
			LEA EDI,[new_resist_3]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_4]
			MOV EDX,0C4h
			JMP [proceed_decimal]
	resist_4:
			LEA EDI,[new_resist_4]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_5]
			MOV EDX,0C8h
			JMP [proceed_decimal]
	resist_5:
			LEA EDI,[new_resist_5]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_6]
			MOV EDX,0CCh
			JMP [proceed_decimal]
	resist_6:
			LEA EDI,[new_resist_6]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_7]
			MOV EDX,0D0h
			JMP [proceed_decimal]
	resist_7:
			LEA EDI,[new_resist_7]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_8]
			MOV EDX,0D4h
			JMP [proceed_decimal]
	resist_8:
			LEA EDI,[new_resist_8]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_9]
			MOV EDX,0D8h
			JMP [proceed_decimal]
	resist_9:
			LEA EDI,[new_resist_9]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,10
			REPE CMPSB [EDI],[ESI]
			JNZ [crit_chance]
			MOV EDX,0DCh
			JMP [proceed_decimal]




	crit_chance:
			LEA EDI,[new_crit_chance]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,13
			REPE CMPSB [EDI],[ESI]
			JNZ [crit_power]
			MOV EDX,0E0h
			JMP [proceed_decimal]
			
	crit_power:
			LEA EDI,[new_crit_power]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,12
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_0_per_lvl]
			MOV EDX,0E4h
			JMP [proceed_decimal]














	stat_0_per_lvl:
			LEA EDI,[new_stat_0_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_1_per_lvl]
			MOV EDX,100h
			JMP [proceed_float]
	stat_1_per_lvl:
			LEA EDI,[new_stat_1_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_2_per_lvl]
			MOV EDX,104h
			JMP [proceed_float]
	stat_2_per_lvl:
			LEA EDI,[new_stat_2_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_3_per_lvl]
			MOV EDX,108h
			JMP [proceed_float]
	stat_3_per_lvl:
			LEA EDI,[new_stat_3_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_4_per_lvl]
			MOV EDX,10Ch
			JMP [proceed_float]
	stat_4_per_lvl:
			LEA EDI,[new_stat_4_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_5_per_lvl]
			MOV EDX,110h
			JMP [proceed_float]
	stat_5_per_lvl:
			LEA EDI,[new_stat_5_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_6_per_lvl]
			MOV EDX,114h
			JMP [proceed_float]
	stat_6_per_lvl:
			LEA EDI,[new_stat_6_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_7_per_lvl]
			MOV EDX,118h
			JMP [proceed_float]
	stat_7_per_lvl:
			LEA EDI,[new_stat_7_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_8_per_lvl]
			MOV EDX,11Ch
			JMP [proceed_float]
	stat_8_per_lvl:
			LEA EDI,[new_stat_8_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [stat_9_per_lvl]
			MOV EDX,120h
			JMP [proceed_float]
	stat_9_per_lvl:
			LEA EDI,[new_stat_9_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,15
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_0_per_lvl]
			MOV EDX,124h
			JMP [proceed_float]



	resist_0_per_lvl:
			LEA EDI,[new_resist_0_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_1_per_lvl]
			MOV EDX,128h
			JMP [proceed_float]
	resist_1_per_lvl:
			LEA EDI,[new_resist_1_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_2_per_lvl]
			MOV EDX,12Ch
			JMP [proceed_float]
	resist_2_per_lvl:
			LEA EDI,[new_resist_2_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_3_per_lvl]
			MOV EDX,130h
			JMP [proceed_float]
	resist_3_per_lvl:
			LEA EDI,[new_resist_3_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_4_per_lvl]
			MOV EDX,134h
			JMP [proceed_float]
	resist_4_per_lvl:
			LEA EDI,[new_resist_4_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_5_per_lvl]
			MOV EDX,138h
			JMP [proceed_float]
	resist_5_per_lvl:
			LEA EDI,[new_resist_5_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_6_per_lvl]
			MOV EDX,13Ch
			JMP [proceed_float]
	resist_6_per_lvl:
			LEA EDI,[new_resist_6_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_7_per_lvl]
			MOV EDX,140h
			JMP [proceed_float]
	resist_7_per_lvl:
			LEA EDI,[new_resist_7_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_8_per_lvl]
			MOV EDX,144h
			JMP [proceed_float]
	resist_8_per_lvl:
			LEA EDI,[new_resist_8_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [resist_9_per_lvl]
			MOV EDX,148h
			JMP [proceed_float]
	resist_9_per_lvl:
			LEA EDI,[new_resist_9_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [crit_chance_per_lvl]
			MOV EDX,14Ch
			JMP [proceed_float]

	crit_chance_per_lvl:
			LEA EDI,[new_crit_chance_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,21
			REPE CMPSB [EDI],[ESI]
			JNZ [crit_power_per_lvl]
			MOV EDX,150h
			JMP [proceed_float]
			
	crit_power_per_lvl:
			LEA EDI,[new_crit_power_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,20
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_max_per_lvl]
			MOV EDX,154h
			JMP [proceed_float]

	hp_max_per_lvl:
			LEA EDI,[new_hp_max_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,16
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_per_lvl]
			MOV EDX,158h
			JMP [proceed_float]

	hp_regen_per_lvl:
			LEA EDI,[new_hp_regen_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_max_per_lvl]
			MOV EDX,15Ch
			JMP [proceed_float]

	mp_max_per_lvl:
			LEA EDI,[new_mp_max_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,16
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_regen_per_lvl]
			MOV EDX,160h
			JMP [proceed_float]

	mp_regen_per_lvl:
			LEA EDI,[new_mp_regen_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,18
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_min_per_lvl]
			MOV EDX,164h
			JMP [proceed_float]

	hp_regen_min_per_lvl:
			LEA EDI,[new_hp_regen_min_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,22
			REPE CMPSB [EDI],[ESI]
			JNZ [hp_regen_max_per_lvl]
			MOV EDX,168h
			JMP [proceed_float]
			
	hp_regen_max_per_lvl:
			LEA EDI,[new_hp_regen_max_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,22
			REPE CMPSB [EDI],[ESI]
			JNZ [mp_regen_cap_per_lvl]
			MOV EDX,16Ch
			JMP [proceed_float]
			
	mp_regen_cap_per_lvl:
			LEA EDI,[new_mp_regen_cap_per_lvl]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,22
			REPE CMPSB [EDI],[ESI]
			JNZ [original_load]
			MOV EDX,170h
			JMP [proceed_float]



		proceed_float:
			LEA EAX,[template_float]
			PUSH EAX ; "%f"
			JMP [data_type_defined_alredy]

		proceed_decimal:
			LEA EAX,[template_integer]
			PUSH EAX ; "%d"
			
		data_type_defined_alredy:
			MOV EAX,DWORD PTR DS:[EBP+0B0h] ; проверка, есть ли поинтер
;			TEST EAX,EAX
;			JNZ [already_alloced]
;			
;			PUSH EDX
;			PUSH 512						; биты
;			CALL DWORD PTR DS:[447194h] 	; mAlloc
;			POP EDX ;fix
;			POP EDX ; восстанавливаем настоящий EDX
;			MOV DWORD PTR DS:[EBP+0B0h],EAX ; записываем указатель
;			ADD EDX,EAX						; складываем адрес и смещение
;			
;				; ниже маленькая процедура очиски выделенной памяти от мусора
;				XOR ECX,ECX
;				cleaning:
;				MOV BYTE PTR DS:[EAX+ECX],0
;				INC ECX
;				CMP ECX,512
;				JL [cleaning]
;			
;			JMP [write_data]
;			
;		already_alloced:
			ADD EDX,EAX	
			
		write_data:
			POP ECX 	; ASCII "%d" или "%f"
			MOV EAX,DWORD PTR SS:[ESP+14h]
			PUSH EDX
			PUSH ECX
			PUSH EAX
			CALL EBX
			ADD ESP,0Ch

skip:
			JMP [next_data]
original_load:
			MOV EAX,0040F78Bh ; восстанавливаем оригинальный EAX, без него краш, ибо на него есть JMP
			JMP [original_data]
		
Loading_Rework endp



Loading_Rework_SlowAttr proc

			LEA EDI,[fix_slow]
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,6
			JMP [fix_slow_b]

Loading_Rework_SlowAttr endp


Loading_Rework_ohp proc

			MOV EDI,44850Ch
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,5
			REPE CMPSB [EDI],[ESI]
			JNZ SHORT [check_ohp]
			ADD EDX,18h ; только если это oid
			JMP EAX
	
check_ohp:	LEA EDI,[new_ohp] ; атрибут ohp
			LEA ESI,DWORD PTR SS:[ESP+70h] ; строчка на обработке
			MOV ECX,5 ; размер включая 00
			REPE CMPSB [EDI],[ESI] ; сравнение
			JNZ SHORT [wrong] ; если ошибка
			ADD EDX,0A4h ; только если это ohp
			JMP EAX

wrong:		JMP [another_attr1]

Loading_Rework_ohp endp


ohp proc
		CMP ECX,5
		JE SHORT [proceed]
		CMP ECX,34h
		JNZ SHORT [ohp_check]
		
		proceed: 
		MOV ECX,10
		MOV DWORD PTR DS:[EAX+2FCh],ECX
		MOV EAX,DWORD PTR DS:[EBX+ESI*4+3ECh]
		MOV DWORD PTR DS:[EAX+304h],ECX
		MOV EDX,DWORD PTR DS:[EBX+ESI*4+3ECh]
		MOV DWORD PTR DS:[EDX+300h],ECX
		MOV EAX,DWORD PTR DS:[EBX+ESI*4+3ECh]
		MOV DWORD PTR DS:[EAX+308h],5
		JMP SHORT [skip]
		
ohp_check:
		MOV ECX,DWORD PTR SS:[ESP+38h]
		MOV ECX,DWORD PTR DS:[ECX+92Ch]
		TEST ECX,ECX
		JZ	[skip]
		MOV DWORD PTR DS:[EAX+2FCh],ECX
		MOV EAX,DWORD PTR DS:[EBX+ESI*4+3ECh]
		MOV DWORD PTR DS:[EAX+304h],ECX
		MOV EDX,DWORD PTR DS:[EBX+ESI*4+3ECh]
		MOV DWORD PTR DS:[EDX+300h],ECX
		MOV EAX,DWORD PTR DS:[EBX+ESI*4+3ECh]
		MOV DWORD PTR DS:[EAX+308h],5
		
skip:	JMP [ohp_back]

ohp endp


Loading_Rework_bdy proc

		memory_allocation_in_ID_section:
			MOV ECX,DWORD PTR SS:[ESP+10h]  ; указатель на Frame страницу
			MOV EDI,DWORD PTR DS:[ECX+12Ch] ; количество BDY в фрейме
			MOV ECX,DWORD PTR DS:[ECX+134h] ; указатель на BDY
			DEC EDI							; вычитаем 1 (т.к. отсчет от 0, а не от 1)
			IMUL EDI,EDI,28h				; получаем нужное смещение после перемножения
			ADD EDI,ECX						; добавляем общее смещение на область со всеми BDY
			
			MOV ESI,DWORD PTR DS:[EDI+20h]
			TEST ESI,ESI
			JNZ [already_alloced]

			PUSH 32						; биты
			CALL DWORD PTR DS:[447194h] ; mAlloc
			ADD ESP,4h
			MOV DWORD PTR DS:[EDI+20h],EAX ; записываем указатель

				; ниже маленькая процедура очиски выделенной памяти от мусора
				XOR ECX,ECX
				cleaning:
				MOV BYTE PTR DS:[EAX+ECX],0
				INC ECX
				CMP ECX,32
				JL [cleaning]

		already_alloced:

			
			MOV EDI,0044851Ch                     ;  ASCII "kind:"
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,6
			REPE CMPSB [EDI],[ESI]
			JNZ [untouchable_check]
			JMP [original_write]

	untouchable_check:
			LEA EDI,[new_untouchable] ; атрибут Untouchable
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,13
			REPE CMPSB [EDI],[ESI]
			JNZ SHORT [repulse_check]
			MOV EDX,0
			JMP [proceed]
	repulse_check:
			LEA EDI,[new_repulse] ; атрибут Repulse
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,9
			REPE CMPSB [EDI],[ESI]
			JNZ SHORT [aframe_check]
			MOV EDX,4
			JMP [proceed]
	aframe_check:
			LEA EDI,[new_aframe] ; атрибут aframe
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ SHORT [vframe_check]
			MOV EDX,8
			JMP [proceed]
	vframe_check:
			LEA EDI,[new_vframe] ; атрибут vframe
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ SHORT [sframe_check]
			MOV EDX,0Ch
			JMP [proceed]
	sframe_check:
			LEA EDI,[new_sframe] ; атрибут sframe
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ SHORT [dmg_owner_check]
			MOV EDX,10h
			JMP [proceed]
	dmg_owner_check:
			LEA EDI,[new_dmg_owner] ; атрибут dmg_owner
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,11
			REPE CMPSB [EDI],[ESI]
			JNZ SHORT [dmg_dec_check]
			MOV EDX,14h
			JMP [proceed]
	dmg_dec_check:
			LEA EDI,[new_dmg_dec] ; атрибут dmg_dec
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,9
			REPE CMPSB [EDI],[ESI]
			JNZ SHORT [original_codes]
			MOV EDX,18h
			JMP [proceed]
			
			

	proceed:
			MOV ECX,DWORD PTR SS:[ESP+10h]  ; указатель на Frame страницу
			MOV EAX,DWORD PTR DS:[ECX+12Ch] ; количество BDY в фрейме
			MOV ECX,DWORD PTR DS:[ECX+134h] ; указатель на BDY
			DEC EAX							; вычитаем 1 (т.к. отсчет от 0, а не от 1)
			IMUL EAX,EAX,28h				; получаем нужное смещение после перемножения
			ADD EAX,ECX						; добавляем общее смещение на область со всеми BDY
			
			MOV ECX,DWORD PTR DS:[EAX+20h]
			MOV EAX,ECX 					; добавляем наше смещение EDX
			
			recording_data:
			ADD EAX,EDX						; добавляем смещение нашего атрибута
			MOV EDX,DWORD PTR SS:[ESP+14h]
			PUSH EAX
			PUSH 00447B08h                  ;  ASCII "%d"
			PUSH EDX
			CALL EBX
			ADD ESP,0Ch

			JMP [bdy_finished]
	

original_write:
			XOR EDX,EDX
			JMP [bdy_original_write]
original_codes:
			XOR EDX,EDX
			JMP [bdy_original_read]
	

Loading_Rework_bdy endp







Loading_Rework_itr proc

		memory_allocation_in_ITR_section:
			MOV EAX,DWORD PTR DS:[EDX+64h]
			TEST EAX,EAX  ; проверка, есть ли поинтер
			JNZ [already_alloced]
			
			PUSH EDX
			PUSH 32							; байты
			CALL DWORD PTR DS:[447194h] 	; mAlloc
			ADD ESP,4h
			POP EDX
			MOV DWORD PTR DS:[EDX+64h],EAX ; записываем указатель
			
				; ниже маленькая процедура очиски выделенной памяти от мусора
				XOR ECX,ECX
				cleaning:
				MOV BYTE PTR DS:[EAX+ECX],0
				INC ECX
				CMP ECX,32
				JL [cleaning]

		already_alloced:

		
		
		
			MOV EDI,00447AA8h                     ;  ASCII "x:"
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,3
			REPE CMPSB [EDI],[ESI]
			JNZ [dtype]
			ADD EDX,4
			JMP [original_write]
	dtype:
			LEA EDI,[new_dtype]
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,7
			REPE CMPSB [EDI],[ESI]
			JNZ [scale_stat]
			MOV EAX,0h
			JMP [write_down]
	scale_stat:
			LEA EDI,[new_scale_stat]  
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,12
			REPE CMPSB [EDI],[ESI]
			JNZ [scale_value]
			MOV EAX,4h
			JMP [write_down]
	scale_value:
			LEA EDI,[new_scale_value]  
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,13
			REPE CMPSB [EDI],[ESI]
			JNZ [crit_chance]
			MOV EAX,8h
			JMP [write_down]
	crit_chance:
			LEA EDI,[new_crit_chance]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,13
			REPE CMPSB [EDI],[ESI]
			JNZ [crit_power]
			MOV EAX,0Ch
			JMP [write_down]
	crit_power:
			LEA EDI,[new_crit_power]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,12
			REPE CMPSB [EDI],[ESI]
			JNZ [aframe]
			MOV EAX,10h
			JMP [write_down]
	aframe:
			LEA EDI,[new_aframe]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [vframe]
			MOV EAX,14h
			JMP [write_down]
	vframe:
			LEA EDI,[new_vframe]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [sframe]
			MOV EAX,18h
			JMP [write_down]
	sframe:
			LEA EDI,[new_sframe]           	
			LEA ESI,DWORD PTR SS:[ESP+70h]
			MOV ECX,8
			REPE CMPSB [EDI],[ESI]
			JNZ [skip]
			MOV EAX,1Ch
			JMP [write_down]



	write_down:
		ADD EAX,DWORD PTR DS:[EDX+64h]
		MOV EDX,EAX
		
		
		PUSH EDX
		PUSH 00447B08h                        ;  ASCII "%d"
		MOV EDX,DWORD PTR SS:[ESP+1Ch]
		PUSH EDX
		CALL EBX
		ADD ESP,0Ch
	
		JMP [custom_itrs]
		
		
	skip:
		MOV EAX,00411143h
		JMP [original_itrs]
		
	original_write:
		JMP [original_write_down]

Loading_Rework_itr endp







Player_Stats proc
		PUSH ECX
		MOV EDX,DWORD PTR DS:[ESI]

		
		MOV ECX,DWORD PTR DS:[EDX+368h] ; dat
		CMP ECX,0	; если отсутствует
		JE [no_pointer]
		MOV ECX,DWORD PTR DS:[ECX+0B0h] ; поинтер
		CMP ECX,0	; если отсутствует
		JE [no_pointer]
		CMP DWORD PTR DS:[ECX+40h],0
		JG [stage_m] ; если там не пусто, то запись уже выполнена ранее и ничего делать не нужно
		
		no_pointer:
		CMP DWORD PTR DS:[EAX],1 ; если режим стадий
		MOV DWORD PTR DS:[EDX+308h],0C8h ; стартовое число маны для VS
		JNE [stage_m]
		MOV DWORD PTR DS:[EDX+308h],1F4h ; перезапись на 500 маны
		JMP [stage_m]

stage_m:
		POP ECX
		JMP [Player_Stat]

Player_Stats endp


Computer_Stats proc
		PUSH ECX
		MOV EDX,DWORD PTR DS:[ESI+28h]

		
		MOV ECX,DWORD PTR DS:[EDX+368h] ; dat
		CMP ECX,0	; если отсутствует
		JE [no_pointer]
		MOV ECX,DWORD PTR DS:[ECX+0B0h] ; поинтер
		CMP ECX,0	; если отсутствует
		JE [no_pointer]
		CMP DWORD PTR DS:[ECX+40h],0
		JG [stage_m] ; если там не пусто, то запись уже выполнена ранее и ничего делать не нужно
		
		no_pointer:
		CMP DWORD PTR DS:[EAX],1 ; если режим стадий
		MOV DWORD PTR DS:[EDX+308h],0C8h ; стартовое число маны для VS
		JNE [stage_m]
		MOV DWORD PTR DS:[EDX+308h],1F4h ; перезапись на 500 маны
		JMP [stage_m]
		

stage_m:
		POP ECX
		JMP [Com_AI_Stat]

Computer_Stats endp




Initialization proc

		;PUSH EBX
		;PUSH ESI
		PUSH EDI
		MOV ESI,ECX
		MOV EDI,ECX
		MOV EBX,DWORD PTR DS:[ECX+368h] ; резервация указателя
		MOV ECX,202h ; число байт для очистки
		XOR EAX,EAX ; 0 как ресурс очистки
		REP STOS DWORD PTR ES:[EDI] ; процесс очистки


			CMP DWORD PTR SS:[ESP+0Ch],0041FDA1h ; место куда возвращается процедура, если вызвана из-за opoint
			JNE [not_opoint]					 ; единственный способ отсеять фикс для других вызовов процедуры
 			MOV EBX,EDX		; перезапись правильного указателя на дата-файл сразу же
							; без этого призываемые клоны и т.д. не имеют выделенной памяти
							; в EDX хранится нужный указатель только в случае opoint, но так же есть на смещении
							; ESP+58h, или вне процедуры инициализации это ESP+48h
			not_opoint:
			
			CMP DWORD PTR SS:[ESP+0Ch],0042D320h ; место куда возвращается процедура, если вызвана из-за Com-игрока
			JNE [not_com_player]				 ; единственный способ отсеять фикс для других вызовов процедуры
 			MOV EBX,EBP		; перезапись правильного указателя на дата-файл сразу же
							; без этого призываемые клоны и т.д. не имеют выделенной памяти
							; в EBP хранится нужный указатель только в случае Com-игрока
			not_com_player:
		
			CMP DWORD PTR SS:[ESP+0Ch],0042166Ah ; место куда возвращается процедура, если вызвана из-за падающего оружия
			JNE [not_weapon]				 ; единственный способ отсеять фикс для других вызовов процедуры
 			MOV EBX,DWORD PTR SS:[ESP+0]	; перезапись правильного указателя на дата-файл сразу же
							; без этого призываемые клоны и т.д. не имеют выделенной памяти
			not_weapon:
		
			MOV DWORD PTR DS:[ESI+368h],EBX ; запись указателя, оригинальная строка
		
		FLD QWORD PTR DS:[447920h]
		FST QWORD PTR DS:[ESI+50h]
		OR EAX,-1h
		FST QWORD PTR DS:[ESI+48h]
		FST QWORD PTR DS:[ESI+40h]
		FST QWORD PTR DS:[ESI+38h]
		FST QWORD PTR DS:[ESI+30h]
		FSTP QWORD PTR DS:[ESI+28h]
		FLDZ
		FST QWORD PTR DS:[ESI+68h]
		FST QWORD PTR DS:[ESI+60h]
		FSTP QWORD PTR DS:[ESI+58h]
		MOV ECX,1F4h ; ~500, можно освободить ECX, слегка увеличит затраты тактов
		; LEA EDI,DWORD PTR DS:[ESI+2E8h] - строчка освобождена, как и EDI
		; свободен EDI
		
		MOV DWORD PTR DS:[ESI+3F8h],EAX ; 
		MOV DWORD PTR DS:[ESI+2F4h],EAX	; 
		MOV DWORD PTR DS:[ESI+2F8h],EAX	; 
		MOV DWORD PTR DS:[ESI+354h],63h	; 99 = 63h
		MOV DWORD PTR DS:[ESI+2FCh],ECX	; 500
		MOV DWORD PTR DS:[ESI+300h],ECX	; 500
		MOV DWORD PTR DS:[ESI+304h],ECX	; 500
		MOV DWORD PTR DS:[ESI+308h],ECX	; 500
		MOV DWORD PTR DS:[ESI+360h],EAX	; 
		MOV DWORD PTR DS:[ESI+324h],EAX	; 
		MOV DWORD PTR DS:[ESI+328h],EAX	; 
		MOV DWORD PTR DS:[ESI+32Ch],EAX	; 
		MOV DWORD PTR DS:[ESI+33Ch],EAX	; 
		MOV EAX,3E8h
		MOV DWORD PTR DS:[ESI+2E8h],EAX	; 
		MOV DWORD PTR DS:[ESI+2ECh],EAX	; 
		MOV DWORD PTR DS:[ESI+2F0h],EAX	; 
		NEG EAX
		MOV DWORD PTR DS:[ESI+400h],EAX	; 
		MOV DWORD PTR DS:[ESI+3FCh],EAX	; 
		
		; начиная отсюда свободен и EAX

		CMP EBP, 13h	; в этом месте всегда значение 13, если происходит лишь запуск ЕХЕ.
		JE [skip_all] 	; в таком состоянии у игры всегда неверный EBX, что крашит игру, там даже не адрес, а мусор
		
		CMP EBX, 0h		; если указатель вдруг пустой \ память очищена
		JLE [skip_all]
	
	
;		CMP DWORD PTR DS:[EBX+6F8h],0 ; проверка типа
;		JNE [skip_all]
		
		CMP DWORD PTR DS:[ESI+190h],0 ; проверяем, есть ли выделенная память
		JNE [skip_mAlloc] ; пропускаем, если уже есть
			
			; пострадают EAX, ECX и EDX
			PUSH 1D00h						; биты
			CALL DWORD PTR DS:[447194h] 	; mAlloc
			ADD ESP,4h
			
			MOV DWORD PTR DS:[ESI+190h],EAX
			
				; ниже маленькая процедура очиски выделенной памяти от мусора
				XOR ECX,ECX
				cleaning:
				MOV BYTE PTR DS:[EAX+ECX],0
				INC ECX
				CMP ECX,1D00h
				JL [cleaning]

		skip_mAlloc: ; уходим
		
			; // Изначально эта часть отвечала за фильтрацию объектов, кому не нужно выделение памяти
			; // Но сейчас выделяем память всем. Однако атрибуты есть всё-таки не у всех.
			; // Поэтому если указателя на собственные атрибуты нет - просто не загружаем их
			; // Такой подход несколько лучше, чем просто выделять память заранее пустую...
			; // Ведь она автоматически выделится если будет хотя бы 1 новый атрибут
			;CMP DWORD PTR DS:[EBX+0B0h],0	; если указатель на новые атрибуты вдруг пустой \ память очищена
			;JLE [skip_all]					; !!! более не актуально, так как сейчас выделяем память всем и всегда !!!
		
		MOV EAX,DWORD PTR DS:[EBX+0B0h]
		TEST EAX,EAX
		JLE [skip_all]
		MOV EDX,DWORD PTR DS:[ESI+190h]
		
		
		start_hp_check:
		CMP DWORD PTR DS:[EAX+0],0 ; start_hp
		JE [start_hp_max_check]
		MOV ECX,DWORD PTR DS:[EAX+0]
		MOV DWORD PTR DS:[ESI+2FCh],ECX
		MOV DWORD PTR DS:[ESI+300h],ECX
		
		start_hp_max_check:
		CMP DWORD PTR DS:[EAX+4],0 ; start_hp_max
		JE [regen_hp_check]
		MOV ECX,DWORD PTR DS:[EAX+4]
		MOV DWORD PTR DS:[ESI+304h],ECX
		
		regen_hp_check:
		CMP DWORD PTR DS:[EAX+8],0 ; hp_regen
		JE [regen_hp_cd_check]
		MOV ECX,DWORD PTR DS:[EAX+8]
		MOV DWORD PTR DS:[EDX+5Ch],ECX
		
		regen_hp_cd_check:
		CMP DWORD PTR DS:[EAX+0Ch],0 ; hp_regen_cd
		JE [regen_hp_dark_check]
		MOV ECX,DWORD PTR DS:[EAX+0Ch]
		MOV DWORD PTR DS:[EDX+0B0h],ECX
		
		regen_hp_dark_check:
		CMP DWORD PTR DS:[EAX+10h],0 ; hp_dark_regen
		JE [regen_hp_dark_cd_check]
		MOV ECX,DWORD PTR DS:[EAX+10h]
		MOV DWORD PTR DS:[EDX+74h],ECX

		regen_hp_dark_cd_check:
		CMP DWORD PTR DS:[EAX+14h],0 ; hp_dark_regen_cd
		JE [start_mp_check]
		MOV ECX,DWORD PTR DS:[EAX+14h]
		MOV DWORD PTR DS:[EDX+0B8h],ECX

		start_mp_check:
		CMP DWORD PTR DS:[EAX+40h],0 ; start_mp
		JE [start_mp_max_check]
		MOV ECX,DWORD PTR DS:[EAX+40h]
		MOV DWORD PTR DS:[ESI+308h],ECX

		start_mp_max_check:
		CMP DWORD PTR DS:[EAX+44h],0 ; start_mp_max
		JE [regen_mp_check]
		MOV ECX,DWORD PTR DS:[EAX+44h]
		MOV DWORD PTR DS:[EDX+60h],ECX
		
		regen_mp_check:
		CMP DWORD PTR DS:[EAX+48h],0 ; mp_regen
		JE [regen_mp_cd_check]
		MOV ECX,DWORD PTR DS:[EAX+48h]
		MOV DWORD PTR DS:[EDX+64h],ECX
		
		regen_mp_cd_check:
		CMP DWORD PTR DS:[EAX+4Ch],0 ; mp_regen_cd
		JE [regen_mp_cap_check]
		MOV ECX,DWORD PTR DS:[EAX+4Ch]
		MOV DWORD PTR DS:[EDX+0C0h],ECX
		
		regen_mp_cap_check:
		CMP DWORD PTR DS:[EAX+58h],0 ; mp_regen_cap
		JE [mp_regen_type]
		MOV ECX,DWORD PTR DS:[EAX+58h]
		MOV DWORD PTR DS:[EDX+70h],ECX
		
		mp_regen_type:
		CMP DWORD PTR DS:[EAX+54h],0 ; mp_regen_type
		JE [hp_regen_type]
		MOV ECX,DWORD PTR DS:[EAX+54h]
		MOV DWORD PTR DS:[EDX+0C8h],ECX
		
		hp_regen_type:
		CMP DWORD PTR DS:[EAX+1Ch],0 ; hp_regen_type
		JE [hp_regen_min]
		MOV ECX,DWORD PTR DS:[EAX+1Ch]
		MOV DWORD PTR DS:[EDX+0D8h],ECX
		
		hp_regen_min:
		CMP DWORD PTR DS:[EAX+20h],0 ; hp_regen_min
		JE [hp_regen_max]
		MOV ECX,DWORD PTR DS:[EAX+20h]
		MOV DWORD PTR DS:[EDX+68h],ECX
		
		hp_regen_max:
		CMP DWORD PTR DS:[EAX+24h],0 ; hp_regen_min
		JE [mp_limit]
		MOV ECX,DWORD PTR DS:[EAX+24h]
		MOV DWORD PTR DS:[EDX+6Ch],ECX
		
		mp_limit:
		CMP DWORD PTR DS:[EAX+50h],0 ; mp_limit
		JE [hp_limit]
		MOV ECX,DWORD PTR DS:[EAX+50h]
		MOV DWORD PTR DS:[EDX+0CCh],ECX
		
		hp_limit:
		CMP DWORD PTR DS:[EAX+18h],0 ; hp_limit
		JE [after_damage_cd]
		MOV ECX,DWORD PTR DS:[EAX+18h]
		MOV DWORD PTR DS:[EDX+0D0h],ECX
		
		after_damage_cd:
		CMP DWORD PTR DS:[EAX+28h],0 ; hp_regen_hurt_cd
		JE [mp_regen_hurt_cd_begin]
		MOV ECX,DWORD PTR DS:[EAX+28h]
		MOV DWORD PTR DS:[EDX+78h],ECX

		mp_regen_hurt_cd_begin:
		CMP DWORD PTR DS:[EAX+5Ch],0 ; mp_regen_hurt_cd
		JE [mp_regen_on_hurt_begin]
		MOV ECX,DWORD PTR DS:[EAX+5Ch]
		MOV DWORD PTR DS:[EDX+7Ch],ECX

		mp_regen_on_hurt_begin:
		CMP DWORD PTR DS:[EAX+60h],0 ; mp_regen_on_hurt
		JE [no_more_stats]
		MOV ECX,DWORD PTR DS:[EAX+60h]
		MOV DWORD PTR DS:[EDX+80h],ECX
		

		no_more_stats:


		skip_all:

		; выделение памяти под функцию определения какой bdy был ударен
			PUSH 80							; биты
			CALL DWORD PTR DS:[447194h] 	; mAlloc
			ADD ESP,4h
			MOV DWORD PTR DS:[ESI+170h],EAX
				; ниже маленькая процедура очиски выделенной памяти от мусора
				XOR ECX,ECX
				cleaning2:
				MOV BYTE PTR DS:[EAX+ECX],0
				INC ECX
				CMP ECX,80
				JL [cleaning2]



		
		POP EDI
		POP ESI
		POP EBX
		RETN

Initialization endp





