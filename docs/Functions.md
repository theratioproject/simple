# Functions.
Functions are parts of the  building blocks for simple-lang. They are set on instructions enclosed in a block that can be called anywhere in it's parent program / file.

```

block sayHello()
    display "Hello !"
end

```
---

Functions are defined with a prefix `block` followed by the function name with a bracket which  can either have parameters or not. The above function can be called to render its value by calling it elsewhere. E.g:

```

sayHello() # displays "Hello !"

```

## Functions with parameters.

Parameters in function blocks, are passed through when the function is called. Let's define a function that takes in a name as an argument and displays it:

``` Name.sim -  Display name.

block main()
    Greet("Abdul")
end

# Define block Greet
block Greet(name)
    display "Greetings " +name+crlf
end

```
 Running the above examples gives out "Greetings Abdul". 