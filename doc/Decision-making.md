# Decision making in simple-lang.
Decision making basically has to do with the `if-else` statement. The  `if-else` statement executes an action  based on the decision made e.g if I have more than 10 bucks, I'll get a software CD else I'll buy a sandwich. That's a simple demonstration. Let's glance through the syntax:

```
n = 9

if ( n < 1 )
	display "  yea n is " + n + " and is less than 10" + crlf
elif ( n == 1 )
	display "  n is 1 " + crlf 
elif ( n > 10 )
	display "  well you inputed " + n + " which is greater than 10" + crlf
	n = 34
end

```
In the above example, the first display statement is executed `if` n is less than 1 `elif` n == 1, the second display statement is executed else