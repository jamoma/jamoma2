# Jamoma2
[![Build Status](https://travis-ci.org/jamoma/jamoma2.svg?branch=master)](https://travis-ci.org/jamoma/jamoma2)

A header-only C++ library for building dynamic and reflexive systems with an emphasis on audio and media.

## How to Build

As a header-only library there is nothing to build for Jamoma itself. You only build your project that uses Jamoma.  You can investigate examples to build in the **examples** folder or build and run tests in the **tests** folder. To build everything, here are a couple of example console sessions:

### Building on the command line (Mac or Linux)

```
	$ cd jamoma2
	$ mkdir build
	$ cd build
	$ cmake ..
	$ make
	$ make test
```

### Building on a Mac using Xcode

```
	$ cd jamoma2
	$ mkdir build-xcode
	$ cd build-xcode
	$ cmake -G Xcode ..
```

Now open an individual Xcode project from `examples` or `tests`.  Alternatively open the Xcode project at the top level to build everything and run all unit tests.

If you don't have CMake you can get it from http://www.cmake.org/ .

## How to Contribute

Please read **Style.md** and contribute code that conforms to the style guidelines.  If your code does not match it will take longer for us to evaluate it and consider it for a possible merge.

You can send code in a variety of ways, but the preferred way is to do a **Pull Request** on Github.

## Why Are We Doing This?

Jamoma1 and its codebase have grown in a number of exciting and unanticipated directions over the past 10 years.  Additionally, the tools with which we build the codebase (C++11/C++14) and our understanding of computer science and best practices have shifted dramatically.

We desperately need an easier-to-maintain, faster-to-build, quicker-to-debug, and more readily understandable means of coding if we are to further expand the platforms and targets with which we work.

Furthermore, a number of difficult problems have dogged Jamoma1 for many years, leading to the conclusion that parts of the codebase such as the Graph/AudioGraph as they currently exist are dead-ends. These problems include a lack of thread-safety which leads to e.g. audio anomalies that occur only occasionally and are rarely reproducible. We also have complex problems with race conditions leading to both deadlock and memory leaks, especially in the AudioGraph.


## Notable Shifts in Thinking from Jamoma1

### No Symbol Table

Symbols in Jamoma1 were implemented as a string and a compound identifier that reduced comparisons between known symbols to 2 integer comparisons.  This speed improvement was sometimes realized, but typically we ended-up doing lookups into the std::unordered_map prior to doing the comparisons themselves.  Worse, the symbol table could be accessed from multiple threads, so it used mutexes.  In audio perform routines checking the equivalent of an enum (1 int comparison with no mutexes or lookups) this was a big price to pay.

When sending a message, or attribute change, by name the receiving object has to compare the name sent in against a reference name. With a symbol it compares 2 ints or it hashes a string. With static linking in C++ in Jamoma2 you never do this. A dynamic class wrapper would still do this, but the Max class wrapper as it exists is not using cached Symbols generally anyway -- see filter_setFrequency() in j.filter.cpp as an example. So we don't lose much...

For lookup to create a new instance through the factory for new objects. currently this factory isn't implemented in Jamoma2. Even if we do this, the creation of a new object is so expensive that it will dwarf the computational expense of a string comparison, especially a short string comparison.

For setting an attribute whose data is a Symbol. E.g. the mode of an Overdrive object or the name of a file to read.

In the latter case the filename may or may not need a comparison to avoid reading an already loaded file, but who cares -- the expense of reading a file is so massive that it won't be noticed.

In the former case we are more likely to care. Here is a specific scenario: A series of changes to the mode parameter for Overdrive are made. These are queued to be executed in the process method. Now we have a whole series of string comparisons happening in the process method and the CPU usage potentially skyrockets.

So, in a world without a Symbol that compares quickly, what do we do?

First, for any calls made in C++ the idea of passing a string is questionable. It can't be autocompleted when writing the code. Documentation is not available when highlighting it in the IDE. It can't be type-checked at compile-time, meaning you don't know about errors until someone is running the code. And (as mentioned) it is slower than molasses.

An idiomatic solution in C++ would be to use enums for these parameters. Comparisons are then a single int, autocomplete, doc integration, and type-safety are all present.

To make the enum dynamically addressable we assign the values for the enumerators to be a hash of the string version of the key.  See the Limiter class as an example.


### Fewer 'Amenities'

We've eliminated the inherited **bypass** for every object.
We've eliminated the inherited **gain** for every object.

These services are not free, not always appropriate, sometimes redundant, and better implemented on an as-needed basis in a way that is idiomatic to the algorithm at hand.

We have not discussed the **mute** option explicitly. In general the sentiment of the Florida workshop was that things like this are perhaps better left as a function of the graph instead of as baked-in to the unit generators themselves.

### DSP Calculation

Back in the PPC processor days we paid a very heavy penalty for branching instructions in the code. As such the original JamomaDSP (or TTBlue as it was then called) went to extreme lengths to optimize by eliminating such branching.  In the case of the DSP calculation routine this meant that we wanted to avoid `if/else` clauses and we did so by creating separate calculation routines and pointed to the routine we wanted by calling through one or more function pointers.

The branching penalty on contemporary processors is not nearly so severe. Furthermore, the indirection through function pointers prohibits the compiler from inlining calls through the methods and thus levies a heavy performance penalty.  Now that we are working in a header-only environment the gains that can be had from radical inlining far exceed the cost of some occasional `if` statements.

As such, we now use simple methods (overloading the the `()` operator), which also yields the most direct, understandable, and elegant code.

## Glossary

* **Sample** -- A single sample value
* **SampleVector** -- A vector of sample values
* **SampleBundle** -- N SampleVectors, where N is the number of channels
* **SampleBundleGroup** -- N SampleBundles

* **Immutable** -- Readonly (or const in C++ terms), meaning it must be fully initialized when constructed. For example: an `ImmutableSampleBundle` might contain the samples from an audio file. You can't change the samples. So if you want to read a different audio file then you create a new `ImmutableSampleBundle` and then discard the old one.
* **Shared** -- A shared type is internal reference counted, probably using C++11 smart pointers. In the example above it would be best to use a `SharedImmutableSampleBundle` because you are guaranteed that the `SampleBundle` will not disappear in the middle of a routine that is attempting to read from it.

### Idiomatic SampleBundleGroup Usage

* **FFT** -- one bundle of reals, one bundle of imaginaries -- This way the graph stays the same regardless of changes to channel counts.  The same will apply to the **Hilbert Transform**.  Also algorithms will make sense e.g. multiplying squares of the two bundles (one bundle of reals and one of imaginaries) will yield a bundle on which we call a sqrt operator to get the magnitudes.
* **SVF** -- one bundle for each response type at output



### Class Construction

* Parameter -- was "attribute"
* Message
* Notification -- was "return"


## Unit Testing

Where relevant, unit tests should include in comments any reference code or processes used to generate the expected results.  For mathematical or dsp cases the preferred environment is Octave.  To set that up on a Mac running Yosemite:

```
# if you do not have homebrew installed, visit http://brew.sh/
brew tap homebrew/science
brew update
brew upgrade

# these next two steps may take almost an hour to complete, 
# even on fast machines. plan accordingly.
brew install gcc
brew install octave

# for dsp applications you will need to download two add-ons.
# these should be downloaded via your browser at the following URLs:
# http://octave.sourceforge.net/control/index.html
# http://octave.sourceforge.net/signal/index.html

# now you can install them in octave itself using the path 
# to your Downloads folder.
# there may be lots of warnings, don't be alarmed.

octave
pkg install ~/Downloads/control-2.8.4.tar.gz
pkg install ~/Downloads/signal-1.3.2.tar.gz

# now you actually load the signal package:

pkg load signal

# and then you can use octave...
# For example to generate an impulse response from a numerator (a) and denominator (b):

a = [0.5, 1.0];% numerator (fir)
b = [1.0, 0.5];% denominator (iir)
i = impz(a, b, 64);
format long g
i
```
