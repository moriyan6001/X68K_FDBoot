cd e:\x68000\BootFD
copy e:IPL_TB.s
copy e:TBI68K.ASM

pause

has IPL_TB.s
hlk -x -b0x2000 IPL_TB.o
tool\hcv -z2000 IPL_TB.x
tool\cutheader IPL_TB.z IPL_TB.bin

has TBI68K.ASM
hlk -x -b0x3000 TBI68K.o
tool\hcv -z3000 TBI68K.X
tool\cutheader TBI68K.z TBI68K.bin
