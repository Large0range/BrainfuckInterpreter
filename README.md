Author: Boh Mingle

Description:
This program is a simple brainfuck interpreter. This took me about 2 hours to create and was written entirely on my own without any outside assistance.

Limitations:
30,000 cell tape, no glider automatic exiting, reading off file from disk, utilizes ftell and fseek.

Limitational Justification:
The program will read from an outside file 1 character at a time, pushing and popping to a stack to resolve loops and using ftell and fseek in order to properly
return to the correct position of the file. As you can imagine this results in incredibly slow behavior as ftell and fseek are not the fastest operations. However this does resolve the potential issue of reading the program into memory and it being too large for the buffer that we choose. Obviously you can write a vector like object that resizes as we need it to in order to write the program into memory however I chose to read it directly off the disk as this presents no size limitations. 

The tape has a standard size of 30,000 cells with no bounds checking. The program will prevent our cell pointer from moving past the tape bounds and will keep it on the edge. This will cause a hanging behavior on gliders that are intentionally written to stop at 0 OR the left / rightmost edge. As the program will not stop gliders from continually running into the edge. This is a behavior we allow as we do not want to inhibit the programmmer too much, allowing an infinite loop by continually running into the edge is something they might want to do so we allow it as a result. 

Potential Implementations:
Simple decompression and interpreter things that will speed up the program. Instead of incrementing at each +, simply count them and increment by that amount. Rewrite it into C code and then into machine code for quicker processing. Resizing the heap and storing the program in memory for faster access.