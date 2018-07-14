# List.

A list is a data type that holds variables of all type be it character, string, function, number etc. The members of this data type are enclosed in `[]`. They have the same functions / features as Arrays have in JavaScript. Example of a List:

```

myList = ["bread", "jam", "egg"]

display myList # bread, jam and egg.

```

## Declaring List.
As earlier discussed in [Low and High ordered variables](Low and High ordered variables.md), we can declare List in two ways but in this chapter, we'll be discussing `Lists` declared from parent class. We'll also discuss the methods attached to them.

Before we dive deep, let's list the basics methods attached to the `List` data type:

- .push()
- .pop()
- .reverse()
- .indexOf()
- .slice()
- .keys()
- .length()

``` Declaring a new List.

# Remember to call the List module.
call "simple/core/List.sim"

myList = ["bread", "jam", "bacon", "eggs"]

```
The above is our declared List which we'll be using to showcase the methods attached to the `List` data type.

### Adding a new value to the List using `.push()`.

To add a new value to the `list`, we use the method `.push(x)`, where `x` is either a boolean, number, function, array or string. Let's test this:

```

call "simple/core/List.sim"

myList = ["bread", "jam", "bacon", "eggs"]

# To add butter to the list, we do that using the .push() method.

myList.push("butter")

display myList # bread, jam, bacon, eggs, butter.

```

### Removing a value from the list using the .pop() method.
To remove the value from an array, we must know the `indexNumber` of the value to be removed.

> Note that index numbers of lists start from 0.

Assuming, we want to remove *bacon* from our list, we execute that by passing the `indexNumber` as an argument in the `.pop()` method.

``` Removing bacon.

call "simple/core/List.sim"

myList = ["bread", "jam", "bacon", "eggs", "butter"]

# Removing bacon where the index number is 2.

myList.pop(2)

display myList # bread, jam, eggs, butter.

```

### Reversing the List using the `.reverse()` method.
When we say  reversing a list, we actually 