;
CDDUP:   db 4,'2DUP'
   dw CVARIAB
DDUP:   dw $+2
   pop hl   ; MSB
   pop de   ; LSB
   push de   ; LSB
   push hl   ; MSB
   jp DPUSH
;
CDMENOR:db 2,'D<'
   dw CDDUP
DMENOR:   dw $+2
   ld (VAR3),ix
   ld ix,8
   add ix,sp
   ld sp,ix
   ld e,(ix-1)
   ld d,(ix-2)   ; LSB2
DMENOR3:ld l,(ix-5)
   ld h,(ix-6)   ; LSB1
DMENOR2:xor a
   sbc hl,de
   ld e,(ix-3)
   ld d,(ix-4)   ; LSB1
   ld l,(ix-7)
   ld h,(ix-8)   ; LSB2
   sbc hl,de
   ld ix,(VAR3)
   ld hl,0
   jp p,HPUSH
   dec hl
   jp HPUSH
;
CDMAIOR: db 2,'D>'
         dw CDMENOR
DMAIOR:  dw RUNF
         dw DSWAP,DMENOR,ENDF
;
CDIGU:   db 2,'D='
   dw CDMAIOR
DIGU:   dw $+2
   ld (VAR3),ix
   ld ix,8
   add ix,sp
   ld sp,ix
   ld e,(ix-1)
   ld d,(ix-2)   ; LSB2
   ld l,(ix-5)
   ld h,(ix-6)   ; LSB1
   xor a
   sbc hl,de
   ld d,(ix-3)
   ld e,(ix-4)   ; LSB1
   ld h,(ix-7)
   ld l,(ix-8)   ; LSB2
   sbc hl,de
   ld ix,(VAR3)
   ld hl,0
   jp nz,HPUSH
   dec hl
   jp HPUSH
;
CDDIF: db 3,'D<>'
       dw CDIGU
       dw RUNF
       dw DIGU,NOT,ENDF
;
CDMEN0:   db 3,'D0<'
   dw CDDIF
   dw $+2
   pop hl
   pop de
   bit 7,h
   ld hl,0
   jp z,HPUSH
   dec hl
   jp HPUSH
;
CDIGU0:   db 3,'D0='
   dw CDMEN0
DIGU0:   dw RUNF
       dw OR,IGU0,ENDF
;
CDMAI0:   db 3,'D0>'
   dw CDIGU0
DMAI0:   dw RUNF
       dw ZERO,ZERO,DMAIOR,ENDF
;
CDROT:   db 4,'2ROT'
   dw CDMAI0
DROT:   dw $+2
   push bc
   ld (VAR1),ix
   ld ix,12
   add ix,sp
   ld h,(ix-1)
   ld l,(ix-2)
   push hl
   ld h,(ix-3)
   ld l,(ix-4)
   push hl
   push ix
   push ix
   ld de,-5
   add ix,de
   push ix
   pop hl
   pop ix
   pop de
   ld bc,8
   ldir
   pop hl
   ld (ix-9),h
   ld (ix-10),l
   pop hl
   ld (ix-11),h
   ld (ix+12),l
   ld ix,(VAR1)
   pop bc
   jp NEXT
;
CDDROP:   db 5,'2DROP'
   dw CDROT
DDROP:   dw $+2
   pop hl
   pop hl
   jp NEXT
;
CDRAND:   db 5,'2RAND'
   dw CDDROP
   dw $+2
   push bc
   ld hl,(SEMT)
   ld de,(SEMT+2)
   ld b,8
DRND1:   ld a,l
   rra
   rra
   xor h
   rra
   rra
   rr h
   rr l
   ld a,e
   rra
   rra
   xor d
   rra
   rra
   rr d
   rr e
   djnz DRND1
   ld (SEMT),hl
   ld (SEMT+2),de
   pop bc
   jp DPUSH
;
CDROLL:   db 5,'2ROLL'
   dw CDRAND
   dw $+2
   exx
   ld (VAR1),ix
   pop ix
   add ix,ix
   add ix,ix
   push ix      ; TAM. DESL.
   add ix,sp
   dec ix
   push ix
   push ix
   ld b,(ix+0)   ; MSB do MSB
   ld c,(ix-1)   ; LSB do MSB
   ld h,(ix-2)   ; MSB do LSB
   ld l,(ix-3)   ; LSB do LSB
   ld (VAR2),bc
   ld (VAR3),hl
   pop de
   pop hl
   ld bc,4
   add hl,bc
   pop bc
   lddr
   ld bc,(VAR2)
   ld hl,(VAR3)
   ld (ix-9),b
   ld (ix-10),c
   ld (ix-11),h
   ld (ix-12),l
   ld ix,(VAR1)
   jp RG
;
CDSLA:   db 3,'D<<'
   dw CDROLL
   dw $+2
   exx
   pop bc
   pop hl
   pop de
   ld b,c
