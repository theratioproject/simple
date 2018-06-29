# SIMPLE LANGUAGE MINI TUTORIAL TO GET YOU STARTED

Developed By Azeez Adewale
Tutorial By Busari Habibullaah 
Edited by Abdulazeez Abdulazeez Adeshina


##  Introduction

Simple is a mini Language, developed as a project during the year 2017, it is still evolving, it is not strongly Typed like C, 
C++, or Java. It extensively support Object oriented programming. It was created as simple to understand programming language, 
even simpler than python and other simple languages. Expereienced programmers should be able to adapt to most of the eamples 
in these tutorial,beginner programmer should read the pages line by line to fully understand the language. 
                                                                                                    Busari Habibullaah.


## Getting Started
I believe to understand how to write a programming langauage, you must read and write it. The first
program to write is the same for all languages:

Hello World!

If you were able to write and run the First Programe successfully, you should not have problems 
running the rest of the codes in following chapters.

```
block main() 
	display("Hello World!"+crlf)
```

This simple code will print out:
Hello World!
Simple functions are like the subroutines, methods, procedures in other programming languages. 
Main will call other functions to help perform its job, some that you wrote, and others from libraries that are provided for you.

The above program could be re-written like this:
```
block main()
     display(“Hello” + crlf)
     display (“World! + crlf)
```
Or it could siply be written as:

display "Hello World!"

where **crlf** are optional. cr means Carriage Return while lf means Line Feed, both cr and lf are escape sequence which makes 
the program output more readable.There is no need for excessive braces but it makes the code more readable.

Variables Declaration
This program claculate and prints a table of farenheit temperatures and their centigrade or celcius eqivalent.

 ```
lower = 0;
upper = 300;
step = 20;
fahr = lower;

for i = lower to upper
      celsius = 5 * (fahr-32) / 9;   
      display  fahr, + celsius + crlf
      fahr = fahr + step;
end
```
Simple provides no real data types, therefore prefixing data types before your varible declaration is not needed otherwise it 
returns unexpected result. The  most basic example of declaring and assigning values to a varible in simple is: 
```
lower = 0;
upper = 300;
step = 20;

fahr = lower;
step = fahr;
```

Note: you will not declare variables surplus of requirement, programmers familiar with python programming should understand this 
clearly. You declare on the go pattern, as needed.


## Conditional Expressions

### If-Else

The if-else statement is used to express decisions. Formally the syntax is
```
              if (expression)
                          statement 1
                    else
                        statement 2
```
where the else part is optional. The expression is evaluated; if it is true (that is, if expression
has a non-zero value), statement 1 is executed. If it is false (expression is zero) and if there is an
else part, statement 2 is executed instead.
```
if ( n == 20 && n > 12) 
	display "  holla it twenty and greater than 12" + crlf
else 
	display "  i dont know" + crlf
end
```


### ElIf

This sequence of if statements isthe most general way of writing a multi-way decision. The expressions are evaluated in order. 
If an expression is true, the statement associated with it is executed, and this terminates thewhole chain. As always, the code 
for each statement is either a single statement, or a group of them.

The construction
```
         if (expression)
                  statement
             elif (expression)
                   statement
            elif (expression)
                   statement
            elif (expression)
                  statement
           else
                  statement

if ( n < 1 )
	display "  yea n is " + n + " and is less than 10" + crlf
elif ( n == 1 )
	display "  n is 1 " + crlf 
elif ( n > 10 )
	display "  well you inputed " + n + " which is greater than 10" + crlf
	n = 34
end
```



### Switch

The switch statement is a multi-way decision that tests whether an expression matches one of
a number of constant integer values, and branches accordingly.
```
              switch (expression) 
                    case const-expr
          statements
                     case const-expr
          statements
                    default
         statements
```
Each case is labeled by one or more integer-valued constants or constant expressions. If a case
matches the expression value, execution starts at that case. All case expressions must be
different. The case labeled default is executed if none of the other cases are satisfied. A
default is optional; if it isn't there and if none of the cases match, no action at all takes place.
Cases and the default clause can occur in any order.

