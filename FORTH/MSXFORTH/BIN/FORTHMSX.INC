;
MSX_SCROFF   equ 41H
MSX_SCRON    equ 44H
MSX_WVDP     equ 47H
MSX_RDVRAM   equ 4AH
MSX_WRTVRAM  equ 4DH
MSX_VFILL    equ 56H
MSX_LDIRVR   equ 59H
MSX_LDIRRV   equ 5CH
MSX_CHGMOD   equ 5FH
MSX_COLOR    equ 62H
MSX_WRTPSG   equ 93H
MSX_RDPSG    equ 96H
MSX_CHRGET   equ 9FH
MSX_CON      equ 0A2H
MSX_PRN      equ 0A5H
MSX_SLOTCFG  equ 0A8H
MSX_PRNSTAT  equ 0ABH
MSX_BEEP     equ 0C0H
MSX_POSIT    equ 0C6H
MSX_HIDEKEYS equ 0CCH
MSX_SHOWKEYS equ 0CFH
MSX_GTSTCK   equ 0D5H
MSX_GTTRIG   equ 0D8H
MSX_GTPAD    equ 0DBH
MSX_GTPDL    equ 0DEH
MSX_CLS      equ 0777H
MSX_ISKEY    equ 0D6AH
;

SAVEREGS:ld (VAR1),bc
   ld (VAR2),ix
   ld (VAR3),iy
   ret
;
RESTREGS:ld bc,(VAR1)
   ld ix,(VAR2)
   ld iy,(VAR3)
   ret
;
CTIME:   db 4,'TIME'
   dw CBACKUP
   dw $+2
   ld hl,0FC9EH
   jp HPUSH
;
CFSTOP:   db 5,'FSTOP'
   dw CTIME
FSTOP:   dw $+2
   ld hl,MSX_INTFLG
   jp HPUSH
;
CLOCK:   db 4,'LOCK'
   dw CFSTOP
LOCK:   dw $+2
   ld a,-1
   ld (MSX_INTFLG),a
   jp NEXT
;
CULOCK:   db 6,'UNLOCK'
   dw CLOCK
ULOCK:   dw $+2
   xor a
   ld (MSX_INTFLG),a
   ld (MSX_INTFLG),a
   jp NEXT
;
CCOLUMN:db 7,'COLUMNS'
   dw CULOCK
   dw $+2
   pop hl
   ld a,l
   ld hl,MSX_LINLEN
   cp (hl)
   jp z,NEXT
   ld (hl),a
   push af
   push bc
   call CLS
   call MSX_SHOWKEYS
   pop bc
   ld a,(MSX_SCRMOD)
   cp 2
   jp m,COL1
   pop af
   inc a
   ld (NCOLG),a
   jp NEXT
COL1:   cp 1
   jr nz,COL0
   pop af
   ld (MSX_LINL32),a
   jp NEXT
COL0:   pop af
   ld (MSX_LINL40),a
   jp NEXT
;
CROWS:   db 4,'ROWS'
   dw CCOLUMN
   dw $+2
   pop hl
   ld a,L
   ld hl,MSX_CRTCNT
   cp (hl)
   jp z,NEXT
   ld (hl),a
   push bc
   call CLS
   call MSX_SHOWKEYS
   pop bc
   jp NEXT
;
CCALSLT:db 6,'CALSLT'
   dw CROWS
   dw $+2
   call SAVEREGS
   pop hl
   ld a,l
   ld (CALLS),a
   pop hl
   ld (CALLS+1),hl
   pop hl
   ld a,l
   pop bc
   pop de
   pop hl
   rst 30H
CALLS:   db 0
   dw 0
   call RESTREGS
   jp NEXT
;
CESCVRA:db 2,'V!'
   dw CCALSLT
   dw $+2
   exx
   pop hl
   pop de
   ld a,e
   call MSX_WRTVRAM
   jp RG
;
CLEVRAM:db 2,'V@'
   dw CESCVRA
   dw $+2
   exx
   pop hl
   call MSX_RDVRAM
   ld h,0
   ld l,a
   push hl
   jp RG
;
CLDIRVR:db 6,'LDIRVR'
   dw CLEVRAM
   dw $+2
   exx
   pop bc
   pop de
   pop hl
   call MSX_LDIRVR
   jp RG
;
CLDIRRV:db 6,'LDIRRV'
   dw CLDIRVR
   dw $+2
   exx
   pop bc
   pop de
   pop hl
   call MSX_LDIRRV
   jp RG
