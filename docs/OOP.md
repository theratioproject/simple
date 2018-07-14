# Object Oriented Programming.

In simple-lang, object oriented programming is practiced. Certain `OOP` techniques are practiced in this such as:

- Inheritance
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
    display test.packer() # displays "Initial module"

```

## Inheriting classes that take-in parameters.

From the previous chapters, we've seen the declaration of   `List` and it follows the inheriting of class but with parameters and the question arise - how is that possible ?

To accomplish that, a similar block is defined: Let's define a class example that exhibits the above said:

```

class List
    list = []

    block List(List)
        List = list
        return List

    block keys()
        display list

end

```

The above class defined, takes in a parameter upon inheriting it. Example:

```
WITH REFERENCE TO THE ABOVE DEFINED CLASS.

myList = new List(["a", "b", "c'])

myList.keys() # displays a b and c.

```

The above is possible because a function with the same class name is defined and is responsible for the actions of the arguments / parameter passed through it.

## The use of `this` and `self`.

`this` is used to refer to methods defined under a class.  Let's see an example:

```

	ocean = new Ocean
	ocean.displayFish("tuna")

class Ocean

	fish = "titus"

	block displayFish(fish)
		? "The paramic fish is : "+fish
		? "The self fish is : "+self.fish
		this.thisBlock()

	block thisBlock()
		display "we called an internal block with this"

```
The above example, is a  `class` named **Ocean** which has two methods: `displayFish(fish)` and `thisBlock()`. In the `displayFish(fish)` block, it takes a function parameter (fish) that is passed to it when a new variable inherits it.

### The `this` method.

This method, is used to refer to a block within a class instead of calling the block.  The use of `this` will be useful in building complex simple programs.

### The `self` method.
This is used to refer to a variable declared outside the function. In the `displayFish(fish)` function, `self` is used as:
```

self.fish # this displayed The self fish is Titus
                        # whereas titus is defined
                        # outside the function and not
                        # the parameter passed through the function.

```
 
 The `self` keyword is useful to differentiate variables which have the same names. It's sole purpose is to avoid confusions when building certain programs such as modules.

 ## The `pri vate` block.
 
 The `private` block in a class is a part of the class that cannot be accessed anywhere outside the class. Example:

 ```

 i = new inPrivate
 i.noteller # No error.
 i.teller() # Error occurs.

class inprivate {

	block noteller(){
		display " this is no private "
	}

	private block teller(){
		display " error will surely occur "
	}
	
}


 ```
 
 This blocks are useful when building certain modules that requires certain variables or constants that shouldn't be accessed from the inheriting varibale.

## Extending classes.

In simple-lang, class also extend each other. This is done by placing a colon __:__ 