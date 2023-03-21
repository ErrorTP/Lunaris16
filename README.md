## Lunaris16
[![C CI](https://github.com/ErrorTheProgrammer/Lunaris16/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/ErrorTheProgrammer/Lunaris16/actions/workflows/c-cpp.yml)
<br>
Lunaris is an assembly language designed for the Horizon16.
This is solely created for experience and fun and is not intended to be used in anything serious.
## How it works
Lunaris is quite a simple assembler and assembly language and currently lacks many features.
As of now both Horizon and Lunaris are under heavy development.
I am still learning C so both are quite prone to bugs, and lack very good codebases.
## The Instruction Set
Instructions are comprised of 16 bits.
Each instruction is split into a 5 bit operator and a 11 bit argument.

| Instruction | Operator | Argument | Function |
|--|--|--|--|
|NOP|00000|0000000|Does nothing|
|LDA|00001|Number|Loads an immediate value into A|
|LDB|00010|Number|Loads an immediate value into B|
|LDC|00011|Number|Loads an immediate value into C|
|LMA|00100|Memory location|Loads a value from memory to register A|
|LMB|00101|Memory location|Loads a value from memory to register B|
|LMC|00110|Memory location|Loads a value from memory to register C|
|STA|00111|Memory location|Stores value of A to memory|
|STC|01000|Memory location|Stores value of C in memory|
|JMP|01001|Instruction location|Unconditionally jumps to location|
|JMPZ|01011|Instruction location|Jumps if register A is 0
|JMPC|01100|Instruction location|Jumps if carry flag|
|JMPNC|01101|Instruction location|Jumps if carry flag is false|
|JMPE|01111|Instruction location|Jumps if A is equal to C|
|BSR|10000|Amount|Bitshifts A right the given amount|
|BSL|10001|Amount|Bitshifts A left the given amount|

Extended

|Instruction|Binary|Function|
|--|--|--|
|ADD|1111100000000000|Adds B to A and stores the result in A|
|SUB|1111100000000001|Subtracts B from A and stores the result in A
|MULT|1111100000000010|Multiplies B by A and stores the result in A
|DIV|1111100000000011|Divides register A by register B and stores the result in A
|MIA|1111100000000100|Loads register A as a memory address and copies the value to C
|MOA|1111100000000101|Uses register A as a memory address and stores the value in C
|SWP|1111100000000110|Swap register A with B (C is erased as a side effect)
|SWC|1111100000000111|Swap register A and C (B is erased as a side effect)
|HLT|1111100000001000|Stop the clock
|CTR|1111100000001001|Loads program counter value into register A
|AND|1111100000001010|Bitwise AND on registers A and B
|OR|1111100000001011|Bitwise OR on registers A and B
|NOT|1111100000001100|Bitwise NOT on register A

# These are subject to change