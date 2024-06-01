
#pragma nonrec

#include <stdio.h>
#include <math.h>

#define LOG_OP (TINY)3 /* xor */

VOID screen();
VOID totext();
VOID line();
VOID cls();
VOID calcxy();

XDOUBLE ll, kk, rr, rl, an, size, pp, temp, x, y;

main() {
    int n, iTemp, i[20];
    unsigned cx, cy, x2, y2;
    XDOUBLE two;

    screen((TINY)2);
    cls();

    itoxd(&two, 2);

    itoxd(&ll, 45);          /**** COMPRIMENTO INICIAL DO GALHO ****/
    itoxd(&temp, 5);
    itoxd(&kk, 4);
    xddiv(&kk, &kk, &temp);  /**** TAXA DE CRESCIMENTO DO GALHO ****/
    itoxd(&rr, 20);          /**** ANGULO DO GALHO DA ESQUERDA  ****/
    itoxd(&rl, 20);          /**** ANGULO DO GALHO DA DIREITA   ****/
    itoxd(&an, 90);
    xdmul(&size, &ll, &kk);

    itoxd(&temp, 1);
    xdatn(&pp, &temp);
    itoxd(&temp, 8);
    xdmul(&pp, &pp, &temp);
    itoxd(&temp, 360);
    xddiv(&pp, &pp, &temp);
    xdtoi(&y2, &ll);

    cx = 128;
    cy = 190-y2;
    line((unsigned)128, (unsigned)190, cx, cy, (TINY)15, LOG_OP);

    n=0;

    do {
      i[n]=0;
      xdmul(&temp, &two, &rr);
      xdsub(&an, &an, &temp);
      xdsub(&an, &an, &rl);

L150: xdadd(&an, &an, &rr);
      xdadd(&an, &an, &rl);

      calcxy();
      xdtoi(&x2, &x);
      xdtoi(&y2, &y);
      line(cx, cy, cx-x2, cy-y2, (TINY)15, LOG_OP);
      cx-=x2;
      cy-=y2;

      n++;
      xdmul(&size, &size, &kk);
      xdtoi(&iTemp, &size);
    } while (iTemp > 10);

L190:
    n--;
    xddiv(&size, &size, &kk);
    calcxy();
    xdtoi(&x2, &x);
    xdtoi(&y2, &y);
    line(cx, cy, cx+x2, cy+y2, (TINY)15, LOG_OP);
    cx+=x2;
    cy+=y2;

    if ((i[n]=i[n]+1) < 2) {
        goto L150;
    }

    xdsub(&an, &an, &rl);

    if (n) {
        goto L190;
    }

    while(!kbhit());
    getch();
    totext();
};

VOID calcxy() {
    XDOUBLE ra;
    xdmul(&ra, &an, &pp);
    xdcos(&x, &ra);
    xdmul(&x, &x, &size);
    xdsin(&y, &ra);
    xdmul(&y, &y, &size);
}
ul(&y, &y, &size);
}
);
}
ul(&y, &y, &size);
}
    torad(&ra);
    xdcos(&x, &ra);
    xdmul(&x, &x, &size);
    xdsin(&y, &ra);
    xdmul(&y, &y, &size);
}
}