;
CVFILL:   db 5,'VFILL'
   dw CLDIRRV
   dw $+2
   exx
   pop hl
   ld a,l
   pop bc
   pop hl
   call MSX_VFILL
   jp RG
;
CSCREEN:db 6,'SCREEN'
   dw CVFILL
   dw $+2
   exx
   pop hl
   ld a,l
   ld (MSX_SCRMOD),a
   push af
   call MSX_CHGMOD
   ld hl,0101H
   ld (MSX_CSRY),hl
   pop af
   cp 2
   jp m,SCRN0
   ld a,(NCOLG)
   ld (MSX_LINLEN),a
   jp RG
;
SCRN0:   exx
   ld hl,(TABCAR)
   jp PUTT
;
CSCR:   db 3,'SCR'
   dw CSCREEN
   dw $+2
   pop de
   push bc
   ld a,e
   or d
   jr nz,SCRON
   call MSX_SCROFF
   pop bc
   jp NEXT
;
SCRON:   call MSX_SCRON
   pop bc
   jp NEXT
;
CESCVDP:db 4,'VDP!'
   dw CSCR
   dw $+2
   exx
   pop hl
   ld c,l
   pop hl
   ld b,l
   call MSX_WVDP
   jp RG
;
CLEVDP:   db 4,'VDP@'
   dw CESCVDP
   dw $+2
   pop de
   ld hl,MSX_RG0SAV
   add hl,de
   ld e,(hl)
   ld d,0
   jp NEXT
;
CINK:   db 3,'INK'
   dw CLEVDP
   dw $+2
   ld hl,MSX_FORCLR
NK:   pop de
   push bc
   ld a,e
   ld (hl),a
   call MSX_COLOR
   pop bc
   ld a,(MSX_FORCLR)
   ld (MSX_ATRBYT),a
   jp NEXT
;
CPAPER:   db 5,'PAPER'
   dw CINK
   dw $+2
   ld hl,MSX_BAKCLR
   jr NK
;
CBORDER:db 6,'BORDER'
   dw CPAPER
   dw $+2
   ld hl,MSX_BDRCLR
   jr NK
;
CESCTB:   db 5,'BASE!'
   dw CBORDER
   dw $+2
   pop hl
   add hl,hl
   ld de,MSX_TXTNAM
   add hl,de
   pop de
   ld (hl),e
   inc hl
   ld (hl),d
   jp NEXT
;
CLETAB:   db 5,'BASE@'
   dw CESCTB
   dw $+2
   pop hl
   add hl,hl
   ld de,MSX_TXTNAM
   add hl,de
   ld e,(hl)
   inc hl
   ld d,(hl)
   push de
   jp NEXT
;
CSETINK:db 6,'SETINK'
   dw CLETAB
   dw $+2
   pop hl
   ld a,l
   ld (MSX_ATRBYT),a
   jp NEXT
;
CPSET:   db 4,'PSET'
   dw CSETINK
PSET:   dw $+2
   exx
   pop hl
   ld (MSX_GRPACY),hl
   ex de,hl
   pop hl
   ld (MSX_GRPACX),hl
   ld c,l
   ld b,h
   call 010EH
   call 0111H
   call 0120H
   ld a,(MSX_FORCLR)
   ld (MSX_ATRBYT),a
   jp RG
;
CPRESET:db 6,'PRESET'
   dw CPSET
   dw $+2
   ld a,(MSX_BAKCLR)
   ld (MSX_ATRBYT),a
   jr PSET+2
;
CFOOT:   db 6,'FOOTER'
   dw CPRESET
   dw $+2
   exx
   pop hl
   ld a,l
   or h
   jr z,FTOFF
   call MSX_SHOWKEYS
   jp RG
;
FTOFF:   call MSX_HIDEKEYS
   jp RG
;
CLINE:   db 4,'LINE'
   dw CFOOT
   dw $+2
   ld hl,58FCH
   jr LBF
;
CFULL:   db 4,'FULL'
   dw CLINE
   dw $+2
   ld hl,58C1H
LBF:   ld (CLBF),hl
   ld (VAR1),bc
   pop hl
   ld (MSX_GYPOS),hl
   ld (MSX_GRPACY),hl
   pop hl
   ld (MSX_GXPOS),hl
   ld (MSX_GRPACX),hl
   pop de
   pop bc
   push ix
   push iy
   call LESLOT
   ld bc,(VAR1)
   pop iy
   pop ix
   jp NEXT