```
switch (n) 
	case 2
		display "it is two"
	case 3 
		display "it is three"
	default
		display "i dont know but it "+n
end 
```


### Loops - While and For

#### The While Statement

while (expression)
statement

The expression is evaluated. If it is non-zero(True), statement is executed and expression is re-
evaluated. This cycle continues until expression becomes zero(false), at which point execution
resumes after statement.
```
while n < 10  
	display " "+n + " "
	n++
end

while ( n <= 100 ) {
	display " " +n + " "
	n = n + 10
}

display "Simple " + getSimpleVersion() + crlf
display "REPL (Read-Eval-Print-Loop)" + crlf
while true
        display crlf + "simple:> "
        read code
        try
                executeCode(code)
        catch
                display __err__
        end
end
```




#### The For Statement
```
              for index = Start to Stop


    start = 2
    stop = 10
    for a = start to stop step 2
	display crlf + a
  end

     for n in [ 1, "four", 6, 5 ] {
	display "number "+n+" "
     } 

     rows = 20
      n = 0
   for r = 1 to rows   
    for c = 1 to r  
        n = n + 1
        display n + " " 
    end display crlf
end

```

#### Do-While

The while and for loops test the termination condition at the top. By contrast, the third loop in C, the do-while , tests at the
bottom after making each pass through the loop body; the body is always executed at least once. The syntax of the do is
```
              do
                statement
            while (expression);
```
The statement is executed, then expression is evaluated. If it is true, statement is evaluated
again, and so on. When the expression becomes false, the loop terminates. Except for the sense
of the test, do-while is equivalent to the Pascal repeat-until statement.


```
do {
	display " "+n + " "
	n++
} while  n < 10 
```




#### Break and Exit
It is sometimes convenient to be able to exit from a loop other than by testing at the top or
bottom. The break statement provides an early exit from for , while , and do , just as from
switch . A break causes loop to be exited immediately. The __exit__ keyword is used to stop the program at any point.
```
n = 40
display "n is " + n + " "

for i = 0 to n
	display i + " "
	break
end
__exit__
display "you cant see me"
```

## Block and Program Structure

Block in simple are like Function in C or C++, Methods in Java and all other programming languages using block break large tasks 
into smaller ones, and enable programmers to build on whatothers have done instead of starting over from scratch. Using block 
hide details ofoperation from parts of the program that don't need to know about them, thus clarifying thewhole, and easing the 
pain of making changes.

```
block mainone() {
	return 1021 ;
}

block maintwo(one, two) 
	return one * two ;
```

Using block you can choose to return or not to return any value. Instead of using the the void type for the non-return functions 
in C, and Int or other fundamental data types in other strongly typed programming languages to return.

## The Call Statement

 The call statement in simple works just like the import statement in java, include file in C or C++.
```
call "module.sim"
call "block.sim" 

i = new inner
i.miner()

display i

#3

display "hello : "+maintwo(9, mainone()) + crlf 
```


## Class

contain data and procedures (known as class methods) themselves, i.e. classes contain the data members and member functions
```
class Empty {

}

class pack {

	block packer() {
		display "initial module "+crlf
	}	

}
```


## List
This data type is the same as the **javascript** *array* and **Python's** *list*. The List houses a lot of methods: A list can be defined in two ways:
### 1. Defining a List without access to it's method.
This basically means defining a list like this;
```
myList = ["a", "b", "c"]
```
### 2. Defining a List with access to it's method.
A list is defined in this method by creating it from a class. The List that houses all it's method has been built into a **MOdule**. To define a list and explore it's function, do it as follows:
```
call "simple/core/List.sim"

myList = new List(["a", "b", "c", "d", "e"])
```
A lot of method are embedded and can be performed on list built using the above style. Such methods include:
+ .push()
* .pop()
- .slice()
* .reverse() 
+ etc..

More examples can be found [here](https://github.com/simple-lang/simple/examples)