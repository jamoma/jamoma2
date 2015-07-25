# jamoma2
A header-only C++ library for building dynamic and reflexive systems with an emphasis on audio and media.




## Idiomatic SampleBundleGroup Usage

* FFT -- one bundle of reals, one bundle of imaginaries -- This way the graph stays the same regardless of changes to channel counts.  Also algorithms (e.g. multiplying the two )


## Golossary

* Sample
* SampleVector
* SampleBundle
* SampleBundleGroup

* Immutable -- what does this imply?
* Shared -- what does this mean?

etc.



## Class Construction

* Parameter -- was "attribute"
* Message
* Notification -- was "return"



### Code Style

We use **camelCase** for variables and **CamelCase** for types.

* kVar -- constant
* gVar -- global
* mVar -- members of a class which are non-public
* var -- local (to a method), or public members of a class (e.g. parameters)
* 



## Notable Shifts in Thinking from Jamoma1

### DSP Calculation

Back in the PPC processor days we paid a very heavy penalty for branching instructions in the code. As such the original JamomaDSP (or TTBlue as it was then called) went to extreme lengths to optimize by eliminating such branching.  In the case of the DSP calculation routine this meant that we wanted to avoid `if/else` clauses and we did so by creating separate calculation routines and pointed to the routine we wanted by calling through one or more function pointers.

The branching penalty on contemporary processors is not nearly so severe. Furthermore, the indirection through function pointers prohibits the compiler from inlining calls through the methods and thus levies a heavy performance penalty.  Now that we are working in a header-only environment this gains that can be had from radical inlining far exceed the cost of some occasional `if` statements.

As such, we now use simple methods (overloading the the `()` operator), which also yields the most direct, understandable, and elegant code.


