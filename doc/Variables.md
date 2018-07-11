# Variables.
Variables are  placeholders for values which can be strings, array / List, number, boolean etc.

## Declaring varibles in simple.
In SIMPLE, variables are defined without any prefix. I mean, we don't have to add a prefix like JavaScript's`let` or C's `int` etc. We have different variable types or do I say data structures that enable us determine the type ofvariable we're declaring. We have:
+ string
+ number
+ List
+ boolean
Below, is a code block that shows the variable declaration of all listed variable types.
```
name = "SIMPLE" # String variable declaration.
age = 1 # Number variable declaration.
List = ["s", "I", "M", "P", "L", "E"] # List type declaration.
fake = False # boolean.
```
The above declaration methods for variables are referred to as low-level variable declaration. These are limited to certain functionalities and method.

## Declaring variables in higher-level order.
The string declared in a low level order, has no functionality but the one declared using the high-order method.
```
# Declaring string using the higher-level order.
name = new String("Abdulazeez") # This is more secure and matured.
list = new List(["s","i","m","p","l","e"])
```
> Note that, variable declared using the new* classical method are open to certain functions. The list can add a  new  value using the .pop() method bit cannot do that when declared in a low-level style.
## Some String methods.
To use strings declared by high-order style, we need to know the various methods attached to them. Let's check them out.
The code block below shows some String methods in action:
```
# Call modules needed.
call "simple/core/String.sim" 
call "simple/utilities/Console.sim" ? simple.utilities

	string = new String("mOduLArity ") # Declared a new string.

block main() {
	Console.println(string.toString()+" | LOWER : "+string.toLower()) # Turns string casing to lower.
	Console.println("UPPER : "+string.toUpper()+" | SENTENCE : "+string.toSentence()) # Turn string casing to uppercase.
	Console.println("LENGTH : "+string.length()+" | Char at 3 : "+string.charAt(3)) 
	if string.isEmpty() Console.println("The String is Empty") 
	else Console.println("We cool, "+string.toString()+" is not empty") end
	if string.equals("modular") Console.println("yea they are equal") 
	else Console.println("Nope They are not equal") end
	if string.compareTo("modular") Console.println("yea they are equal")
	else Console.println("Nope They are not equal") end
	if string.startsWith("mod") Console.println(string.toString()+", start with mod ")
	else Console.println(string.toString()+" does not start with mod but with 'mOd'") end
	Console.println("FIRST CHAR : "+string.firstChar()+" | LAST CHAR : "+string.lastChar())
	Console.println("HASHCODE : "+string.getHashCode())
	Console.println("LEFT : "+string.left(6)+" | RIGHT : "+string.right(3))
	Console.println("TRIM : >"+string.trim()+"< | COPY : "+string.copy(2))
	if string.endsWith("rity ") Console.println("yea it ends with 'rity '") end
	Console.println("LINE COUNT : "+string.lineCount()+" | SUBSTRING : "+string.subString("d"))
	Console.println("REPLACE : "+string.replace("OduLA", "odula")+" | REMOVE : "+string.remove("ity "))
	Console.println("TYPE : "+string.getType()+" | TYPECODE : "+string.getTypeCode())
	Console.println("CONCAT : "+string.concat("and complexity"))
}
```