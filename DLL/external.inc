.data

Frame db "sprite\UI\FRAME.png",0
BackFrame1 dd 00426F0Eh

CS2 db "sprite\UI\CS2.png",0
BackFrame2 dd 00426EC3h

CS3 db "sprite\UI\CS3.png",0
BackFrame3 dd 00426ED2h

CS4 db "sprite\UI\CS4.png",0
BackFrame4 dd 00426EE1h

CS5 db "sprite\UI\CS5.png",0
BackFrame5 dd 00426EF0h

CS6 db "sprite\UI\CS6.png",0
BackFrame6 dd 00426EFFh

WORDS0 db "sprite\UI\WORDS0.png",0
BackFrame7 dd 00426F1Dh

WORDS1 db "sprite\UI\WORDS1.png",0
BackFrame8 dd 00426F2Ch

WORDS2 db "sprite\UI\WORDS2.png",0
BackFrame9 dd 00426F3Bh

WORDS3 db "sprite\UI\WORDS3.png",0
BackFrame10 dd 00426F4Ah

WORDS4 db "sprite\UI\WORDS4.png",0
BackFrame11 dd 00426F59h

WORDS5 db "sprite\UI\WORDS5.png",0
BackFrame12 dd 00426F68h

MENU_CLIP db "sprite\UI\MENU_CLIP.png",0
BackFrame13 dd 00425F44h

MENU_CLIP2 db "sprite\UI\MENU_CLIP2.png",0
BackFrame14 dd 00425F58h

MENU_CLIP3 db "sprite\UI\MENU_CLIP3.png",0
BackFrame15 dd 00425F67h

MENU_CLIP4 db "sprite\UI\MENU_CLIP4.png",0
BackFrame16 dd 00425F76h

MENU_CLIP5 db "sprite\UI\MENU_CLIP5.png",0
BackFrame17 dd 00425F85h

MENU_CLIP6 db "sprite\UI\MENU_CLIP6.png",0
BackFrame18 dd 00425F94h

ENDING db "sprite\UI\ENDING.png",0
BackFrame19 dd 00425FB2h

PAUSE db "sprite\UI\PAUSE.png",0
BackFrame20 dd 004273C1h

DEMO db "sprite\UI\DEMO.png",0
BackFrame21 dd 004273D5h

SCORE_BOARD1 db "sprite\UI\SCORE_BOARD1.png",0
BackFrame22 dd 004273E4h

SCORE_BOARD2 db "sprite\UI\SCORE_BOARD2.png",0
BackFrame23 dd 004273F3h

SCORE_BOARD3 db "sprite\UI\SCORE_BOARD3.png",0
BackFrame24 dd 00427402h

SCORE_BOARD4 db "sprite\UI\SCORE_BOARD4.png",0
BackFrame25 dd 00427411h

WIN_ALIVE db "sprite\UI\WIN_ALIVE.png",0
BackFrame26 dd 00427420h

WIN_DEAD db "sprite\UI\WIN_DEAD.png",0
BackFrame27 dd 0042742Fh

LOSE_DEAD db "sprite\UI\LOSE_DEAD.png",0
BackFrame28 dd 0042743Eh

CHARMENU db "sprite\UI\CHARMENU.png",0
BackFrame29 dd 0040C2D2h

CM1 db "sprite\UI\CM1.png",0
BackFrame30 dd 0040C2E1h

CM2 db "sprite\UI\CM2.png",0
BackFrame31 dd 0040C2F0h

CM3 db "sprite\UI\CM3.png",0
BackFrame32 dd 0040C2FFh

CM4 db "sprite\UI\CM4.png",0
BackFrame33 dd 0040C30Eh

CM5 db "sprite\UI\CM5.png",0
BackFrame34 dd 0040C31Dh

CMA db "sprite\UI\CMA.png",0
BackFrame35 dd 0040C32Ch

CMA2 db "sprite\UI\CMA2.png",0
BackFrame36 dd 0040C33Bh

CMC_ db "sprite\UI\CMC.png",0
BackFrame37 dd 0040C34Ah

RFACE db "sprite\UI\RFACE.png",0
BackFrame38 dd 0040C359h

SPARK db "sprite\UI\spark.png",0
BackFrame39 dd 0040C368h

.code

FRAMEimg proc
	MOV ECX, offset [Frame]
	PUSH ECX 
	JMP [BackFrame1]
FRAMEimg endp

CS2img proc
	MOV ECX, offset [CS2]
	PUSH ECX 
	JMP [BackFrame2]
CS2img endp

CS3img proc
	MOV ECX, offset [CS3]
	PUSH ECX 
	JMP [BackFrame3]
CS3img endp

CS4img proc
	MOV ECX, offset [CS4]
	PUSH ECX 
	JMP [BackFrame4]
CS4img endp
	
CS5img proc
	MOV ECX, offset [CS5]
	PUSH ECX 
	JMP [BackFrame5]
CS5img endp

CS6img proc
	MOV ECX, offset [CS6]
	PUSH ECX 
	JMP [BackFrame6]
CS6img endp
	
WORDS0img proc
	MOV ECX, offset [WORDS0]
	PUSH ECX 
	JMP [BackFrame7]
