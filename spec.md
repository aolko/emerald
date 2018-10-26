# Emerald spec

## TOC
* Basics
* Modules
* Control structures
* Arrays and hashes


## Basics

### Comments
```
# this is a single-line comment
// as well as this
```

```
/*
	This is a multi-line comment
*/
```
```
/#
	this one is also possible
#/
```
### Variables

```
variable = 1
also_a_variable = "text"
Юникод = "text"
```
Unicode variables are a thing as well (everything is in utf-8mb4).
Want a sigil (`$`)? Psyche, there's none! Oh, wait. That's a global variable one.
```
$global_variable
```

### Functions
```
fn Function(variable,anotherVariable):
	echo variable + anotherVariable 
end
```
```
Function(2,3)
#=> 5
```
### Output
You can print to the output with a newline at the end
```
echo "I'm printing!"
#=> I'm printing!
#=> nil
```
...or print to the output without a newline
```
print "I'm printing!"
#=> "I'm printing!" => nil
```

## Math

### Arithmetic
```
1 + 1
2 - 1
3 * 5
40 / 8
2 ** 5
5 % 3
```

### Bitwise
```
3 & 5
3 | 5
3 ^ 5
```
```
nil
true
false
```
### Comparators
```
1 == 1 #=> true
2 == 1 #=> false
1 < 10 #=> true 
1 > 10 #=> false
2 <= 2 #=> true
2 >= 2 #=> true
```
**`<=>`** returns `1` when the first argument is greater, `-1` when the second argument is greater, otherwise `0`
```
1 <=> 10 #=> -1 (1 < 10)
10 <=> 1 #=> 1 (10 > 1)
1 <=> 1 #=> 0 (1 == 1)
```
### Logic
```
true && false #=> false
true || false #=> true
# -or-
# `do_something_else` only called if `do_something` succeeds.
do_something() and do_something_else()
# `log_error` only called if `do_something` fails.
do_something() or log_error()
```
You can also join strings
```
'hello ' + 'world'  #=> "hello world"
'hello ' + 3 #=> TypeError: can't convert Fixnum into String
'hello ' + 3.to_s #=> "hello 3"
"hello {3}" #=> "hello 3"
```
 ...or combine strings and operators
```
'hello ' * 3 #=> "hello hello hello "
```
 ...or append to string
```
'hello' << ' world' #=> "hello world"
```


## Modules

Modules are collections of functions and variables
```
module "MyModule"

fn Hi(Thing):
	echo "Hi, {Thing}"
end
```
```
import "MyModule"

MyModule.Hi("World")
#=> Hi, World
```

You can also namespace your modules
```
Module "MyModule.Math"

fn Add(num1,num2):
	echo num1 + num2
end
```
```
import "MyModule.Math"
Add(3,3)
#=> 6
```

## Control structures
### Conditionals

```
if condition:
	#action
elsif otherCondition:
	#another action
else:
	#another action
end
```
 ### Repeats/Loops
 Repeat a function 5 times
```
5.times do:
	fn() 
end
```

Repeat a function forever
```
forever.times do:
	fn()
end
```

```
for counter in 1..10 do:
	echo "#{counter}"
end
```

```
counter = 0
while counter <= 5 do:
	echo "#{counter}"
	counter += 1
end
```

## Arrays and hashes
### Arrays
Arrays are used for simple enumerations
```
["i'm","an","array",1,2,3]
#=> ["i'm","an","array",1,2,3]
```

### Hashes
Hashes are dodgy key/value pair dictionaries, look at their mustaches
```
{"well"=>"i'm","a"=>"hash"}
#=> {"well"=>"i'm","a"=>"hash"}
```
