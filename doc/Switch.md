# The Switch statement.
The switch statement, is a replacement for `if-else` statements. The switch statement reduces the numerous `if-else` statement that might occur in large apps. In a `switch` statement, there are two compulsory parameters: `case` and `default`. The case replaces the `if-else` statement and the `default` represents the final `else` statement. Let's glance through an example so as to better explain the syntax:
```
display "input your number : " read n 

switch (n) 
	case 2
		display "it is two"
	case 3 
		display "it is three"
	default
		display "i dont know but it "+n
end 

```
The above code example, displays **it is two** if the inputed value enclosed in n is 2 else displays **it is three** if the inputed value is 3 else returns a `default` message: **I don't know but it's " +n**.

If you observe, the above example can be re-written using the `if-else` syntax. 

## Use cases.
The switch statement is useful in deciding large datas. It can be used for building programs like grading systems etc. The `switch`