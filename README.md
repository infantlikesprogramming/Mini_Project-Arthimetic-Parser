# Mini_Project-Arthimetic-Parser

This project reimplements the Arithmetic Parser (no parenthesis) from https://github.com/DoctorWkt/acwj - 03 Precedence.

This parser will evaluate simple arithmetic expressions comprise of "+,-,*,/" and integers.

Grammar: There can only be integers and operations. There must be one and only one operation in between integers (run example input01 to see).

How to run:
- Command line (Linux): cc -o parser -g main.c scan.c expr2.c tree.c interp.c

./parser input01.txt 

- There can be other txt files in place of input01

