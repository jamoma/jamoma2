# Jamoma2 Coding Guidelines

The Jamoma codebase has a very strict and consistent coding style.
This is important to maintain so that code contributed by many authors will be easily understood, debugged, and maintained as if it were written by a single author.

These rules are largely taken from the [Juce Coding Standards](http://www.juce.com/learn/coding-standards) though there are some deviations.

## General Coding Principles

* **Don't Repeat Yourself** -- Every piece of knowledge must have a single, unambiguous, authoritative representation within a system.
* **Don't Use Pointers** -- Jamoma2 aims to eliminate ambiguous responsibility for resources (memory, files, etc), and error-prone idioms are discouraged. As such, using raw pointers is highly discouraged. Instead use a managed construct such as a class that contains an STL smart pointer.  As a consequence, **never call `new` or `delete` or `malloc` or `free` etc...**.
* **const** : Be intentional about const always. If it can be const, make it const. Even local variables. Prefer const ref arguments where practical.  Don't return const temporaries.  see  [JUCE guidelines](http://www.juce.com/learn/coding-standards)
* **use override and noexcept** : see [JUCE guidelines](http://www.juce.com/learn/coding-standards)
* Give variables as localized a scope as possible
* Prefer stack allocation to heap allocation
* **Avoid raw loops** -- Here is a [video](https://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning) on the subject.

## Formatting and Whitespace

* **Header Guards** -- All headers must be guarded to prevent multiple inclusion. Preferably using `#pragma once`.
* **Prefer Tabs** -- Don't indent with spaces where a tab will work. 1 tab = 4 spaces.
* **Braces** -- [Stroustrup Style](https://en.wikipedia.org/wiki/Indent_style#Variant:_Stroustrup) -- meaning closing braces on their own line but opening braces on the same line as the identifier for the block.  There may be exceptions if it increases clarity (e.g. constructors with initializer lists)
* **Hugging** -- pointer or ref designation hug the type not the var identifier, e.g. `MyType* foo = nullptr;` 
* **Variables** -- one per line only.  Preferably initialized.  (same as JUCE guidelines)
* **Variables** -- blocks of variable definitions should use tabs to align the variable names.
* **Commas** -- Never put a space before a comma. Always put a space after a comma.
* Do not put a space before an open parenthesis
* Do not write 'if' statements all-on-one-line. Except when you've got a sequence of lines containing similar if statements, and are aligning them all vertically to highlight their similarities.
* Do not use braces on one-liner if-statements (unless it improves clarity, e.g. in multiple nested one-liners)
* **Initialization Lists** : lists, including the leading colon, begin on a new line.  Each succeeding member in the list go on a new line with a leading comma.
* **Class Organization** : data members at the top (like you do for blocks in C) and then methods below.  Try to minimize switching between `private`/`protected`/`public` a lot by grouping things together.  Prefer to go from `private` to `public`, but this is not a hard-and-fast rule.
* **Prefer preinc/predec** -- e.g. `++i` or `--i`.
* Prefer a line of whitespace after variable declarations and before computation/logic.
* Prefer a line of whitespace before and after one-or-more assert/static_assert statements.

## Naming Conventions

* **camelCase** -- for variables and member methods.
* **CamelCase** -- for types/classes as well as free-standing functions.
* **Underscores** -- don't do it. Avoid underscores in your names, *especially* leading or trailing underscores.
* * **Macros** -- generally avoid, but if you must, name it using ALL_CAPS_WITH_UNDERSCORES
* Additional conventions:
 	* **varName** -- local variables, or public members of a class (e.g. parameters)
 	* **mVarName** -- members (non-public)
	* **kVarName** -- constants
	* **sVarName** -- statics (rare)
	* **gVarName** -- globals (exceptionally rare)
* **Enums** -- use camel-case with the same capitalization that you use for a class and its member variables (enum is CamelCase, members are camelCase)


## Optional / Things to Consider

JUCE suggests the following:

* Constructors that take a single parameter should be default be marked 'explicit'. Obviously there are cases where you do want implicit conversion, but always think about it carefully before writing a non-explicit constructor.
* Never put an "else" statement after a "return" -- The [LLVM coding standards](http://llvm.org/docs/CodingStandards.html#don-t-use-else-after-a-return) give a good explanation of this.



