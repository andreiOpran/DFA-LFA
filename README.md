# Deterministic finite automaton Emulator

<br>

This C++ project is designed to validate and process inputs for a Deterministic Finite Automaton. It reads a DFA
configuration from a text file, which includes states, transitions, and alphabet, then verifies if a given word is accepted
by the automaton. The program provides error handling for missing files, validates file contents, and allows users to
test multiple inputs interactively.


<br>

## Formatting Rules for the Input Text File:

- The alphabet can only contain letters of length 1, because when processing the string to be checked, it is processed letter by letter.
- The alphabet cannot contain "Q".
- States must be in the format "QX F S", where X is any number, and "F" and "S" may be omitted but must appear at least once in the states section.
- Transitions must be in the format "QX L QY", where L is a letter from the alphabet, and QX and QY are states from the states section, which can be identical.
- A section begins with "SectionHeader:" where "SectionHeader" can be any string, and after the data is entered according to the above format, the last line should contain "End".
- Comments are marked with "#" at the beginning of the line.
- The alphabet, states, and transitions can be entered in any order, but each can only appear once.




<br>

## Example of an input file:

<br>

\#  
\# comment lines (skip them)  
\#  
Sigma:  
0  
1  
End  
\#  
\# comment lines (skip them)  
\#  
States:  
Q1  
Q2 F  
Q3 F S  
Q4   
End  
\#  
\# comment lines (skip them)  
\#  
Transitions:  
Q1 0 Q2  
Q2 1 Q3  
Q2 0 Q2  
Q4 1 Q3  
Q3 0 Q4  
End  
