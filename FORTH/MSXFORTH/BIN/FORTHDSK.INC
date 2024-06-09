;
CFCBPS: db 5,'(FCB)'
        dw CTAPOOF
FCBPS:  dw $+2
        ld hl,(FCB)
        jp HPUSH
;
CFCB: db 3,'FCB'
      dw CFCBPS
      dw $+2
      ld hl,FCB
      jp HPUSH
;
CDTA: db 3,'DTA'
      dw CFCB
DTA:  dw $+2
      ld hl,(FCB)
      ld de,40
      add hl,de
      jp HPUSH
;
CDRVA: db 2,'A:'
       dw CDTA
       dw RUNF
       dw PUSHN,14,ZERO,DIOS,DROP,ENDF
;
CDRVB: db 2,'B:'
       dw CDRVA
       dw RUNF
       dw PUSHN,14,ONE,DIOS,DROP,ENDF
;
CFMASK: db 8,'FILEMASK'
        dw CDRVB
FMASK:  dw $+2
        ld hl,(FCB)
        push bc
        push hl
        xor a
        ld (hl),a
        push hl
        pop de
        inc de
        ld bc,167
        ldir   ; LIMPA FCB
        pop hl
        pop bc
        pop de
        push bc
        inc de
        ld a,(de)
        and a
        jr nz,FLNMA
        inc hl
        ld a,'?'
        ld (hl),a
        push hl
        pop de
        inc de
        ld bc,10
        ldir
        jp FLNM1+1

FLNMA:  dec de
        ld a,(de)
        push af
        ld b,a
        ld c,0
FLNMX:  inc de
        ld a,(de)
        cp 32
        jr nz,FLNMX1
        dec b
        jr FLNMX

FLNMX1: push af
        push de
        inc de
        ld a,(de)
        pop de
        dec de
        cp ":"
        jr nz,FLNMY
        inc de
        inc de
        pop af
        cp 'A'
        jp m,ERRNM3
        cp 'E'
        jp p,FLNMN
        sub 40H
        jr FLNMM
FLNMN:  cp 'a'
        jp m,ERRNM3
        cp 'e'
        jp p,ERRNM3
        sub 60H
FLNMM:  ld (hl),a
        dec b
        djnz FLNM
        inc hl
        ld a,'?'
        ld (hl),a
        push hl
        pop de
        inc de
        ld bc,10
        ldir
        jr FLNM1

FLNM:   push af
FLNMY:  pop af
FLNMZ:  inc hl
        inc de
        ld a,(de)
        cp '.'
        jr nz,FLNM2
        ld a,32
        ld (FLL+1),a
        call FLL
        jr EXT

FLNM2: cp '*'
       jr nz,FLNM3
       ld a,'?'
       ld (FLL+1),a
       call FLL
FLNM4: dec b
       inc de
       ld a,(de)
       cp '.'
       jr z,EXT
       inc c
       ld a,c
       cp 12
       jp m,FLNM4
       ld b,3
       ld a,32
FLNM5: ld (hl),a
       inc hl
       djnz FLNM5
FLNM1: pop af
       pop bc
       ld hl,0
       jp HPUSH

FLNM3: call VERNOM
       ld (hl),a
       inc c
       ld a,c
       cp 12
       jp p,FLNM1
       djnz FLNMZ
       ld a,11
       sub c
       ld b,a
       inc hl
       jr FLNM5-2
;
EXT:   pop af
       push af
       cp b
       jr z,ERRNM1
       ld a,c
       cp 10
       jp p,ERRNM1
       inc de
       dec b
       ld c,0
EXT1:  ld a,(de)
       cp '*'
       jr nz,EXT2
       ld a,5
       add a,c
       ld c,a
       ld a,'?'
       ld (FLL+1),a
       call FLL
       jp FLNM1
EXT2:  call VERNOM
       ld (hl),a
       inc hl
       inc de
       inc c
       ld a,c
       cp 4
       jp p,FLNM1
       djnz EXT1
       ld a,5
       add a,c
       ld c,a
       cp 8
       ld a,32
       ld (FLL+1),a
       call m,FLL
       jp FLNM1
;
VERNOM: cp 33
        jp m,ERRNOM
        push hl
        push bc
        ld hl,TABERRN
        ld bc,ERRNOM-TABERRN
        cpir
        pop bc
        pop hl
        jr z,ERRNOM
        ret
;
TABERRN: db '"+,/:;<=>[\]'
;
ERRNOM: pop af
ERRNM1: pop af
ERRNM2: pop bc
        ld hl,-1
        jp HPUSH
ERRNM3: pop af
        pop bc
        ld hl,1
        jp HPUSH
;
FLL: ld a,0
     ld (hl),a
     inc hl
     inc c
     ld a,c
     cp 8
     jp m,FLL
     ret
;
CBDOS: db 4,'BDOS'
       dw CFMASK
