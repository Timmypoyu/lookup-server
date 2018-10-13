This file should contain:

  - your name
  - your UNI
  - lab assignment number
  - description for each part
  
The description should indicate whether your solution for the part is
working or not.  You may also want to include anything else you would
like to communicate to the grader such as extra functionalities you
implemented or how you tried to fix your non-working code.

------------------------------------------------------------------------------
Name: Wu Po Yu 
UNI: pw2440
lab3 

Part 1:
The code and functions  work as the instruction intended. 
==25820== Memcheck, a memory error detector
==25820== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==25820== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==25820== Command: ./mylist-test
==25820== 
testing addFront(): 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing flipSignDouble(): -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0 
testing flipSignDouble() again: 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing findNode(): OK
popped 9.0, the rest is: [ 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 8.0, the rest is: [ 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 7.0, the rest is: [ 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 6.0, the rest is: [ 5.0 4.0 3.0 2.0 1.0 ]
popped 5.0, the rest is: [ 4.0 3.0 2.0 1.0 ]
popped 4.0, the rest is: [ 3.0 2.0 1.0 ]
popped 3.0, the rest is: [ 2.0 1.0 ]
popped 2.0, the rest is: [ 1.0 ]
popped 1.0, the rest is: [ ]
testing addAfter(): 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 
popped 1.0, and reversed the rest: [ 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 ]
popped 9.0, and reversed the rest: [ 2.0 3.0 4.0 5.0 6.0 7.0 8.0 ]
popped 2.0, and reversed the rest: [ 8.0 7.0 6.0 5.0 4.0 3.0 ]
popped 8.0, and reversed the rest: [ 3.0 4.0 5.0 6.0 7.0 ]
popped 3.0, and reversed the rest: [ 7.0 6.0 5.0 4.0 ]
popped 7.0, and reversed the rest: [ 4.0 5.0 6.0 ]
popped 4.0, and reversed the rest: [ 6.0 5.0 ]
popped 6.0, and reversed the rest: [ 5.0 ]
popped 5.0, and reversed the rest: [ ]
==25820== 
==25820== HEAP SUMMARY:
==25820==     in use at exit: 0 bytes in 0 blocks
==25820==   total heap usage: 19 allocs, 19 frees, 1,312 bytes allocated
==25820== 
==25820== All heap blocks were freed -- no leaks are possible
==25820== 
==25820== For counts of detected and suppressed errors, rerun with: -v
==25820== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Part 2: 
No command line written for the valgrind below:
==27007== Memcheck, a memory error detector
==27007== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==27007== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==27007== Command: ./revecho
==27007== 

dude not found
==27007== 
==27007== HEAP SUMMARY:
==27007==     in use at exit: 0 bytes in 0 blocks
==27007==   total heap usage: 1 allocs, 1 frees, 3,072 bytes allocated
==27007== 
==27007== All heap blocks were freed -- no leaks are possible
==27007== 
==27007== For counts of detected and suppressed errors, rerun with: -v
==27007== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Command line: "one two three dude" entered for the valgrind below:
==27573== Memcheck, a memory error detector
==27573== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==27573== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==27573== Command: ./revecho one two three dude
==27573== 
dude
three
two
one

dude found
==27573== 
==27573== HEAP SUMMARY:
==27573==     in use at exit: 0 bytes in 0 blocks
==27573==   total heap usage: 5 allocs, 5 frees, 3,648 bytes allocated
==27573== 
==27573== All heap blocks were freed -- no leaks are possible
==27573== 
==27573== For counts of detected and suppressed errors, rerun with: -v
==27573== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
