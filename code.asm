.MODEL SMALL
.DATA
b3 DW 0
c2 DW 0
.CODE
.STARTUP
             MOV AX, c2
                PUSH AX
              MOV AX, 20
                PUSH AX
               POP AX
                 MOV c2,AX
              MOV AX, b3
                PUSH AX
              MOV AX, c2
                PUSH AX
              MOV AX, 10
                PUSH AX
               POP AX 
              POP CX 
              IMUL CX
             PUSH AX
               POP AX
                 MOV b3,AX
 .EXIT
END