DSLA1:   sla e
   rl d
   rl l
   rl h
   djnz DSLA1
   push de
   push hl
   exx
   jp NEXT
;
CDSRA:   db 3,'D>>'
   dw CDSLA
   dw $+2
   exx
   pop bc
   pop hl
   pop de
   ld b,c
DSRA1:   srl h
   rr l
   rr d
   rr e
   djnz DSRA1
   push de
   push hl
   exx
   jp NEXT
;
DB_LOOP:dw $+2
   pop hl
   ld (ix-8),l
   ld (ix-7),h
   pop hl
   ld (ix-6),l
   ld (ix-5),h
   pop hl
   ld (ix-4),l
   ld (ix-3),h
   pop hl
   ld (ix-2),l
   ld (ix-1),h
   ld de,-8
   add ix,de
   jp NEXT
;
DLEAVE:   dw $+2
   ld a,(ix+0)
   ld (ix+4),a
   ld a,(ix+1)
   ld (ix+5),a
   ld a,(ix+2)
   ld (ix+6),a
   ld a,(ix+3)
   ld (ix+7),a
   jp NEXT
;
DS_LOOP:dw $+2
   pop hl
   pop de
   jr DLOOP1
;
DLOOP:   dw $+2
   ld hl,0
   ld de,1
DLOOP1:   push bc
   push hl
   rl h
   ex af,af'
   ld l,(ix+2)
   ld h,(ix+3)
   add hl,de
   ld (ix+2),l
   ld (ix+3),h
   ex de,hl
   pop hl
   push de
   ld e,(ix+0)
   ld d,(ix+1)
   adc hl,de
   ld (ix+0),l
   ld (ix+1),h
   ld b,h
   ld c,l
   pop de
   ld l,(ix+6)
   ld h,(ix+7)
   ex af,af'
   jr c,DLOOP3
   xor a
   ex de,hl
   sbc hl,de
   ld l,(ix+4)
   ld h,(ix+5)
   push bc
   push hl
   pop bc
   pop hl
   sbc hl,bc
   jr DLOOP4
DLOOP3:   xor a
   sbc hl,de
   ld l,(ix+4)
   ld h,(ix+5)
   sbc hl,bc
DLOOP4:   pop bc
   jp m,BRCH+2
   ld de,8
   add ix,de
   inc bc
   inc bc
   jp NEXT
;
CPOK32:   db 2,'2!'
   dw CDSRA
POK32:   dw $+2
   ld (VAR1),ix
   pop ix
   pop hl      ; MSB
   pop de      ; LSB
   ld (ix+0),l
   ld (ix+1),h
   ld (ix+2),e
   ld (ix+3),d
   ld ix,(VAR1)
   jp NEXT
;
CPEK32:   db 2,'2@'
   dw CPOK32
PEK32:   dw $+2
   pop hl
   ld e,(hl)
   inc hl
   ld d,(hl)
   inc hl
   push de
   ld e,(hl)
   inc hl
   ld d,(hl)
   ex de,hl
   ex (sp),hl
   jp HPUSH
;
CDINRP:   db 3,'D>R'
   dw CPEK32
DINRP:   dw $+2
   pop hl      ; MSB
   pop de      ; LSB
   dec ix
   ld (ix+0),e
   dec ix
   ld (ix+0),d
   dec ix
   ld (ix+0),h
   dec ix
   ld (ix+0),l
   jp NEXT
;
CDOUTRP:db 3,'DR>'
   dw CDINRP
DOUTRP:   dw $+2
   ld l,(ix+0)   ; LSB
   inc ix
   ld h,(ix+0)
   inc ix
   ld e,(ix+0)   ; MSB
   inc ix
   ld d,(ix+0)
   inc ix
   jp DPUSH
;
CDLERP:   db 2,'2R'
   dw CDOUTRP
DLERP:   dw $+2
   ld l,(ix+0)
   ld h,(ix+1)
   ld e,(ix+2)
   ld d,(ix+3)
   jp DPUSH
;
CCNT32:   db 2,'2I'
   dw CDLERP
   dw $+2
   ld l,(ix+0)
   ld h,(ix+1)
   ld e,(ix+2)
   ld d,(ix+3)
   jp DPUSH
;
CDRESET:db 5,'D0SET'
   dw CCNT32
DRESET:   dw $+2
   pop hl
   ld (hl),0
   inc hl
   ld (hl),0
   inc hl
   ld (hl),0
   inc hl
   ld (hl),0
   jp NEXT
;
CDSET:   db 5,'D1SET'
   dw CDRESET
DSET:   dw $+2
   pop hl
   ld (hl),-1
   inc hl
   ld (hl),-1
   inc hl
   ld (hl),-1
   inc hl
   ld (hl),-1
   jp NEXT
