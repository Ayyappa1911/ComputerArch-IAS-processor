Read me file:


IMT2020529 Dhanvi Medha
IMT2020555 Ayyappa Koppuravuri

The IMT2020529_IMT2020555_IAS.cpp file has the implementation of IAS machine.All the commands given in the slides are implemented and are identified 
by their corresponding opcodes.The Machine is tested for two different C programs and 3 different test cases.
fac.txt,mul.txt and div.txt are the input text cases with hexadecimal/decimal input. (addresses are in decimal and instructions in hexadecimal).
 
You can run the IMT2020529_IMT2020555_IAS.cpp file and test it with the test cases in 
 fac.txt,mul.txt and div.txt.

Description of all the functions and their outputs are stored in the “factorial Output.pdf” and “If Else Multiplciation.pdf” files.
These files also include the corresponding C equivalent programs.The values of all the important 
register variables are repeatedly printed after implementing an instruction.

Assumptions made during the implementation:

* There cannot be a half instruction,in case we want to implement a half instruction,we should initialise 
the right part of the instruction to zero.This half instruction should be the last instruction of all.
If any half instruction is implemented in between ,It will halt the Machine and will not give the required output.

* Halt variable in the program is either the left instruction or the right instruction whose value is 0.

* Negative numbers are dealt in 2’s complement format instead of sign magnitude form.

* Some intermediate variables are used for some interim operations. (apart from standard register variables like MAR,PC,etc)