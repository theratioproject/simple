# Low And High Level Ordered Variables.
Declaring variables is easy but what are Low and High level ordered variables ?. I'll break the mystery. First let's discuss the declaration techniques.

In simple-lang, we can declare strings and lists in two ways: either by using the normal declaration method ( traditional method ) or declaring variables from their parent classes. In a nutshell, there are two methods for declaring variables: traditional method and inheriting class. Let's look at an example:
``` Declaring a String and List traditionally.
# Let's declare a string traditionally.

name = "Simple-lang"

# Let's declare a list traditionally.

myList = ["code", "eat", "read", "hack"]

```

``` Declaring a string and List by inheriting parent classes.
call "simple/core/String.sim"
call "simple/core/List.sim"

# declare string.

name = new String("simple-lang")

# declare a List.

myList = new List(["s","i","m","p","l","e"])

```

> Note that String and List module have been placed in the core module folder as they are simple-lang's core modules.

## Low Level vs High Level Order.
Low level declaration looks more easy but is limited. Variables declared using the low level method, are limited to functionalities as they can't exhibit normal operations like `toUppercase` etc. 

Variables declared using the high order technique on the other hand, are open to various methods embedded to parent class. For example, a list variable declared using the high order technique exhibits function like adding, removing, reversing and slicing etc while low level declared are not open to any function.

### When to use either technique ?
Low level techniques, should be used only for basic programs e.g simple programs, guess games etc. While High level order technique on the other hand, should be used for writing better, complex simple-lang programs such as modules, packages, enviroments etc. High level ordered variables, are safely typed and have little / no risks as they cannot be manipulated easily.

## Reference.
In order to have a nicer view of this chapter, it'll be nice to check out the GitHub issue where changes were made and decided [here](https://github.com/simple-lang/simple/issues/15).