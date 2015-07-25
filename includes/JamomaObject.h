//
//  JamomaObject.h
//  JamomaExperiments
//
//  Created by Timothy Place on 3/27/15.
//  Copyright (c) 2015 jamoma. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>
#include <array>


namespace Jamoma {
	
	using Synopsis = const char*;

	template <typename T>
	using Boundaries = std::pair<T, T>;
	
	enum class BoundaryBehavior {
		none,
		clip,
		wrap,
		fold
	};
	
	
	class Object {
	public:
		// constructor for users of an object that is created by dynamic lookup, e.g. Jamoma::Object filter("lowpass.4");
		Object(String name)
		{}
		
		// constructor for users of an object that is created statically/directly
		Object()
		{}
		
		// do we also need a constexpr constructor ?
		// that way objects can register and add their tags?
		// how does that all work?
		
		
		
		ValueBase send(const String& name, const ValueBase& input) { return Value<int>(0); };
		ValueBase send(const String& name) { return Value<int>(0); };
		
		
		// Allows us a unified means for referencing a Parameter of any template-specialization
		// The bool part is only present as a type of some sort is required -- this trick learned from std::string implementation
		//template <bool>
		//class ParameterBase {
		class ParameterBase {
			Object*				mOwner;
			String				mName;

		public:
			ParameterBase(Object* owner, const String& name)
			: mOwner(owner)
			, mName(name)
			{}
			
			String& name()
			{
				return mName;
			}
			
			friend bool operator == (const ParameterBase& lhs, const char* rhs)
			{
				return lhs.mName == rhs;
			}
			
			virtual ParameterBase& operator = (const ValueBase& input) = 0;

		};
		
		template <class T>
		// class Parameter : public ParameterBase<true> {
		class Parameter : public ParameterBase {
			T					mValue;
			Synopsis			mSynopsis;
			Boundaries<T>		mBoundaries;
			BoundaryBehavior	mBoundaryBehavior;
			Function			mSetter = { nullptr };
			// getter
			
		public:
			
			//template <typename F>
			//Parameter(Object* owner, String name, T initial, ...)
			Parameter(Object* owner, String name, T initial)
			: ParameterBase(owner, name)
			, mValue(initial)
			, mBoundaryBehavior(BoundaryBehavior::none)
			{
				// 1. iterate args
				// 2. determine their types
				// 3. do something appropriate for their given type
				// 4. can we make this whole thing constexpr ?
				
				// need to have a default-setter closure, and default-getter closure to use if none are passed-in
				
				owner->parameters[name] = this;
			}
			
			
			Parameter(Object* owner, String name, T initial, Function setter)
			: ParameterBase(owner, name)
			, mValue(initial)
			, mBoundaryBehavior(BoundaryBehavior::none)
			, mSetter(setter)
			{
				// 1. iterate args
				// 2. determine their types
				// 3. do something appropriate for their given type
				// 4. can we make this whole thing constexpr ?
				
				// need to have a default-setter closure, and default-getter closure to use if none are passed-in
				
				owner->parameters[name] = this;
			}

			
			// setter
			Parameter& operator = (T input)
			{
				mValue = input;
				if (mSetter)
					mSetter();
				return *this;
			}
			
			
			// setter for case when input is a generic value
			Parameter& operator = (const ValueBase& input)
			{
				mValue = (T)input;
				return *this;
			}

			
			// assign *values* from one attribute to another
			Parameter& operator = (Parameter& input)
			{
				mValue = input.mvalue;
				return *this;
			}
			
			
			// getter
			operator T() const
			{
				return mValue;
			}
		};
		
		
		// we really just care that we have a pointer, not about the type of the attribute
		// attributes can be raw pointers because they are only accessed and owned by our class
		using ParameterMap = std::unordered_map<String, ParameterBase*>;
		
		ParameterMap	parameters;
		

		class Message {
		public:
			
			template <typename F>
			Message(String name, F fn) {}
			
			template <typename F>
			Message(String name, Synopsis synopsis, F fn) {}
			
			Error operator ()() {
				return Error::none;
			}
			
		private:
			Synopsis		mSynopsis;
		};
		
	};

} // namespace Jamoma
