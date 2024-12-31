# Automato theory🍅  
These are my labs from MEPHI automato theory course.  

# Labs descriptions  

## lab1  
This was just to become familiar with flex framework, SMC tool and regular expressions.    

![image](https://github.com/user-attachments/assets/1259c06d-7e74-4ebb-aa51-8b3c61f383b4)

## lab2  
Self-written regex library that allows not only constructing automatos from regexes, but also add them, subtract them and ofcourse match against string.  

![image](https://github.com/user-attachments/assets/942c077b-6fc3-4b3c-ae51-a1380b7a14e8)

## lab3  
My own programming language. It has quite limited syntax, but that was enough to make a mini game about robot escaping labirint in this language. Grammar and parser were written using flex and bison libraries.  

![image](https://github.com/user-attachments/assets/e00f70e0-d77c-4016-83f1-9fc9dfdd9334)
![image](https://github.com/user-attachments/assets/31dd9089-9815-4249-b25e-f95e1831811b)

### How to build and use interpreter for this language?  
Firstly, build target ```test``` with ```Makefile``` presented in ```lab3``` directory.  
Then, in order to run interpreter in console mode simply run  
```console
$ ./test
```
In order to interpret code from file call the following command:
```console
$ ./test cool_code_file.boba
```
> .boba extension is actually optional, you can load there any file

### How to get familiar with syntax?  
There are several example programs provided in this repository such as:  
[binary_number.boba](https://github.com/kargamant/automata_theory/blob/main/lab3/binary_number.boba)  
[fibonnachi.boba](https://github.com/kargamant/automata_theory/blob/main/lab3/fibonnachi.boba)  
[geometric_progression.boba](https://github.com/kargamant/automata_theory/blob/main/lab3/geometric_progression.boba)  
[number_reverse.boba](https://github.com/kargamant/automata_theory/blob/main/lab3/number_reverse.boba)  
[power_of_ten.boba](https://github.com/kargamant/automata_theory/blob/main/lab3/power_of_ten.boba)  
and many more...  

### What is a mini game with robot?  
This is a little extension of a language that allows to interact with robot and labirint.  
As an example, there is a program that implements A-star path-finding algorithm for robot to find exit from labirint.  
⭐ [a_star.boba](https://github.com/kargamant/automata_theory/blob/main/lab3/a_star.boba)  
  
If you want to set your own labirint you just need to change name of file given to Map class in ```compile_vars.h``` file:  
https://github.com/kargamant/automata_theory/blob/c0430b6231313825a00a75f29cd6e41789534059/lab3/compile_vars.h#L3  


