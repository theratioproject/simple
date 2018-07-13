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