;
LESLOT:   rst 30H
   db 0
CLBF:   dw 0
   ret
;
CBOX:   db 3,'BOX'
   dw CFULL
   dw $+2
   ld hl,5912H
   jr LBF
;
CGRX:   db 3,'GRX'
   dw CBOX
   dw $+2
   ld hl,MSX_GRPACX
   jp HPUSH
;
CGRY:   db 3,'GRY'
   dw CGRX
   dw $+2
   ld hl,MSX_GRPACY
   jp HPUSH
;
CSTEP:   db 4,'STEP'
   dw CGRY
   dw $+2
   ld de,(MSX_GRPACX)
   ld hl,(MSX_GRPACY)
   jp DPUSH
;
CCLICK:   db 5,'CLICK'
   dw CSTEP
   dw $+2
   ld hl,MSX_CLIKSW
   jp HPUSH
;
CSOUND:   db 5,'SOUND'
   dw CCLICK
   dw $+2
   pop hl
   ld a,l
   out (160),a
   pop hl
   ld a,l
   out (161),a
   jp NEXT
;
CESCPSG:db 4,'PSG!'
   dw CSOUND
   dw $+2
   pop hl
   ld a,l
   pop de
   jp MSX_WRTPSG
;
CLEPSG:   db 4,'PSG@'
   dw CESCPSG
   dw $+2
   pop hl
   ld a,l
   call MSX_RDPSG
   ld l,a
   ld h,0
   jp HPUSH
;
CSTTPRT:db 8,'?PRINTER'
   dw CLEPSG
   dw $+2
   call MSX_RDPSG
   ld l,a
   ld h,0
   jp HPUSH
;
CSTICK:   db 5,'STICK'
   dw CSTTPRT
   dw $+2
   call SAVEREGS
   pop hl
   ld a,l
   call MSX_GTSTCK
   ld l,a
   ld h,0
   call RESTREGS
   jp HPUSH
;
CSTRIG:   db 5,'STRIG'
   dw CSTICK
   dw $+2
   call MSX_GTTRIG
   ld l,a
   ld h,a
   jp HPUSH
;
CTOUCHP:db 8,'TOUCHPAD'
   dw CSTRIG
   dw $+2
   call SAVEREGS
   pop hl
   ld a,l
   call MSX_GTPAD
   ld l,a
   ld h,0
   call RESTREGS
   jp HPUSH
;
CPADDLE:db 6,'PADDLE'
   dw CTOUCHP
   dw $+2
   call SAVEREGS
   pop hl
   ld a,l
   call MSX_GTPDL
   ld l,a
   ld h,0
   call RESTREGS
   jp HPUSH
;
CKEYBD: db 8,'KEYBOARD'
   dw CPADDLE
   dw $+2
   di
   exx
   pop bc
   ld b,c
   ld hl,(MSX_PUTPNT)
KEYBD1:   ld de,(MSX_GETPNT)
   push hl
   inc hl
   xor a
   sbc hl,de
   pop hl
   jr z,KEYBD3
   pop de
   ld a,e
   ld (hl),a
   inc hl
   push hl
   ld de,0FC18H
   xor a
   sbc hl,de
   pop hl
   jp m,KEYBD2
   ld hl,0FBF0H
KEYBD2:   djnz KEYBD1
   jr KEYBD4
KEYBD3:   pop de
   djnz KEYBD3
KEYBD4:   ld (MSX_PUTPNT),hl
   ei
   jp RG
;
CNEWCAR:db 6,'NEWCAR'
   dw CKEYBD
   dw $+2
   ld hl,0A000H
PUTTAB:   ld (TABCAR),hl
   ld a,(MSX_SCRMOD)
   cp 2
   jp p,NEXT
PUTT:   ld de,(MSX_TXTNAM+4)
   and a
   jr z,PUTT1
   ld de,(MSX_TXTNAM+14)
PUTT1:   push bc
   push ix
   push iy
   ld bc,2048  ; 256 CARACT.
   call MSX_LDIRRV
   pop iy
   pop ix
   pop bc
   jp NEXT
;
CNORML:   db 6,'NORMAL'
   dw CNEWCAR
   dw $+2
   ld hl,1BBFH
   jp PUTTAB
;
