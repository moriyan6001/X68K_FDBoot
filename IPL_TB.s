	.include	\include\iocscall.mac

	.cpu	68000
	.text
boot:
	bra.w	entry

	dc.b	"FDD IPL"

	.even
entry:
	lea	(stack_end,pc),a7

	move.w	#$0,d1
	move.w	#$0,d2
	IOCS	_B_LOCATE

	IOCS	_OS_CURON

	lea.l	(TXT_MSG_PUSHKEY,pc),a1
	IOCS	_B_PRINT

	; KEY WAIT
	IOCS	_B_KEYINP

	lea.l	(TXT_MSG_LOADING,pc),a1
	IOCS	_B_PRINT

	; DISK READ
	; SIDE:0[裏], track1, sector1から8sector分を読み込んで、$3000からのRAM領域に配置
	move.l	#$03000001,d2			; sector len:3(1024), side = 0, sector = 1
	clr.l	d0
	move.w	#$1,d0				; track number
	swap	d0				; track:bit23-16
	add.l	d0,d2
	move.l	#$9000,d1			; drive0
	ori.w	#$0050,d1			; 0111_0000: MFM, RETRY, SEEK
	move.l	#8*1024,d3			; size
	move.l	#$3000,a1			; 読み込み先
	IOCS	_B_READ

	jmp	$3000

	.data
	.even

TXT_MSG_PUSHKEY:
	.dc.b	"original boot loader",$0d,$0a
	.dc.b	"PUSH ANY KEY",$0d,$0a,$00
	.even

TXT_MSG_LOADING:
	.dc.b	"LOADING...",$0d,$0a,$00

	.bss
	.even

stack:
	ds.b	256
stack_end:
	.end
