	processor 6502
	include vcs.h
	include macro.h
	org $F000

YPosFromBot  = $80;
YPosFromBot2 = $70;
VisiblePlayerLine = $81;

Start
	CLEAN_START

	lda #$00   
	sta COLUBK
	
	lda #$1C   
	sta COLUP0

	lda #80
	sta YPosFromBot
	
	lda #58
	sta COLUP1
	lda #70
	sta YPosFromBot2

;VSYNC time
MainLoop
	lda #2
	sta VSYNC
	sta WSYNC
	sta WSYNC
	sta WSYNC
	lda #43
	sta TIM64T
	lda #0
	sta VSYNC

	lda #%00010000	;Down?
	bit SWCHA
	bne SkipMoveDown
	inc YPosFromBot
SkipMoveDown

	lda #%00100000	;Up?
	bit SWCHA
	bne SkipMoveUp
	dec YPosFromBot
SkipMoveUp

	ldx #0
	lda #%01000000	;Left?
	bit SWCHA
	bne SkipMoveLeft
	ldx #$10	;a 1 in the left nibble means go left

	lda #%00001000   ;a 1 in D3 of REFP0 says make it mirror
	sta REFP0

SkipMoveLeft
	lda #%10000000	;Right?
	bit SWCHA
	bne SkipMoveRight
	ldx #$F0	;a -1 in the left nibble means go right...

	lda #%00000000
	sta REFP0
SkipMoveRight


	stx HMP0	;set the move for player 0, not the missile like last time...	
	
	
	lda #%00000010	;Down?
	bit SWCHA
	bne SkipMoveDown
	inc YPosFromBot2
SkipMoveDown2

	lda #%00000001	;Up?
	bit SWCHA
	bne SkipMoveUp
	dec YPosFromBot2
SkipMoveUp2
	
;assum horiz speed will be zero
	ldx #0

	lda #%00000100	;Left?
	bit SWCHA
	bne SkipMoveLeft2
	;ldx #$10	;a 1 in the left nibble means go left

	
SkipMoveLeft2
	lda #%00001000	;Right?
	bit SWCHA
	bne SkipMoveRight2
	;ldx #$F0	;a -1 in the left nibble means go right...

SkipMoveRight2

	stx HMP1



; see if player and missile collide, and change the background color if so

	;just a review...comparisons of numbers always seem a little backwards to me,
	;since it's easier to load up the accumulator with the test value, and then
	;compare that value to what's in the register we're interested.
	;in this case, we want to see if D7 of CXM1P (meaning Player 0 hit
	; missile 1) is on. So we put 10000000 into the Accumulator,
	;then use BIT to compare it to the value in CXM1P

	lda #%10000000
	bit CXP0FB
	beq NoCollision	;skip if not hitting...
	lda YPosFromBot	;must be a hit! load in the YPos...
	sta COLUBK	;and store as the bgcolor
NoCollision
	sta CXCLR	;reset the collision detection for next time


WaitForVblankEnd
	lda INTIM
	bne WaitForVblankEnd
	ldy #191


	sta WSYNC
	sta HMOVE

	sta VBLANK


;main scanline loop...


ScanLoop
	sta WSYNC

; here the idea is that VisiblePlayerLine
; is zero if the line isn't being drawn now,
; otherwise it's however many lines we have to go

CheckActivatePlayer
	cpy YPosFromBot
	bne SkipActivatePlayer
	lda #8
	sta VisiblePlayerLine
SkipActivatePlayer



;set player graphic to all zeros for this line, and then see if
;we need to load it with graphic data
	lda #0
	sta GRP0
	sta GRP1


	ldx VisiblePlayerLine	;check the visible player line...
	beq FinishPlayer		;skip the drawing if its zero...


IsPlayerOn
	lda BigHeadGraphic-1,X	;otherwise, load the correct line from BigHeadGraphic
				;section below... it's off by 1 though, since at zero
				;we stop drawing
	sta GRP0		;put that line as player graphic
	
	lda BigHeadGraphic2-1,X
	sta GRP1
	
	dec VisiblePlayerLine 	;and decrement the line count
FinishPlayer


	dey
	bne ScanLoop

	lda #2
	sta WSYNC
	sta VBLANK
	ldx #30
OverScanWait
	sta WSYNC
	dex
	bne OverScanWait
	jmp  MainLoop

BigHeadGraphic
	.byte #%11000011
	.byte #%01111110
	.byte #%00111100
	.byte #%11000011
	.byte #%00011000
	.byte #%00111100
	.byte #%00011100
	.byte #%00111100
	
BigHeadGraphic2
	.byte #%11000011
	.byte #%01111110
	.byte #%00111100
	.byte #%11000011
	.byte #%00011000
	.byte #%00111100
	.byte #%00011100
	.byte #%00111111

	org $FFFC
	.word Start
	.word Start
