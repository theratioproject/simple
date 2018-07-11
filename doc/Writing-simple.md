# A detailed guide to writing SIMPLE codes.
Writing simple codes is simple just as the name implies. SIMPLE doesn't mind whitespace and indentations but as a neat developer, you should indent your work to make it look pretty.
## Comment style.
Most SIMPLE codes do have comments at the top of the file indicating the description and purpose of the code written below.
#### Inline comments.
This type of comments is written on a single line.
To write an inline comment in SIMPLE, a *hash* (#) is used to denote inline comments e.g
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
