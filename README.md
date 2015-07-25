# jamoma2
A header-only C++ library for building dynamic and reflexive systems with an emphasis on audio and media.





## Notable Shifts in Thinking from Jamoma1

### Fewer 'Amenities'

We've eliminated the inherited **bypass** for every object.
We've eliminated the inherited **gain** for every object.

These services are not free, not always appropriate, sometimes redundant, and better implemented on an as-needed basis in a way that is idiomatic to the algorithm at hand.

We have not discussed the **mute** option explicitly. In general the sentiment of the Florida workshop was that things like this are perhaps better left as a function of the graph instead of as baked-in to the unit generators themselves.

### DSP Calculation

Back in the PPC processor days we paid a very heavy penalty for branching instructions in the code. As such the original JamomaDSP (or TTBlue as it was then called) went to extreme lengths to optimize by eliminating such branching.  In the case of the DSP calculation routine this meant that we wanted to avoid `if/else` clauses and we did so by creating separate calculation routines and pointed to the routine we wanted by calling through one or more function pointers.

The branching penalty on contemporary processors is not nearly so severe. Furthermore, the indirection through function pointers prohibits the compiler from inlining calls through the methods and thus levies a heavy performance penalty.  Now that we are working in a header-only environment this gains that can be had from radical inlining far exceed the cost of some occasional `if` statements.

As such, we now use simple methods (overloading the the `()` operator), which also yields the most direct, understandable, and elegant code.




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

### Pointers

If you are using pointers, you are probably doing something wrong.

Jamoma2 aims to tighten areas where ambiguous responsibility of resources (memory, files, etc) is eliminated and error-prone idioms are discouraged. As such, using pointers directly is highly discouraged and places where pointers might be necessary should be done through a managed construct such as a class that contains an STL smart pointer.

Obviously we still need to interface with C code that will pass us pointers in some cases (such as getting samples from a sound card).