WORDS0img endp

WORDS1img proc
	MOV ECX, offset [WORDS1]
	PUSH ECX 
	JMP [BackFrame8]
WORDS1img endp

WORDS2img proc
	MOV ECX, offset [WORDS2]
	PUSH ECX 
	JMP [BackFrame9]
WORDS2img endp

WORDS3img proc
	MOV ECX, offset [WORDS3]
	PUSH ECX 
	JMP [BackFrame10]
WORDS3img endp

WORDS4img proc
	MOV ECX, offset [WORDS4]
	PUSH ECX 
	JMP [BackFrame11]
WORDS4img endp

WORDS5img proc
	MOV ECX, offset [WORDS5]
	PUSH ECX 
	JMP [BackFrame12]
WORDS5img endp

MENU_CLIPimg proc
	MOV ECX, offset [MENU_CLIP]
	PUSH ECX 
	JMP [BackFrame13]
MENU_CLIPimg endp

MENU_CLIP2img proc
	MOV ECX, offset [MENU_CLIP2]
	PUSH ECX 
	JMP [BackFrame14]
MENU_CLIP2img endp

MENU_CLIP3img proc
	MOV ECX, offset [MENU_CLIP3]
	PUSH ECX 
	JMP [BackFrame15]
MENU_CLIP3img endp

MENU_CLIP4img proc
	MOV ECX, offset [MENU_CLIP4]
	PUSH ECX 
	JMP [BackFrame16]
MENU_CLIP4img endp
	
MENU_CLIP5img proc
	MOV ECX, offset [MENU_CLIP5]
	PUSH ECX 
	JMP [BackFrame17]
MENU_CLIP5img endp

MENU_CLIP6img proc
	MOV ECX, offset [MENU_CLIP6]
	PUSH ECX 
	JMP [BackFrame18]
MENU_CLIP6img endp

ENDINGimg proc
	MOV ECX, offset [ENDING]
	PUSH ECX 
	JMP [BackFrame19]
ENDINGimg endp

PAUSEimg proc
	MOV ECX, offset [PAUSE]
	PUSH ECX 
	JMP [BackFrame20]
PAUSEimg endp

DEMOimg proc
	MOV ECX, offset [DEMO]
	PUSH ECX 
	JMP [BackFrame21]
DEMOimg endp

SCORE_BOARD1img proc
	MOV ECX, offset [SCORE_BOARD1]
	PUSH ECX 
	JMP [BackFrame22]
SCORE_BOARD1img endp

SCORE_BOARD2img proc
	MOV ECX, offset [SCORE_BOARD2]
	PUSH ECX 
	JMP [BackFrame23]
SCORE_BOARD2img endp

SCORE_BOARD3img proc
	MOV ECX, offset [SCORE_BOARD3]
	PUSH ECX 
	JMP [BackFrame24]
SCORE_BOARD3img endp

SCORE_BOARD4img proc
	MOV ECX, offset [SCORE_BOARD4]
	PUSH ECX 
	JMP [BackFrame25]
SCORE_BOARD4img endp

WIN_ALIVEimg proc
	MOV ECX, offset [WIN_ALIVE]
	PUSH ECX 
	JMP [BackFrame26]
WIN_ALIVEimg endp

WIN_DEADimg proc
	MOV ECX, offset [WIN_DEAD]
	PUSH ECX 
	JMP [BackFrame27]
WIN_DEADimg endp

LOSE_DEADimg proc
	MOV ECX, offset [LOSE_DEAD]
	PUSH ECX 
	JMP [BackFrame28]
LOSE_DEADimg endp

CHARMENUimg proc
	MOV ECX, offset [CHARMENU]
	PUSH ECX 
	JMP [BackFrame29]
CHARMENUimg endp

CM1img proc
	MOV ECX, offset [CM1]
	PUSH ECX 
	JMP [BackFrame30]
CM1img endp

CM2img proc
	MOV ECX, offset [CM2]
	PUSH ECX 
	JMP [BackFrame31]
CM2img endp
	
CM3img proc
	MOV ECX, offset [CM3]
	PUSH ECX 
	JMP [BackFrame32]
CM3img endp

CM4img proc
	MOV ECX, offset [CM4]
	PUSH ECX 
	JMP [BackFrame33]
CM4img endp

CM5img proc
	MOV ECX, offset [CM5]
	PUSH ECX 
	JMP [BackFrame34]
CM5img endp

CMAimg proc
	MOV ECX, offset [CMA]
	PUSH ECX 
	JMP [BackFrame35]
CMAimg endp

CMA2img proc
	MOV ECX, offset [CMA2]
	PUSH ECX 
	JMP [BackFrame36]
CMA2img endp

CMC_img proc
	MOV ECX, offset [CMC_]
	PUSH ECX 
	JMP [BackFrame37]
CMC_img endp

RFACEimg proc
	MOV ECX, offset [RFACE]
	PUSH ECX 
	JMP [BackFrame38]
RFACEimg endp

spark proc
	MOV ECX, offset [SPARK]
	PUSH ECX 
	JMP [BackFrame39]
spark endp













