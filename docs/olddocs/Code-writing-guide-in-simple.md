# A detailed guide to writing SIMPLE codes.
Writing simple codes is simple just as the name implies. SIMPLE doesn't mind whitespace and indentations but as a neat developer, you should indent your work to make it look pretty.

## Comment style.
Most SIMPLE codes do have comments at the top of the file indicating the description and purpose of the code written below.
#### Inlime comments.
This type of comment is written on a single line.
To write an inline comment in SIMPLE, a *hash* **#** is used to denote inline comments. e.g
```
# This is an inline comment.
block main 
    display "Hello world!" +crlf
```
#### Block comments / Large comments.
This comments are those that entails large description. Example:
```
/*
This is a large comment
In this example, we'll be writing an empty class 😁.
Written on the 7th of April.
*/
class Empty {
    # This is an empty class.
}
```

Okay, we're done discussing the comment styles used in SIMPLE as that's the first thing.

## Syntax Guide.
In this section, the guides on writing clean and readable code are disbursed below 😄.

### Indentation.
Indentation in SIMPLE isn't a problem but to make code easier to read, indentation is needed. To indent a program in SIMPLE, a tab or 4 spaces is all that is needed. Example:
```
# Indentation example.
block main
    display "Properly indented"
end
```
### Comment Map.
For every program written, comments are needed to give details of the program. There are different styles of commenting on a program but these are the ones used mostly in SIMPLE.
```Comment style one.
/* 
	Copyright (c) 2018 Abdulazeez Abdulazeez <laisibizness@gmail.com> 
	MIT License Copyright (c) 2018 simple 
*/
That comments indicate the name, email and it is open source (MIT License).
```
```Comment style two
/* 
 * #filename - ConsoleColor.sim
 * #author - Azeez Adewale
 * #date - 11 Febuary 2017
 */
 Indicates the file / program name, author's name and date written.
```
``` Comment style three
/*
    comment map
    -------
    #author - [[Abdulazeez Abdulazeez Adeshina][twitter]]@kvng_zeez
    #date - April 4 2018
    #name - Length.sim
    #detail - A module used in getting the length of strings.

*/
```
ANy of the aboved comment style can be used when writing programs.

## Casing.
SIMPLE supports the basic casing styles we have but we use the pascal and camel casing styles.

## Variable declaration.
Names of declared variables should be simple and short. Example
```
# Good variable declaration
name = "Abdul"
# Bad variable declaration
isLoadingCurrentlyOrNot = true
```

## Module naming convention.
Modules are the building blocks of SIMPLE. A module can be written but naming matters. Example:
```

#1
module simple.utilities

#2

#3
    block getTypeLength(object)
    if (isList(object) || isString(object))
        return lengthOf(object)
    elif (isNumber(object))
        return object
    end

/*
    comment map
    -------
    #author - [[Abdulazeez Abdulazeez Adeshina][twitter]]@kvng_zeez
    #date - April 4 2018
    #name - Length.sim
    #detail - A module used in getting the length of strings.

*/
```
The module above is named according to the folder it is found - **simple.utilities**.
Need a guide on writing modules ?. Check [this](Simple-Mini-Tutorial-v1.0.md)

## Wrapping up.
This basically comes to the end of the guide, more content will be added as SIMPLE expands.