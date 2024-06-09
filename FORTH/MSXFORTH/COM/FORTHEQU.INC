;
MSX_ROM_BDOS_VECTOR equ 0F37EH
MSX_BIOS            equ 0F37DH
;
; SUBROUTINES FOR READ/WRITE CALLS OF THE INTER-SLOT
;
MSX_RDPRIM  equ 0F380H ; Read from basic slot, used by RDSLT (0Ch) BIOS routine
MSX_WRPRIM  equ 0F385H ; Write to basic slot, used by WRSLT (14h) BIOS routine
MSX_CLPRIM  equ 0F38CH ; Call basic slot, used by CALSLT (1Ch) BIOS routine
MSX_USR0TAB equ 0F39AH ; USR function starting USR(0)
MSX_USR1TAB equ 0F39CH ; USR function starting USR(1)
MSX_USR2TAB equ 0F39EH ; USR function starting USR(2)
MSX_USR3TAB equ 0F3A0H ; USR function starting USR(3)
MSX_USR4TAB equ 0F3A2H ; USR function starting USR(4)
MSX_USR5TAB equ 0F3A4H ; USR function starting USR(5)
MSX_USR6TAB equ 0F3A6H ; USR function starting USR(6)
MSX_USR7TAB equ 0F3A8H ; USR function starting USR(7)
MSX_USR8TAB equ 0F3AAH ; USR function starting USR(8)
MSX_USR9TAB equ 0F3ACH ; USR function starting USR(9)
MSX_LINL40  equ 0F3AEH ; Screen width per line in SCREEN 0 (Default 39)
MSX_LINL32  equ 0F3AFH ; Screen width per line in SCREEN 1 (Default 29)
MSX_LINLEN  equ 0F3B0H ; Current screen width per line
MSX_CRTCNT  equ 0F3B1H ; Number of lines of current screen (default 24)
MSX_CLMLST  equ 0F3B2H ; Horizontal location in the case that items are divided by commas in PRINT statement

; WORK FOR INITIALIZATION

; SCREEN 0
MSX_TXTNAM equ 0F3B3H ; Pattern name table
MSX_TXTCOL equ 0F3B5H ; Color table
MSX_TXTCGP equ 0F3B7H ; Pattern ganarator table
MSX_TXTATR equ 0F3B9H ; Unused
MSX_TXTPAT equ 0F3BBH ; Unused

; SCREEN 1
MSX_T32NAM equ 0F3BDH ; Pattern name tabte
MSX_T32COL equ 0F3BFH ; Color table
MSX_T32CGP equ 0F3C1H ; Pattern ganarator table
MSX_T32ATR equ 0F3C3H ; Sprite attribute table
MSX_T32PAT equ 0F3C5H ; Sprite generator table

; SCREEN 2
MSX_GRPNAM equ 0F3C7H ; Pattern name tabte
MSX_GRPCOL equ 0F3C9H ; Color table
MSX_GRPCGP equ 0F3CBH ; Pattern ganarator table
MSX_GRPATR equ 0F3CDH ; Sprite attribute table
MSX_GRPPAT equ 0F3CFH ; Sprite generator table

; SCREEN 3
MSX_MLTNAM equ 0F3D1H ; Pattern name tabte
MSX_MLTCOL equ 0F3D3H ; Color table
MSX_MLTCGP equ 0F3D5H ; Pattern ganarator table
MSX_MLTATR equ 0F3D7H ; Sprite attribute table
MSX_MLTPAT equ 0F3D9H ; Sprite generator table
MSX_CLIKSW equ 0F3DBH ; Key click switch 0 = Disabled / 1 = Enabled
MSX_CSRY   equ 0F3DCH ; Y-coordinate of text cursor
MSX_CSRX   equ 0F3DDH ; X-coordinate of text cursor
MSX_CNSDFG equ 0F3DEH ; Functon key display switch 0 = NOT Visible / 1 = Visible

; AREA TO SAVE VDP REGISTERS

