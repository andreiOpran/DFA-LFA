# Emulator DFA

<br>

## Reguli de formatare al fisierului text de input:

 - alfabetul poate contine doar litere cu o lungime egala cu 1, deoarece atunci cand parcurg sirul de verificat, il parcurg litera cu litera.  
 - alfabetul nu poate contine "Q".  
 - starile trebuie sa fie de forma "QX F S", unde X este un numar oarecare, iar "F" si "S" pot sa lipseasca, dar trebuie sa apara cel putin o data in fisierul de stari.  
 - tranzitiile trebuie sa fie de forma "QX L QY", unde L este o litera din alfabet, QX si QY sunt stari din sectiunea de stari si pot fi identice.  
 - o sectiune incepe cu "HeaderSectiune:" unde "HeaderSectiune" poate fi orice sir, si dupa ce se introduc datele conform formatarii de mai sus, pe ultima linie se introduce "End".  
 - comentariile sunt semnalate prin "#" la inceputul liniei.  
 - alfabetul, starile si tranzitiile pot fi introduse in orice ordine, dar pot fi introduse o singura data.  

<br>

## Exemplu fisier de input:

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
