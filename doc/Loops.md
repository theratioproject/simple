# Loops.
I don't think it'll be possible for a programming language to survive without a loop feature. In simple-lang, all loop types are practiced: do..while, for loops and while loop.
## For loops.
This is the basic type of loop and most commonly used one. It is used widely in Arrays and other scenarios where the need arise. Let's see how the syntax look like:

```
for # A condition passed,
    # Do something. 
end # Close loop.

<!-- The loop below displays  from 8 to 12.-->

for n = 8 to 12 
	display "number "+n+" "
end

```
The for loop statement looks quite different right ?. Well, the `to` word there is just a faster representation of this : `n < 12; n++` as we''ll have in other languages.

The `for` loop also has a feature that allows it to  jump / loop over a certain number e.g

```
for a = 2 to 10 step 2
	display crlf + a
end
```

The above example, loops even number from 2 to 10. This is possible using the `step` word in the loop argument. A little complex code will be required in other languages.

## The While loop.
Th e while loop, performs an action when a requirement is fulfilled. Let's view the syntax:
``` While loop

n = 1

while n < 10  
	display " "+n + " "
	n++
end

```
The above example, loops `n` while it's value is less than 10. The while loop can also have it's actions embedded in curly braces __({})__. This is only when a complex argument is passed or will have mu