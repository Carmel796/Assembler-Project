Labratory in C - 20465 (2024B) : Open University

This is my final project of the course Labratory in C - 20465 (2024B) in the Open University,
The program purpose is to convert Assembly-Like language to Machine-Language using C language.

Using these 3 parts the program creates 4 output file: .am, .ob, .ent, .ext:
- pre_processor: responsible for creating the .am file after all macro interpretation;
- first_pass: ( the big boy (: ) responsible for adding symbols detected in the am file into Hash-Table Data Structure, and handaling encoding of all the lines he is able to into "Words".
- second pass: responsible for encoding all the "Words" first pass was not able to.


.am file - the file created after macro interpretation in the pre_processor;
.ob file - the Machine-Language file created as the main progrm output, having the memory address of each "Word" and its octal presentation;
.ent file - holding address of symbols which defined as .entry;
.ext file - holding address of symbols which defined as .extern;

- Carmel Cohen - 
