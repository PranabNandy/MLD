#### Heap memory Corruption:
-	Attempting to free memory already freed.
-	Freeing memory that was not allocated.
-	Attempting to read/write memory already freed.
-	Attempting to read/write to memory which was never allocated.
-	Memory allocation error.
-	Reading/writing to memory out of the bounds of a dynamically allocated array

#### Memory leak description: 

Memory is allocated but not released causing an application to consume memory reducing the available memory for other applications and eventually causing the system to page virtual memory to the hard drive slowing the application or crashing the application when than the computer memory resource limits are reached. The system may stop working as these limits are approached.

	
![Design](1.png)

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
	
	
	
	
	
	