MSX_RG0SAV equ 0F3DFH ; Content of VDP(0) register (R#0)
MSX_RG1SAV equ 0F3E0H ; Content of VDP(1) register (R#1)
MSX_RG2SAV equ 0F3E1H ; Content of VDP(2) register (R#2)
MSX_RG3SAV equ 0F3E2H ; Content of VDP(3) register (R#3)
MSX_RG4SAV equ 0F3E3H ; Content of VDP(4) register (R#4)
MSX_RG5SAV equ 0F3E4H ; Content of VDP(5) register (R#5)
MSX_RG6SAV equ 0F3E5H ; Content of VDP(6) register (R#6)
MSX_RG7SAV equ 0F3E6H ; Content of VDP(7) register (R#7)
MSX_STATFL equ 0F3E7H ; Content of VDP(8) register (MSX2- VDP status register 0  S#0)
MSX_TRGFLG equ 0F3E8H ; Stores trigger button status of joystick

; Information about trigger buttons and space bar state
; 7 6 5 4 3 2 1 0
; | | | |       +-- Space bar, trig(0) (0 = pressed)
; | | | +---------- Stick 1, Trigger 1 (0 = pressed)
; | | +------------ Stick 1, Trigger 2 (0 = pressed)
; | +-------------- Stick 2, Trigger 1 (0 = pressed)
; +---------------- Stick 2, Trigger 2 (0 = pressed)

MSX_FORCLR equ 0F3E9H ; Foreground colour
MSX_BAKCLR equ 0F3EAH ; Background colour
MSX_BDRCLR equ 0F3EBH ; Border colour
MSX_MAXUPD equ 0F3ECH ; JMP 0000 (used by CIRCLE statement)
MSX_MINUPD equ 0F3EFH ; JMP 0000 (used by CIRCLE statement)
MSX_ATRBYT equ 0F3F2H ; Color code in csing graphic

; WORK AREA FOR PLAY STATEMENT

MSX_QUEUES equ 0F3F3H ; Points to queue table at the execution of PLAY st.
MSX_FRCNEW equ 0F3F5H ; DB 255

; WORK AREA FOR KEY INPUT

MSX_SCNCNT equ 0F3F6H ; Interval for the key scan
MSX_REPCNT equ 0F3F7H ; Delay until the auto-repeat of the key begins
MSX_PUTPNT equ 0F3F8H ; DW KEYBUF points to adress to write in the key buffer
MSX_GETPNT equ 0F3FAH ; DW KEYBUF points to adress to read from the key buffer

; PARAMETERS FOR CASSETTE

MSX_CS120_12  equ 0F3FCH ; DB LOW01,HIGH01,LOW11,HIGH11,HEDLEN*2/256 ; FOR 1200 BAUD
MSX_CS120_24  equ 0F401H ; DB LOW02,HIGH02,LOW12,HIGH22,HEDLEN*2/256 ; FOR 2400 BAUD
MSX_LOW       equ 0F406H ; DB LOW01,HIGH01    Width of LOW & HIGH wich represents bit 0
MSX_HIGH      equ 0F408H ; DB LOW11,HIGH11    Width of LOW & HIGH wich represents bit 1
MSX_HEADER    equ 0F40AH ; DB HEDLEN*2/256    Header bit for the short header
MSX_ASPCT1    equ 0F40BH ; 256/aspect ratio for BASIC Circle command
MSX_ASPCT2    equ 0F40DH ; 256*aspect ratio for BASIC Circle command
MSX_ENDPGM    equ 0F40FH ; DB ":" Dummy program end for RESUME NEXT st.

; WORK USED BY BASIC INTERNALLY

MSX_ERRFLG equ 0F414H ; BASIC Error number
MSX_LPTPOS equ 0F415H ; Position of printer head
MSX_PRTFLG equ 0F416H ; Flag whether to send to printer 0 = Print to Screen / 1 = Print to printer
MSX_NTMSXP equ 0F417H ; = 0 If MSX printer (This converts TAB's and unknown characters to spaces)
MSX_RAWPRT equ 0F418H ; <>0 If printing is in 'RAW MODE'
MSX_VLZADR equ 0F419H ; ADDRESS OF CHARACTER REPLACED BY VAL
MSX_VLZDAT equ 0F41BH ; CHARACTER REPLACED WITH 0 BY VAL
MSX_CURLIN equ 0F41CH ; Current execution line number of BASIC
MSX_KBFMIN equ 0F41EH ; Same as  ENDPRG, used if direct statement error occures
MSX_KBUF   equ 0F41FH ; Crunch buffer; translated into intermediate language from BUF
MSX_BUFMIN equ 0F55DH ; used by INPUT routine
MSX_BUF    equ 0F55EH ; Buffer to store characters typed( in ASCII code)

MSX_SX_L    equ 0F562H ; VDP R# 32, Source X Low
MSX_SX_H    equ 0F563H ; VDP R# 33, Source X High
MSX_SY_L    equ 0F564H ; VDP R# 34, Source Y Low
MSX_SY_H    equ 0F565H ; VDP R# 35, Source Y High
MSX_DX_L    equ 0F566H ; VDP R# 36, Dest. X Low
MSX_DX_H    equ 0F567H ; VDP R# 37, Dest. X High
MSX_DY_L    equ 0F568H ; VDP R# 38, Dest. Y Low
MSX_DY_H    equ 0F569H ; VDP R# 39, Dest. Y High
MSX_NX_L    equ 0F56AH ; VDP R# 40, Nr of dots X Low
MSX_NX_H    equ 0F56BH ; VDP R# 41, Nr of dots X High
MSX_NY_L    equ 0F56CH ; VDP R# 42, Nr of dots Y Low
MSX_NY_H    equ 0F56DH ; VDP R# 43, Nr of dots Y High
MSX_CDUMMY  equ 0F56EH ; VDP R# 44, Color register
MSX_VDP_ARG equ 0F56FH ; VDP R# 45, Argument register
MSX_L_OP    equ 0F570H ; VDP R# 46, Command  register

; The above Bit-blitten addresses are used by the COPY command in Basic.
; The VDP is allso able to communicate with the DISKROM to
; save or load images from or to VRAM.
; A 2Byte filename pointer is expected in SX for Loading and DX for Writing operation.
; i.e. FNAAM: DEFB 34,"d:filename.ext",34,0
; See SUB-ROM / EXT-ROM  (BIT-BLIT routines)
; L_OP has 10 different operators:
; 0 -  PSET       1 -  AND
; 2 -  OR         3 -  XOR
; 4 -  PRESET     8 -  TPSET
; 9 -  TAND       10 - TOR
; 11 - TXOR       12 - TPRESET

MSX_ENDBUF   equ 0F660H ; Preventoverflow of BUF
MSX_TTYPOS   equ 0F661H ; Virtual cursor location internally retained by BASIC
MSX_DIMFLG   equ 0F662H ; ARRAY FLAG
MSX_VALTYP   equ 0F663H ; Contains the code of the type of variable that is currently in DAC

; 2 = Integer
; 3 = String
; 4 = Single Precision
; 5 = Double Precision

MSX_DORES    equ 0F664H ; Indicates whether stored word can be crunched
MSX_DONUM    equ 0F665H ; flag for crunch
MSX_CONTXT   equ 0F666H ; Text address used by CNRGET
MSX_CONSAV   equ 0F668H ; Store token of constant after calling CHRGET
MSX_CONTYP   equ 0F669H ; Type of stored constant
MSX_CONLO    equ 0F66AH ; Valu of stored constant
MSX_MEMSIZ   equ 0F672H ; HIGHEST LOCATION IN MEMORY USED BY BASIC
MSX_STKTOP   equ 0F674H ; TOP LOCATION TO BE USED FOR THE STACK
MSX_TXTTAB   equ 0F676H ; Starting address of BASIC text area
MSX_TEMPPT   equ 0F678H ; Starting address of unused area of temporary descriptor
MSX_TEMPST   equ 0F67AH ; Temporary descriptors
MSX_DSCTMP   equ 0F698H ; String descriptor wich is the result of string fun.
MSX_FRETOP   equ 0F69BH ; Starting address of unused area of string area
MSX_TEMP3    equ 0F69DH ; Used for garbage collection or by USR function
MSX_TEMP8    equ 0F69FH ; Used for garbage collection
MSX_ENDFOR   equ 0F6A1H ; Next address of FOR st.
MSX_DATLIN   equ 0F6A3H ; Line number of DATA st.read by READ st.
MSX_SUBFLG   equ 0F6A5H ; Flag for array for USR fun.
MSX_FLGINP   equ 0F6A6H ; Flag for INPUT or READ
MSX_TEMP     equ 0F6A7H ; Location for temporary reservation for st.code
MSX_PTRFLG   equ 0F6A9H ; LINE NUMBER CONVERTED TO POINTERS ( 00 = NO / 0D = Yes )
MSX_AUTFLG   equ 0F6AAH ; AUTO MODE FLAG ( 00 = Yes / 01 = No )
MSX_AUTLIN   equ 0F6ABH ; Current line number for auto
MSX_AUTINC   equ 0F6ADH ; Increment for auto
MSX_SAVTXT   equ 0F6AFH ; Text pointer for resume
MSX_SAVSTK   equ 0F6B1H ; Save stack when error occurs
MSX_ERRLIN   equ 0F6B3H ; Line where last error
MSX_DOT      equ 0F6B5H ; CURRENT LINE for edit & list
MSX_ERRTXT   equ 0F6B7H ; Text pointer for use by RESUME
MSX_ONELIN   equ 0F6B9H ; LINE to go when error
MSX_ONEFLG   equ 0F6BBH ; =1 if executing an error trap routine
MSX_TEMP2    equ 0F6BCH ;
MSX_OLDLIN   equ 0F6BEH ; OLD LINE NUMBER set up ^C ...
MSX_OLDTXT   equ 0F6C0H ; Points st. to be executed next
MSX_VARTAB   equ 0F6C2H ; Pointer to start of variable space
MSX_ARYTAB   equ 0F6C4H ; Pointer to begging of array table
MSX_STREND   equ 0F6C6H ; End of storage in use
MSX_DATPTR   equ 0F6C8H ; DATA pointer
MSX_DEFTBL   equ 0F6CAH ; Default valtype for each letter

; WORK FOR USER FUNCTION PARAMETER

MSX_PRMSTK   equ 0F6E4H ; Previous definition block on stack
MSX_PRMLEN   equ 0F6E6H ; Number of bytes of objective table
MSX_PARM1    equ 0F6E8H ; Objective prameter definition table
MSX_PRMPRV   equ 0F74CH ; Pointer to previous parameter block
MSX_PRMLN2   equ 0F74EH ; Size of parameter block
MSX_PARM2    equ 0F750H ; For parameter storage
MSX_PRMFLG   equ 0F7B4H ; Flag to indicate whether PARM1 was searching
MSX_ARYTA2   equ 0F7B5H ; End point of search
MSX_NOFUNS   equ 0F7B7H ; 0 if no function active
MSX_TEMP9    equ 0F7B8H ; Location of temporary storage for garbage collection
MSX_FUNACT   equ 0F7BAH ; Count of active functions
MSX_SWPTMP   equ 0F7BCH ; Value of first  variable in SWAP st.
MSX_TRCFLG   equ 0F7C4H ; 0 MEANS NO TRACE

; WORK FOR MATH-PACK

MSX_FBUFFR   equ 0F7C5H ; Buffer for fout
MSX_DECTMP   equ 0F7F0H ; Used to transform decimal integer to floating point number
MSX_DECTM2   equ 0F7F2H ; Used at division routine execution
MSX_DECCNT   equ 0F7F4H ; Used at division routine execution
MSX_DAC      equ 0F7F6H ; DECIMAL ACCUMULATOR (Interger in USR()-function stored to #F7F8)
MSX_HOLD8    equ 0F806H ; Registers for decimal multiplication
MSX_HOLD2    equ 0F836H ; Work area in the execution of numerical operators
MSX_HOLD     equ 0F83EH ; Work area in the execution of numerical operators
MSX_DAC_ARG  equ 0F847H ; Area to set the value to be calculate with DAC
MSX_RNDX     equ 0F857H ; Last random number

; DATA AREA USED BY BASIC INTERPRETER

MSX_MAXFIL   equ 0F85FH ; High legal file number
MSX_FILTAB   equ 0F860H ; Starting address of of file data area
MSX_NULBUF   equ 0F862H ; Points to file 0 buffer ( used in SAVE & LOAD st.)
MSX_PTRFIL   equ 0F864H ; Points to file data of currently accessing file
MSX_RUNFLG   equ 0F866H ; Non-zero for run after load
MSX_FILNAM   equ 0F866H ; Name for FILES, NAME & others
MSX_FILNM2   equ 0F871H ; Second name for NAME
MSX_NLONLY   equ 0F87CH ; When loading  program ( 00 = NON BASIC / 01 = BASIC )
MSX_SAVEND   equ 0F87DH ; End address for BSAVE
MSX_FNKSTR   equ 0F87FH ; FUNCTION KEY AREA
MSX_CGPNT    equ 0F91FH ; Slot ID of the character FONT
MSX_ADDPNT   equ 0F920H ; Address of the character FONT
MSX_NAMBAS   equ 0F922H ; Base address of current pattern name table
MSX_CGPBAS   equ 0F924H ; Base address of current pattern generator table
MSX_PATBAS   equ 0F926H ; Base address of current sprite generator table
MSX_ATRBAS   equ 0F928H ; Base address of current sprite attribute table

MSX_CLOC    equ 0F92AH ; Cursor Location
MSX_CMASK   equ 0F92CH ; Mask of Cursor
MSX_MINDEL  equ 0F92DH ; Used by LINE  command in BASIC
MSX_MAXDEL  equ 0F92FH ; Used by LINE  command in BASIC

; DATA AREA FOR CIRCLE STATEMENT

MSX_ASPECT   equ 0F931H ; Aspect ratio of the circle; set by <ratio> of CIRCLE
MSX_CENCNT   equ 0F933H ; End count
MSX_CLINEF   equ 0F935H ; Flag to draw line to centre
MSX_CNPNTS   equ 0F936H ; Point to be plottted
MSX_CPLOTF   equ 0F938H ; Plot polarity flag
MSX_CPCNT    equ 0F939H ; 1/8 of number of points in circle
MSX_CPCNT8   equ 0F93BH ;
MSX_CRCSUM   equ 0F93DH ;
MSX_CSTCNT   equ 0F93FH ;
MSX_CSCLXY   equ 0F941H ; Scale of X & Y
MSX_CSAVEA   equ 0F942H ; reservation area of ADVGRP
MSX_CSAVEM   equ 0F944H ; reservation area of ADVGRP
MSX_CXOFF    equ 0F945H ; X offset from center
MSX_CYOFF    equ 0F947H ; Y offset from center

; DATA AREA FOR PAINT STATEMENT

MSX_LOHMSK   equ 0F949H ; Used by PAINTcommand in BASIC
MSX_LOHDIR   equ 0F94AH ; Used by PAINTcommand in BASIC
MSX_LOHADR   equ 0F94BH ; Used by PAINTcommand in BASIC
MSX_LOHCNT   equ 0F94DH ; Used by PAINTcommand in BASIC
MSX_SKPCNT   equ 0F94FH ; Skip count,  Used by PAINTcommand in BASIC
MSX_MOVCNT   equ 0F951H ; Movement count,  Used by PAINTcommand in BASIC
MSX_PDIREC   equ 0F953H ; Direction of the paint, Used by PAINTcommand in BASIC
MSX_LFPROG   equ 0F954H ; Used by PAINTcommand in BASIC
MSX_RTPROG   equ 0F955H ; Used by PAINTcommand in BASIC
MSX_MCLTAB   equ 0F956H ; Used by DRAW / PLAY command in BASIC
MSX_MCLFLG   equ 0F958H ; Used by DRAW / PLAY command in BASIC
MSX_QUETAB   equ 0F959H ; queue information  (VOICAQ, VOICBQ, VOICCQ and RS2IQ (RS232))
MSX_QUEBAK   equ 0F971H ;
MSX_VOICAQ   equ 0F975H ; 1st Voice of Play Buffer (PSG)

; If MSX-Music is present area #F9C0-#F9F8 is used to store copy of YM2413 registers

MSX_VOICBQ   equ 0F9F5H ; 2st Voice of Play Buffer (PSG)
MSX_VOICCQ   equ 0FA75H ; 3st Voice of Play Buffer (PSG)
MSX_DPPAGE   equ 0FAF5H ; Display page number (SET PAGE X)
MSX_ACPAGE   equ 0FAF6H ; active page number (SET PAGE ,X)
MSX_AVCSAV   equ 0FAF7H ; Reserves AV control port
MSX_EXBRSA   equ 0FAF8H ; SUB_ROM / EXT-ROM slot address
MSX_CHRCNT   equ 0FAF9H ; Character counter in the buffer, used in KANA-ROM
MSX_ROMA     equ 0FAFAH ; Area to store KANA character (Japan version only)
MSX_MODE     equ 0FAFCH ; mode switch for VRAM size
MSX_NORUSE   equ 0FAFDH ; unused <edit> Used by KANJI-ROM for rendering KANJI fonts in graphic modes:

; 	bit 7 Don't return to textmode
; 	bit 6 if 1 and #f7f4 (DECCNT)=0, read SHIFT status ???
; 	bit 5 Disable some functinality
; 	bit 4 Not in use
; 	bit 3 color 0 = Transparent
; 	BIT 0-2:  Logical operation on kanji font draw:
; 		  0       PSET
; 		  1       AND
; 		  2       OR
; 		  3       XOR
; 		  4       NOT

MSX_XSAVE    equ 0FAFEH ; [10000000 XXXXXXXX] X-coordinate Mouse/Trackball/Lightpen
MSX_YSAVE    equ 0FB00H ; [*0000000 YYYYYYYY]  Y-coordinate Mouse/Trackball/Lightpen
MSX_LOGOPR   equ 0FB02H ; Logical operation code

; Data area used by RS-232C or disk drive

MSX_RSTMP    equ 0FB03H ; Temporary data storage for RS232 Driver
MSX_TOCNT    equ 0FB03H ;
MSX_RSFCB_L  equ 0FB04H ; Adress of the RS232 LOW
MSX_RSFCB_H  equ 0FB05H ; Adress of the RS232 HIGH
MSX_RSIQLN   equ 0FB06H ; Byte DATA
MSX_MEXBIH   equ 0FB07H ; Hook RST (&H30)
MSX_BYTEDT1  equ 0FB08H ; Byte Data
MSX_DTLOW    equ 0FB09H ; LOW
MSX_DTHIGH   equ 0FB0AH ; HIGH
MSX_OLDINT   equ 0FB0BH ; Old interupt ( RET &HC9 )
MSX_OLDSTT   equ 0FB0CH ; Hook
MSX_RSUNKN   equ 0FB10H ; Unknown
MSX_HKRST    equ 0FB11H ; Hook RST (&H30)
MSX_BYTEDT2  equ 0FB12H ; Byte DATA
MSX_DT2LOW   equ 0FB13H ; LOW
MSX_DT2HIGH  equ 0FB14H ; HIGH
MSX_RSRET    equ 0FB15H ; ( RET &HC9 )
MSX_DEVNUM   equ 0FB16H ; Byte OFFSET
MSX_DATCNT   equ 0FB17H ; Byte DATA
MSX_BYTPNT1  equ 0FB18H ; Byte POINTER
MSX_BYTPNT2  equ 0FB19H ; Byte POINTER
MSX_ERRORS   equ 0FB1AH ; Byte DATA
MSX_FLAGS    equ 0FB1BH ; BIT BOOLEAN
MSX_ESTBLS   equ 0FB1CH ; BIT BOOLEAN
MSX_COMMSK   equ 0FB1DH ; Byte DATA
MSX_LSTCOM   equ 0FB1EH ; Byte DATA
MSX_LSTMOD   equ 0FB1FH ; Byte DATA
MSX_RSUNK2   equ 0FB20H ;

; Data area used by MSX-DOS

MSX_DRVINV_1_DSKS equ 0FB21H ; Nr. of drives connected to disk interface 1
MSX_DRVINV_1_SLT  equ 0FB22H ; Slot adress of disk interface 1
MSX_DRVINV_2_DSKS equ 0FB23H ; Nr. of drives connected to disk interface 2
MSX_DRVINV_2_SLT  equ 0FB24H ; Slot adress of disk interface 2
MSX_DRVINV_3_DSKS equ 0FB25H ; Nr. of drives connected to disk interface 3
MSX_DRVINV_3_SLT  equ 0FB26H ; Slot adress of disk interface 3
MSX_DRVINV_4_DSKS equ 0FB27H ; Nr. of drives connected to disk interface 4
MSX_DRVINV_4_SLT  equ 0FB28H ; Slot adress of disk interface 4

; music

MSX_PRSCNT  equ 0FB35H ; Used by PLAY command in BASIC
MSX_SAVSP   equ 0FB36H ; Used by PLAY command in BASIC
MSX_VOICEN  equ 0FB38H ; Used by PLAY command in BASIC
MSX_SAVVOL  equ 0FB39H ; Used by PLAY command in BASIC
MSX_MCLLEN  equ 0FB3BH ; Used by PLAY command in BASIC
MSX_MCLPTR  equ 0FB3CH ; Used by PLAY command in BASIC
MSX_QUEUEN  equ 0FB3EH ;
MSX_MUSICF  equ 0FB3FH ;
MSX_PLYCNT  equ 0FB40H ;
MSX_VCBA    equ 0FB41H ;
MSX_VCBB    equ 0FB66H ;
MSX_VCBC    equ 0FB8BH ;
MSX_ENSTOP  equ 0FBB0H ; <>0 if warm start enabled (CTRL+SHIFT+GRPH+KANA/CODE for warm start)
MSX_BASROM  equ 0FBB1H ; <>0 if basic is in rom (CTRL+STOP disabled)
MSX_LINTTB  equ 0FBB2H ; line terminator table (<>0 if line terminates)
MSX_FSTPOS  equ 0FBCAH ; first position for inlin
MSX_CODSAV  equ 0FBCCH ; code save area for cursor
MSX_FNKSWI  equ 0FBCDH ; indicate which func key is displayed
MSX_FNKFLG  equ 0FBCEH ; fkey which have subroutine
MSX_ONGSBF  equ 0FBD8H ; global event flag
MSX_CLIKFL  equ 0FBD9H ;
MSX_OLDKEY  equ 0FBDAH ;
MSX_NEWKEY  equ 0FBE5H ;

;  Example of European Keyboard Layout
; FBE5 0  => 7       6         5         4         3         2         1         0
; FBE6 1  => ; ]         [         \         =         -         9         8
; FBE7 2  => B       A         ACCENT    /         .         ,         `         '
; FBE8 3  => J       I         H         G         F         E         D         C
; FBE9 4  => R       Q         P         O         N         M         L         K
; FBEA 5  => Z       Y         X         W         V         U         T         S
; FBEB 6  => F3      F2        F1        CODE      CAPS      GRPH      CTRL      SHIFT
; FBEC 7  => RET     SEL       BS        STOP      TAB       ESC       F5        F4
; FBED 8  => RIGHT   DOWN      UP        LEFT      DEL       INS       HOME      SPACE
; FBEE 9  => 4       3         2         1         0          /         +         *
; FBEF 10 => .         ,         -         9         8         7         6         5

MSX_KEYBUF  equ 0FBF0H ; key code buffer
MSX_BUFEND  equ 0FC18H ; end of key buffer
MSX_LINWRK  equ 0FC18H ;
MSX_PATWRK  equ 0FC40H ; Pattern Buffer
MSX_BOTTOM  equ 0FC48H ;
MSX_HIMEM   equ 0FC4AH ;
MSX_TRPTBL  equ 0FC4CH ;
MSX_RTYCNT  equ 0FC9AH ;
MSX_INTFLG  equ 0FC9BH ; This flag is set if STOP or CTRL + STOP is pressed

; 0 = Not Pressed
; 3 = CTRL +STOP Pressed
; 4 = STOP Pressed

MSX_PADY   equ 0FC9CH ; Y-coordinate of a connected Graphics Tablet (PAD)
MSX_PADX   equ 0FC9DH ; X-coordinate of a connected Graphics Tablet (PAD)
MSX_JIFFY  equ 0FC9EH ; Contains value of the software clock, each interrupt of the VDP  it is increased by 1.

; The contents can be read or changed by the 'TIME' function or 'TIME' statement.

MSX_INTVAL  equ 0FCA0H ; Contains length of the interval when the ON INTERVAL routine was established.
MSX_INTCNT  equ 0FCA2H ; ON INTERVAL counter (counts backwards)
MSX_LOWLIM  equ 0FCA4H ; Used by the Cassette system (minimal length of startbit)
MSX_WINWID  equ 0FCA5H ; Used by the Cassette system (store the difference between a low-and high-cycle)
MSX_GRPHED  equ 0FCA6H ; flag for graph. char
MSX_ESCCNT  equ 0FCA7H ; escape sequence counter FCA8 INSFLG  insert mode flag
MSX_CSRSW   equ 0FCA9H ; cursor display switch
MSX_CSTYLE  equ 0FCAAH ; cursor style i.e. Used if INS Key is used ( 00# = Full Cursor / FF# = Halve Cursor )
MSX_CAPST   equ 0FCABH ; capital status ( 00# = Off / FF# = On )
MSX_KANAST  equ 0FCACH ; russian key status (Dead Keys)

; 0 = No Dead Keys
; 1 = Dead Key > Accent Grave
; 2 = SHIFT + Dead Key > Accent Egu
; 3 = CODE + Dead Key > Accent Circumflex
; 4 = SHIFT + CODE + Dead Key > Trema

MSX_KANAMD  equ 0FCADH ;
MSX_FLBMEM  equ 0FCAEH ; 0 if loading basic programm
MSX_SCRMOD  equ 0FCAFH ; screen mode
MSX_OLDSCR  equ 0FCB0H ; old screen mode
MSX_CASPRV  equ 0FCB1H ;
MSX_BRDATR  equ 0FCB2H ; border color for paint
MSX_GXPOS   equ 0FCB3H ; X-position
MSX_GYPOS   equ 0FCB5H ; Y-position
MSX_GRPACX  equ 0FCB7H ;
MSX_GRPACY  equ 0FCB9H ;
MSX_DRWFLG  equ 0FCBBH ; Used by the DRAW statement  (DrawFlag)

; Bit 7 = Draw Line 0 = No / 1 = Yes ( ,N )
; Bit 6 = Move Cursor 0 = Yes / 1 = Yes ( ,B )
; Bit 5 - 0 Unused

MSX_DRWSCL  equ 0FCBCH ; Used by the DRAW statement  (DrawScaling)
MSX_DRWANG  equ 0FCBDH ; Used by the DRAW statement (DrawAngle)

; 0 = 0∞  rotation
; 1 = 90∞ rotation
; 2= 180∞ rotation
; 3= 270∞ Rotation

MSX_RUNBNF   equ 0FCBEH ; Run Binary File After loading ( Bload"File.Bin",R ) 0 = Don't Run / 1 = Run
MSX_SAVENT   equ 0FCBFH ; start address for BSAVE / BLOAD operations
MSX_EXPTBL_0 equ 0FCC1H ; flag for primary expanded slot 0 80h = Expanded / 00h = NOT Expanded
MSX_EXPTBL_1 equ 0FCC2H ; flag for primary expanded slot 1 80h = Expanded / 00h = NOT Expanded
MSX_EXPTBL_2 equ 0FCC3H ; flag for primary expanded slot 2 80h = Expanded / 00h = NOT Expanded
MSX_EXPTBL_3 equ 0FCC4H ; flag for primary expanded slot 3 80h = Expanded / 00h = NOT Expanded
MSX_SLTTBL_0 equ 0FCC5H ; current expanded slot 0 reg
MSX_SLTTBL_1 equ 0FCC6H ; current expanded slot 1 reg
MSX_SLTTBL_2 equ 0FCC7H ; current expanded slot 2 reg
MSX_SLTTBL_3 equ 0FCC8H ; current expanded slot 3 reg
MSX_SLTATR   equ 0FCC9H ; Slotatributes found during start process

; Bit 7 = Basic programm 0 = No / 1 = Yes
; Bit 6 = Device Extention  0 = No / 1 = Yes
; Bit 5 = Statement Extention  0 = No / 1 = Yes
; Bit 4 - 0 = Unused

MSX_SLTWRK equ 0FD09H ; (free word = FD09H + 32*basic slot + 8*expansion slot + 2*page)
MSX_PROCNM equ 0FD89H ; name of expanded statement
MSX_DEVICE equ 0FD99H ; device ID for cartrige 0-3

; HOOKS

MSX_HKEYI   equ 0FD9AH ; 0C4A  Interrupt handler
MSX_HTIMI   equ 0FD9FH ; 0C53  Interrupt handler
MSX_HCHPU   equ 0FDA4H ; 08C0  ƒœ CHPUT(A-character; SAVE ALL)
MSX_HDSPC   equ 0FDA9H ; 09E6  Display cursor    (no param.)
MSX_HERAC   equ 0FDAEH ; 0A33  Errase cursor     (no param.)
MSX_HDSPF   equ 0FDB3H ; 0B2B  DSPFNK std routine(no param.)
MSX_HERAF   equ 0FDB8H ; 0B15  ERAFNK std routine(no param.)
MSX_HTOTE   equ 0FDBDH ; 0842  TOTEXT std routine
MSX_HCHGE   equ 0FDC2H ; 10CE  CHGET  std routine
MSX_HINIP   equ 0FDC7H ; 071E  Copy character set to VDP
MSX_HKEYC   equ 0FDCCH ; 1025  Keyboard decoder
MSX_HKYEA   equ 0FDD1H ; 0F10  Keyboard decoder
MSX_HNMI    equ 0FDD6H ; 1398  NMI std routine
MSX_HPINL   equ 0FDDBH ; 23BF  PINLIN std routine
MSX_HQINL   equ 0FDE0H ; 23CC  QINLIN std routine
MSX_HINLI   equ 0FDE5H ; 23D5  INLIN std routine
MSX_HONGO   equ 0FDEAH ; 7810  "ON DEVICE GOSUB"
MSX_HDSKO   equ 0FDEFH ; 7C16  "DSKO$"
MSX_HSETS   equ 0FDF4H ; 7C1B  "SET"
MSX_HNAME   equ 0FDF9H ; 7C20  "NAME"
MSX_HKILL   equ 0FDFEH ; 7C25  "KILL"
MSX_HIPL    equ 0FE03H ; 7C2A  "IPL"
MSX_HCOPY   equ 0FE08H ; 7C2F  "COPY"
MSX_HCMD    equ 0FE0DH ; 7C34  "CMD"
MSX_HDSKF   equ 0FE12H ; 7C39  "DSKF"
MSX_HDSKI   equ 0FE17H ; 7C3E  "DSKI$"
MSX_HATTR   equ 0FE1CH ; 7C43  "ATTR$"
MSX_HLSET   equ 0FE21H ; 7C48  "LSET"
MSX_HRSET   equ 0FE26H ; 7C4D  "RSET"
MSX_HFIEL   equ 0FE2BH ; 7C52  "FIELD"
MSX_HMKI$   equ 0FE30H ; 7C57  "MKI$"
MSX_HMKS$   equ 0FE35H ; 7C5C  "MKS$"
MSX_HMKD$   equ 0FE3AH ; 7C61  "MKD$"
MSX_HCVI    equ 0FE3FH ; 7C66  "CVI"
MSX_HCVS    equ 0FE44H ; 7C6B  "CVS"
MSX_HCVD    equ 0FE49H ; 7C70  "CVD"
MSX_HGETP   equ 0FE4EH ; 6A93  Locate FCB
MSX_HSETF   equ 0FE53H ; 6AB3  Locate FCB
MSX_HNOFO   equ 0FE58H ; 6AF6  "OPEN": not found
MSX_HNULO   equ 0FE5DH ; 6B0F  "OPEN"
MSX_HNTFL   equ 0FE62H ; 6B3B  Close I/O buffer 0
MSX_HMERG   equ 0FE67H ; 6B63  "MERGE/LOAD"
MSX_HSAVE   equ 0FE6CH ; 6BA6  "SAVE"
MSX_HBINS   equ 0FE71H ; 6BCE  "SAVE"
MSX_HBINL   equ 0FE76H ; 6BD4  "MERGE/LOAD"
MSX_HFILE   equ 0FE7BH ; 6C2F  "FILES"
MSX_HDGET   equ 0FE80H ; 6C3B  "GET/PUT"
MSX_HFILO   equ 0FE85H ; 6C51  Sequential output
MSX_HINDS   equ 0FE8AH ; 6C79  Sequential input
MSX_HRSLF   equ 0FE8FH ; 6CD8  "INPUT$"
MSX_HSAVD   equ 0FE94H ; 6D03"LOC",6D14"LOF",6D25"EOF",6D39"FPOS"
MSX_HLOC    equ 0FE99H ; 6D0F  "LOC"
MSX_HLOF    equ 0FE9EH ; 6D20  "LOF"
MSX_HEOF    equ 0FEA3H ; 6D33  "EOF"
MSX_HFPOS   equ 0FEA8H ; 6D43  "FPOS"
MSX_HBAKU   equ 0FEADH ; 6E36  "LINE INPUT#"
MSX_HPARD   equ 0FEB2H ; 6F15  Parse device name
MSX_HNODE   equ 0FEB7H ; 6F33  Parse device name
MSX_HPOSD   equ 0FEBCH ; 6F37  Parse device name
MSX_HDEVN   equ 0FEC1H ; This hook not used
MSX_HGEND   equ 0FEC6H ; 6F8F  I/O function despatcher
MSX_HRUNC   equ 0FECBH ; 629A  Run-clear
MSX_HCLEA   equ 0FED0H ; 62A1  Run-clear
MSX_HLOPD   equ 0FED5H ; 62AF  Run-clear
MSX_HSTKE   equ 0FEDAH ; 62F0  Reset stack
MSX_HISFL   equ 0FEDFH ; 145F  ISFLIO std routine
MSX_HOUTD   equ 0FEE4H ; 1B46  OUTDO std routine
MSX_HCRDO   equ 0FEE9H ; 7328  CR,LF to OUTDO
MSX_HDSKC   equ 0FEEEH ; 7374  Mainloop line input
MSX_HDOGR   equ 0FEF3H ; 593C  Line draw
MSX_HPRGE   equ 0FEF8H ; 4039  Program end
MSX_HERRP   equ 0FEFDH ; 40DC  Error handler
MSX_HERRF   equ 0FF02H ; 40FD  Error handler
MSX_HREAD   equ 0FF07H ; 4128  Mainloop "OK"
MSX_HMAIN   equ 0FF0CH ; 4134  Mainloop
MSX_HDIRD   equ 0FF11H ; 41A8  Mainloop direct statement
MSX_HFINI   equ 0FF16H ; 4237  Mainloop finished
MSX_HFINE   equ 0FF1BH ; 4247  Mainloop finished
MSX_HCRUN   equ 0FF20H ; 42B9  Tokenise
MSX_HCRUS   equ 0FF25H ; 4353  Tokenise
MSX_HISRE   equ 0FF2AH ; 437C  Tokenise
MSX_HNTFN   equ 0FF2FH ; 43A4  Tokenise
MSX_HNOTR   equ 0FF34H ; 44EB  Tokenise
MSX_HSNGF   equ 0FF39H ; 45D1  "FOR"
MSX_HNEWS   equ 0FF3EH ; 4601  Runloop new statement
MSX_HGONE   equ 0FF43H ; 4646  Runloop execute
MSX_HCNRG   equ 0FF48H ; 4666  CHRGTR std routine
MSX_HRETU   equ 0FF4DH ; 4821  "RETURN"
MSX_HPRTF   equ 0FF52H ; 4A5E  "PRINT"
MSX_HCOMP   equ 0FF57H ; 4A94  "PRINT"
MSX_HFINP   equ 0FF5CH ; 4AFF  "PRINT"
MSX_HTRMN   equ 0FF61H ; 4B4D  "READ/INPUT" error
MSX_HFRME   equ 0FF66H ; 4C6D  Expression Evaluator
MSX_HNTPL   equ 0FF6BH ; 4CA6  Expression Evaluator
MSX_HEVAL   equ 0FF70H ; 4DD9  Factor Evaluator
MSX_HOKNO   equ 0FF75H ; 4F2C  Factor Evaluator
MSX_HFING   equ 0FF7AH ; 4F3E  Factor Evaluator
MSX_HISMI   equ 0FF7FH ; 51C3  Runloop execute
MSX_HWIDT   equ 0FF84H ; 51CC  "WIDTH"
MSX_HLIST   equ 0FF89H ; 522E  "LIST"
MSX_HBUFL   equ 0FF8EH ; 532D  Detokenise
MSX_HFRQI   equ 0FF93H ; 543F  Convert to integer
MSX_HSCNE   equ 0FF98H ; 5514  Line number to pointer
MSX_HFRET   equ 0FF9DH ; 67EE  Free descriptor
MSX_HPTRG   equ 0FFA2H ; 5EA9  Variable search
MSX_HPHYD   equ 0FFA7H ; 148A  PHYDIO std routine
MSX_HFORM   equ 0FFACH ; 148E  FORMAT std routine
MSX_HERRO   equ 0FFB1H ; 406F  Error handler( Œ¡ﬁ¡Ãœ )
MSX_HLPTO   equ 0FFB6H ; 085D  LPTOUT std routine
MSX_HLPTS   equ 0FFBBH ; 0884  LPTSTT std routine
MSX_HSCRE   equ 0FFC0H ; 79CC  "SCREEN"
MSX_HPLAY   equ 0FFC5H ; 73E5  "PLAY" statement
MSX_EXTBIO  equ 0FFCAH ; xxxx Used to access external BIOS implementations
MSX_HBGFD   equ 0FFCFH ; before physical operation with disk (BUG: Not called on MSX tR when DOS2 active)
MSX_HENFD   equ 0FFD4H ; after physical operation with disk  (BUG: Not called on MSX tR when DOS2 active)
MSX_RG08SAV equ 0FFE7H ; Content of VDP(09) register (R#08)
MSX_RG09SAV equ 0FFE8H ; Content of VDP(10) register (R#09)
MSX_RG10SAV equ 0FFE9H ; Content of VDP(11) register (R#10)
MSX_RG11SAV equ 0FFEAH ; Content of VDP(12) register (R#11)
MSX_RG12SAV equ 0FFEBH ; Content of VDP(13) register (R#12)
MSX_RG13SAV equ 0FFECH ; Content of VDP(14) register (R#13)
MSX_RG14SAV equ 0FFEDH ; Content of VDP(15) register (R#14)
MSX_RG15SAV equ 0FFEEH ; Content of VDP(16) register (R#15)
MSX_RG16SAV equ 0FFEFH ; Content of VDP(17) register (R#16)
MSX_RG17SAV equ 0FFF0H ; Content of VDP(18) register (R#17)
MSX_RG18SAV equ 0FFF1H ; Content of VDP(19) register (R#18)
MSX_RG19SAV equ 0FFF2H ; Content of VDP(20) register (R#19)
MSX_RG20SAV equ 0FFF3H ; Content of VDP(21) register (R#20)
MSX_RG21SAV equ 0FFF4H ; Content of VDP(22) register (R#21)
MSX_RG22SAV equ 0FFF5H ; Content of VDP(23) register (R#22)
MSX_RG23SAV equ 0FFF6H ; Content of VDP(24) register (R#23)
MSX_ROMSLT  equ 0FFF7H ; Slotadress of Main-ROM
MSX_RESERV  equ 0FFF8H ; Reserved
MSX_RG25SAV equ 0FFFAH ; Content of VDP(26) register (R#25) MSX2+
MSX_RG26SAV equ 0FFFBH ; Content of VDP(27) register (R#26) MSX2+
MSX_RG27SAV equ 0FFFCH ; Content of VDP(28) register (R#27) MSX2+
MSX_TMPSPS  equ 0FFFDH ; Temporary stack pointer storage
MSX_SLTSL   equ 0FFFFH ; Secondary slot select register (Reading returns INVERTED! previous written value)
;
