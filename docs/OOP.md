# Object Oriented Programming.

In simple-lang, object oriented programming is practiced. Certain `OOP` techniques are practiced in this such as:

- Inheritance
- Polymorphism
- The use of `self ` and `this`.

## Classes.

`Classes` are th e foundation of Object Oriented Programming, in simple-lang, `classes` are defined like this: the `class` keyword followed by the class name with the methods and statements, enclosed in curly braces as show below:

```

# Defining an empty class.

class Empty {

}

# Defining a class that has a method.

class pack {

	block packer() {
	    display "initial module "+crlf
	}	

}


```

## Inheriting classes.

Variables can inherit classes and their method by using the `new` keyword follow by the class name. E.g

```

# WITH REFERENCE TO THE DEFINED CLASS PACK ABOVE.

    test = new Pack

    

```