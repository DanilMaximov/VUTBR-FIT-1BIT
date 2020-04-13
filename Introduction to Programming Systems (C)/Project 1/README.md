The aim of the project is to create a program that emulates
a simplified algorithm for searching contacts entered using
a sequence of digits. The program input is a sequence of digits.
The output of the program will contain a list of contacts
that match the specified numeric filter.


$ ./proj1 <contacts.txt
petr dvorak, 603123456
jana novotna, 777987654
bedrich smetana ml., 541141120


$ ./proj1 12 <contacts.txt

petr dvorak, 603123456
bedrich smetana ml., 541141120


$ ./proj1 686 <seznam.txt

jana nOVOtna, 777987654
(OVO only for demonstration)


Task condition for compiling:
gcc -std=c99 -Wall -Wextra -Werror proj1.c -o proj1
