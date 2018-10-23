# Emerald spec

## TOC
* Basics
* Functions

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

Modules are collections of functions
```

```