;
CDVEZES:db 2,'D*'
   dw CDSET
DVEZES:   dw $+2
   pop de
   ld a,e
   pop hl
   ld (VAR2),hl
   pop hl
   push bc
   ld de,0
   ld (VAR1),de
DVEZ1:   srl a
   jr nc,DVEZ2
   push hl
   add hl,de
   ex de,hl
   ld bc,(VAR1)
   ld hl,(VAR2)
   adc hl,bc
   ld (VAR1),hl
   pop hl
DVEZ2:   and a
   jr z,DVEZ3
   add hl,hl
   push hl
   ld hl,(VAR2)
   adc hl,hl
   ld (VAR2),hl
   pop hl
   jr DVEZ1
DVEZ3:   ld hl,(VAR1)
   pop bc
   jp DPUSH
;
CDMAIS:   db 2,'D+'
   dw CDVEZES
DMAIS:   dw $+2
   ld hl,6
   add hl,sp
   ld e,(hl)
   ld (hl),c
   inc hl
   ld d,(hl)
   ld (hl),b
   pop bc
   pop hl
   add hl,de
   ex de,hl
   pop hl
   ld a,l
   adc a,c
   ld l,a
   ld a,h
   adc a,b
   ld h,a
   pop bc
   jp DPUSH
;
CDMENOS:db 2,'D-'
   dw CDMAIS
DMENOS:   dw $+2
   ld hl,6
   add hl,sp
   ld e,(hl)
   ld (hl),c
   inc hl
   ld d,(hl)
   ld (hl),b
   pop bc
   pop hl
   ex de,hl
   xor a
   sbc hl,de
   ex de,hl
   pop hl
   ld a,l
   sbc a,c
   ld l,a
   ld a,h
   sbc a,b
   ld h,a
   pop bc
   jp DPUSH
;
CDJ:   db 2,'2J'
   dw CDMENOS
   dw $+2
   ld e,(ix+8)
   ld d,(ix+9)
   ld l,(ix+10)
   ld h,(ix+11)
   jp DPUSH
;
CDPICK:   db 5,'2PICK'
   dw CDJ
   dw RUNF
       dw MENOS1,PUSHN,4,VEZES
   dw MAISP,PEK32,ENDF
;
CDSWAP:   db 5,'2SWAP'
   dw CDPICK
DSWAP:   dw $+2
   pop hl   ; MSB1
   pop de   ; LSB1
   exx
   pop hl   ; MSB2
   pop de   ; LSB2
   exx
   push de   ; LSB1
   push hl   ; MSB1
   exx
   push de   ; LSB2
   push hl ; MSB2
   jp RG
;
CDSOMEM:db 3,'D+!'
   dw CDSWAP
DSOMEM:   dw $+2
   pop hl
   pop de
   ex (sp),hl
   ld a,(hl)
   add a,e
   ld (hl),a
   inc hl
   ld a,(hl)
   adc a,d
   ld (hl),a
   inc hl
   pop de
   ld a,(hl)
   adc a,e
   ld (hl),a
   inc hl
   ld a,(hl)
   adc a,d
   ld (hl),a
   jp NEXT
;
CDPASSO:db 6,'+2LOOP'
   dw CCODI
   dw RUNF
       dw PUSHN,DS_LOOP,MARK_E,ENDF
;
CDLEAVE:db 6,'2LEAVE'
   dw CDPASSO
   dw RUNF
       dw PUSHN,DLEAVE,POKD16,ENDF
;
CDDO:   db 3,'2DO'
   dw CDLEAVE
   dw RUNF
       dw PUSHN,DB_LOOP,MARK_S,ENDF
;
CDLOOP:   db 5,'2LOOP'
   dw CDDO
   dw RUNF
       dw PUSHN,DLOOP,MARK_E,ENDF
;
CDOVER:   db 5,'2OVER'
   dw CDSOMEM
DOVER:   dw $+2
   pop hl
   pop de
   push de
   ex de,hl
   jp DPUSH
;
CDCONST:db 9,'2CONSTANT'
   dw CDOVER
DCONST:   dw RUNF
       dw CREATE,POKD32,SCODE
   ex de,hl
   ld de,3
   add hl,de
   ld d,(hl)
   dec hl
   ld e,(hl)
   dec hl
   push de
   ld d,(hl)
   dec hl
   ld e,(hl)
   push de
   jp NEXT
;
CDVAR:   db 4,'2VAR'
   dw CDCONST
DVAR:   dw RUNF
       dw DCONST,SCODE
   push de
   jp NEXT
;
CDVARIAB:db 9,'2VARIABLE'
   dw CDVAR
DVARIAB:dw RUNF
       dw ZERO,ZERO,DVAR,ENDF
;
CDDIV:   db 2,'D/'
   dw CDVARIAB
DDIV:   dw RUNF
       dw DMOD,DDROP,ENDF
;
