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

## Modules

Modules are collections of functions and variables
```
module "MyModule"

function Hi(Thing):
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

function Add(num1,num2):
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
