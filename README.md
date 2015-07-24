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