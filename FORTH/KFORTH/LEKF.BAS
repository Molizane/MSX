10 OPEN "kforth.mac" FOR INPUT AS #1: x = 1: a$ = ""
20 GOSUB 100
30 IF LOF(2) > 32000 GOTO 20
40 IF EOF(1) GOTO 70
50 b$ = INPUT$(1, #1): IF b$ = CHR$(&HD) GOTO 60 ELSE a$ = a$ + b$: GOTO 40
60 PRINT a$: PRINT #2, a$: a$ = "": b$ = INPUT$(1, #1): GOTO 30
70 IF a$ <> "" THEN PRINT a$: PRINT #2, a$
80 CLOSE : END
90 '
100 CLOSE #2: x$ = STR$(x): x$ = RIGHT$(x$, LEN(x$) - 1)
110 nome$ = "f-forth" + x$ + ".mac"
120 OPEN nome$ FOR OUTPUT AS #2: PRINT : PRINT nome$: x = x + 1: RETURN

