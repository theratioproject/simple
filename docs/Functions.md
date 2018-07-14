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

# Main block 

block main()
    Greet("Abdul")
end

# Define block Greet which takes name as an argument when the function is defined.

block Greet(name)
    display "Greetings " +name+crlf
end

```
 Running the above examples gives out "Greetings Abdul". 

 ## The `main()` block.
 In the previous example above, we defined a block `main()`. The block `main()`, is a block that should be defined when building certain programs. The `main()` block is responsible for rendering