BDOS:  dw $+2
       ld (PF),bc
       ld (PC),ix
       ld (VAR3),iy
       pop de   ;PEGA de
       pop bc   ;PEGA bc
       pop hl   ;PEGA Acc
       ld a,l
       ld hl,BDS1
       push hl
       ld hl,(BDS)
       jp (hl)
BDS1:  ld iy,(VAR3)
       ld ix,(PC)
       ld bc,(PF)
       ld l,a
       ld h,0
       jp HPUSH
;
CDIOS: db 4,'DIOS'
       dw CBDOS
DIOS:  dw $+2
       pop de
       pop hl
       push hl
       push hl
       push de
       jr BDOS+2
;
CERRDSK: db 6,'ERRDSK'
         dw CDIOS
ERRDSK:  dw RUNF
         dw DUP,ZERO,IGU,BRCH0,ERRD0
         dw BRCH,ERRFIM+4
ERRD0:   dw DUP,ONE,IGU,BRCH0,ERRD1,DISP
         db 10,'N',0B0H,'O ACHADO'
         dw BRCH,ERRFIM
ERRD1:   dw DUP,TWO,IGU,BRCH0,ERRD2,DISP
         db 14,'DRIVE INV',84H,'LIDO'
         dw BRCH,ERRFIM
ERRD2:   dw DUP,THREE,IGU,BRCH0,ERRD3,DISP
         db 24,'NOME DE ARQUIVO INV',84H,'LIDO'
         dw BRCH,ERRFIM
ERRD3:   dw DUP,PUSHN,4,IGU,BRCH0,ERRD4,DISP
         db 11,'DISCO CHEIO'
         dw BRCH,ERRFIM
ERRD4:   dw DUP,PUSHN,5,IGU,BRCH0,ERRD5,DISP
         db 15,'DIRET',8AH,'RIO CHEIO'
         dw BRCH,ERRFIM
ERRD5:   dw DISP
         db 29,'ERRO DE DISCO INDETERMINADO ('
         dw DUP,IMPSS,PUSHN,')',EMIT
ERRFIM:  dw CR,DROP,ENDF
;
CFILES: db 5,'FILES'
        dw CERRDSK
        dw RUNF
        dw LNCOND,BLANK
        dw WORD,HERE,FMASK,DUP,IGU0
        dw BRCH0,FILES1,DROP,PUSHN,MSX_LINLEN
        dw PEK8,PUSHN,13,DVMOD,MENOS1,PUSHN
        dw VAR1,POK16,PUSHN,VAR2,POK16
        dw PUSHN,26,DTA,DIOS,PUSHN,17
        dw FCBPS,BDOS,DUP,IGU0,BRCH0
        dw FILES2,TRUE,PUSHN,NL,POK16
FILES3: dw IGU0,BRCH0,FILES4,PUSHN,NL,PEK16
        dw MAIS1,DUP,PUSHN,NL,POK16,PUSHN
        dw VAR1,PEK16,MAIOR,BRCH0,FILES5
        dw PUSHN,VAR2,PEK16,MAI0,BRCH0
        dw FILES7,CR
FILES7: dw PUSHN,NL,RESET
FILES5: dw DTA,DUP,MAIS1,PUSHN,8,TYPE
        dw PUSHN,'.',EMIT,PUSHN,9,MAIS
        dw PUSHN,3,TYPE,SPACE,PUSHN
        dw 18,FCBPS,DIOS,BRCH,FILES3
FILES2: dw ONE,ERRDSK,DROP,ENDF
FILES1: dw ONE,IGU,BRCH0,FILES8,TWO
        dw ERRDSK,ENDF
FILES8: dw THREE,ERRDSK
FILES4: dw CR,ENDF
;
CKILL: db 4,'KILL'
       dw CFILES
       dw RUNF
       dw LNCOND,BLANK,WORD,HERE
       dw FMASK,DUP,DUP,IGU0,BRCH0
       dw KILL1,DROP,FCBPS,MAIS1,PUSHN
       dw 11,ZERO,B_LOOP
KILL2: dw PE8I,PUSHN,'?',IGU,BRCH0,KILL7
       dw LOOP,KILL2,DISP
       db 20,0DH,0AH,'APAGA TUDO (S/N)? '
KILL4: dw KEY,DUP,DUP,PUSHN,0DFH,AND
       dw DUP,DUP,PUSHN,'N',IGU,SWAP
       dw PUSHN,'S',IGU,OR,BRCH0,KILL4
       dw SWAP,EMIT,PUSHN,'S',IGU,BRCH0
       dw KILL5,BRCH,KILL3
KILL7: dw OUTRP,OUTRP,DROP,DROP
KILL3: dw PUSHN,19,FCBPS,DIOS,BRCH0
       dw KILL5,ONE,ERRDSK,ENDF
KILL1: dw ONE,IGU,BRCH0,KILL6,TWO
       dw ERRDSK,ENDF
KILL6: dw THREE,ERRDSK
KILL5: dw ENDF
;
