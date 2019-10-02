# int8_vs_class
Testing int8_t vs int with operator overload with switches

## Int class
Int class comes from here (warning: big file https://raw.githubusercontent.com/Arandur/prog3B/master/src/Int.cpp)

Small benchmark test to see how much of a difference on x86 it'd make.

None of this is intended for production (please!)

## Trivia
*There's a bug on the Int class' modulo operator. Parity can't be reached if using BenchInt::benchSimpleMod
*This might blow up on Wndows/MSVC++. Reduce intCount so it doesn't overflow the stack.
