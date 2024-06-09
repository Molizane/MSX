;
CMOTOR: db 5,'MOTOR'
   dw CASS
   dw $+2
   pop hl
   ld a,l
   call 0F3H
   jp NEXT
;
CTAPION:db 6,'STAPE>'
   dw CMOTOR
TAPION:   dw $+2
   call SAVEREGS
   call 00E1H
   call RESTREGS
   ld hl,-1
   jp c,HPUSH
   dec hl
   jp HPUSH
;
CTAPIN:   db 5,'TAPE>'
   dw CTAPION
TAPIN:   dw $+2
   call SAVEREGS
   pop hl      ; END.
   pop de      ; TAM.
TAPIN0:   push de
   push hl
   call 00E4H
   pop hl
   pop de
   jr c,TAPIN1
   ld (hl),a
   inc hl
   dec de
   ld a,e
   or d
   jr nz,TAPIN0
   xor a
TAPIN1:   call RESTREGS
   ld hl,-1
   jp c,HPUSH
   inc hl
   jp HPUSH
;
CTAPIOF:db 6,'ETAPE>'
   dw CTAPIN
TAPIOF:   dw $+2
   call 00E7H
   jp NEXT
;
CTAPOON:db 6,'>STAPE'
   dw CTAPIOF
TAPOON:   dw $+2
   call SAVEREGS
   pop hl
   ld a,l
   call 0EAH
   call RESTREGS
   ld hl,-1
   jp c,HPUSH
   inc hl
   jp HPUSH
;
CTAPON:   db 5,'>TAPE'
   dw CTAPOON
TAPON:   dw $+2
   call SAVEREGS
   pop hl      ; END.
   pop de      ; TAM.
TAPON0:   push de
   push hl
   ld a,(hl)
   call 00EDH
   pop hl
   pop de
   jr c,TAPON1
   inc hl
   dec de
   ld a,e
   or d
   jr nz,TAPON0
   xor a
TAPON1:   call RESTREGS
   ld hl,-1
   jp c,HPUSH
   inc hl
   jp HPUSH
;
CTAPOOF:db 6,'>ETAPE'
   dw CTAPON
TAPOOF:   dw $+2
   call 00F0H
   jp NEXT
;
