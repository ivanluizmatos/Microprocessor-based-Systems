ldr r0,=a
mov r1,#0

@...

Begin:
    CMP r1,r0
    BGT End       
    BL g          @ appel de la function g (si i<=a)
    ADD r1,r1,#1  
    B Begin       

End:
    B End
    
g:
    @...
    BX lr