# Chapter 1 - Data Representation

Understanding numbering systems such as hexidecimal, octal, and binary helps simplify complex topics including boolean algebra and logic design, signed numeric representation, character codes, and packed data.

## Chapter Overview

- Numbering Systems:
	- Binary
	- Hexidecimal
	- Signed
	- Unsigned

- Binary Data Organization:
	- Bits
	- Nibbles
	- Bytes
	- Words
	- Double Words

- Binary Operations:
	- Arithmetic
	- Logical
	- Shift
	- Rotate

- Bit Fields
- Packed Data
- ASCII Character Set

### 1.1 Numbering Systems

Modern computers typically use a binary or two's compliment numbering system.

#### 1.1.1 Decimal System

The decimal system is a positional notation system with a base of 10.

#### 1.1.2 Binary System

Can be represented in terms of voltage levels:
- 0v (0)
- +5v (1)

The binary system works the same way as decimal except in base 2.

_bits_ is short for binary digits.

Bit zero is usually called the _low order_ (L.O.) bit. The left-most bit is usually called the _high order_ (H.O.) bit.

### 1.2 Data Organization

#### 1.2.1 Bits

The smallest "unit" of data on a computer is a single _bit_.

You can use a single bit to represent any two distinct items. For example, with a single bit, you could represent the color red and the number 3254.

**NOTE:** _Data is what you define it to be._

#### 1.2.2 Nibbles

A collection of four bits is called a _nibble_. 

With a nibble, you can represent up to 16 distinct values. In other words, you can represent a single BCD (_binary coded decimal_) number or hexadecimal digit.

Hexadecimal: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F

BCD: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

#### 1.2.3 Bytes

Consists of eight bits.

The smallest addressable datum (data item).

Main memory and I/O addresses are all byte addresses.

Bit 0 is the _low order bit_ or _least significant bit_, bit 7 is the _high order bit_ or _most significant bit_ of the byte. All other bits are referred to by their number.

**NOTE:** A byte contains exactly two nibbles.

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| H.O. Nibble | -> | -> | -> | <- | <- | <- | L.O. Nibble | 

Byte values require two hexadecimal digits.

It's more effecient to manipulate a whole byte than an individual bit or nibble, therefore it's typical to use a whole byte to represent data types with 256 items or fewer. An example is ASCII (128 codes) and Extended ASCII (256).

#### 1.2.4 Words

A word is a group of 16 bits.

There's two bytes and four nibbles in a word.

Unsigned values are represented by the binary value corresponding to the bits in the word.

Signed values use two's complement form.

#### 1.2.5 Double Words

Two words, four bytes, and eight nibbles.

Represents 32 bits.

### 1.3 Hexadecimal Numbering System

Base 16.

Represents numbers more compactly than binary and easy to convert to one another.

Some conventions:
- All numeric values begin with a decimal digit.
- All hexadecimal values end with the letter "h".
- All binary values end with the letter "b".
- Decimal numbers _may_ have a "t" or "d" suffix.

Below is a table that you can use to convert between hexadecimal and binary:

| Binary | Hexadecimal |
| --- | --- |
| 0000 | 0 |
| 0001 | 1 |
| 0010 | 2 |
| 0011 | 3 |
| 0100 | 4 |
| 0101 | 5 |
| 0110 | 6 |
| 0111 | 7 |
| 1000 | 8 |
| 1001 | 9 |
| 1010 | A |
| 1011 | B |
| 1100 | C |
| 1101 | D |
| 1110 | E |
| 1111 | F |

### 1.4 Arithmetic Operations on Binary and Hexadecimal Numbers

You can add, subtract, multiply, divide and perform other arithmetic operations.

A calculator is reccommended as our brains naturally want to do arithmetic in the decimal system which will result in wrong answers. Therefore, if you must do calculations by hand, you should convert the number to decimal, perform the arithmetic, and then convert it back to binary.

I personally don't have a calculator so I made a C program to do all the above steps for me.
- Decimal to Binary Converter: [binconv.c](https://github.com/rawb2020/Assembly/blob/main/Chapter1/binconv.c)
- TODO: Make a complete calculator

### 1.5 Logical Operations on Bits

Four main logical operations:
- Dyadic (2 operands):
	- AND
	- OR
	- XOR
- Monadic (1 operand):
	- NOT

All of the logical functions above only work with single bit operands ie. 1 or 0.

### 1.6 Logical Operations on Binary Numbers and Bit Strings

Logical functions on the 80x86 operate on a _bit-by-bit_ or _bitwise_ basis.

iDue to the reason above, it's easier to convert octal and hexadecimal numbers to binary before performing logical operations.

Masking: Using the logical AND, OR, and XOR operations to manipulate bit strings.

### 1.7 Signed and Unsigned Numbers

With _n_ bits we can represent the signed values in the range of -2^(n-1) to +2^(n-1)-1.

Two's compliment: 
- The highest order bit is the _sign bit_.
- If the sign bit is 0, the number is positive.
- If the sign bit is 1, the number is negative.

How to convert positive to negative:
1. Invert all bits (logical NOT)
2. Add one to the inverted result.

The 80x86 microprocessor provides an instruction **_NEG_** (negate) which performs two's compliment operation.

### 1.8 Sign and Zero Extension

Two's compliment integers have a fixed length so a problem arises when trying to convert say, an 8 bit integer to 16 bits, and vice versa.

**Sign Extension**: Converting to a larger bit value.

**Contraction**: Converting to a smaller bit value.

**Zero Extension**: Converting small unsigned values to larger unsigned values.

### 1.9 Shifts and Rotates

_Shift_ and _rotate_ operations are another set of logical operations that can be applied to bit strings.

- Left shift
- Right shift
	- Right arithmetic shift
- Left rotate
- Right rotate

#### Shift Left

- Zero gets shifted into the L.O. bit.
- The previous value of bit 7 will be the _carry_.

This is the same thing as multiplying it by it's radix.

More generally, if you shift a value left _n_ times, you multiply that value by 2^n.

#### Shift Right

Similarily, if you shift a value right _n_ times, you divide that value by 2^n.

However, when dealing with signed numbers, you have to use an _arithmetic shift right_.

##### Arithmetic Shift Right

Same as a regular shift right, except we leave bit seven alone.

This operation always rounds the numbers to the closest integer _which is less than or equal to the actual result_.

#### Rotates

The same as shifts, except the bit that gets shifted out gets placed back at the other end.

### 1.10 Bit Fields and Packed Data

Packed data is effecient in terms of memory usage, but computationally inefficient.

### 1.11 The ASCII Character Set

Divided into 4 groups of 32 characters.

The only difference between uppercase and lowercase characters is bit 5. Uppercase always has a zero in bit 5. Lowercase always have a one in bit 5.

Bits 5 and 6 determine which of the four groups of ASCII character set you're in:

| Bit 6 | Bit 5 | Group |
| --- | --- | --- |
| 0 | 0 | Control Characters |
| 0 | 1 | Digits & Punctuation |
| 1 | 0 | Upper Case & Special |
| 1 | 1 | Lower Case & Special |
