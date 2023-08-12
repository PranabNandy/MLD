
![Screenshot](1.png)

# Makefile

TARGET:exe

#### common_math.o:common_math/common_math.c

	gcc -c -I common_math common_math/common_math.c -o common_math/common_math.o
 
#### complex_math.o:complex_math/complex_math.c

	gcc -c -I complex_math complex_math/complex_math.c -o complex_math/complex_math.o
 
#### trig_math.o:trig_math/trig_math.c

	gcc -c -I trig_math trig_math/trig_math.c -o complex_math/complex_math.o
	
#### libcalculator.a:trig_math/trig_math.o common_math/common_math.o complex_math/complex_math.o

	ar rs libcalculator.a common_math/common_math.o complex_math/complex_math.o trig_math/trig_math.o
 
#### exe.elf:main.o libcalculator.a

	gcc main.o -o exe.elf -L . libcalculator.a -lm
 
#### main.o:main.c

	gcc -c -I common_math -I complex_math -I trig_math main.c -o main.o
	
	

## -lm == <math.h>   == libmath.so
	
	
	
	
	
	
