/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Generator Algorithms
	
	@details 	Generator Algorithms for use with std::generate.
	
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once


namespace Jamoma {
	namespace Generator {
	
		
		// NW: what follows are three examples (Ramp, Sine, Triangle)
		// these demo what a class designed to work with std:generate might look like
		
		template <typename T>
		class Ramp {
		public:
			Ramp (int size = 1)
			: max(size)
			{}
			
			T operator()() {
				++current;
				return T(current) / max;
			}
			
		private:
			int current = -1;
			int max;
		};
		
		
		template <typename T>
		class Sine {
		public:
			Sine (int size = 1)
			: max(size)
			{}
			
			T operator()() {
				++current;
				auto output = std::sin(current * kTwoPi / max);
				return T(output);
			}
			
		private:
			int current = -1;
			int max;
		};
		
		
		template <typename T>
		class Triangle {
		public:
			Triangle (int size = 1)
			: max(size)
			{}
			
			T operator()() {
				T out = 0.0;
				++current;
				
				if (current <= max/4)
					out = 4.0 * current / max;
				else if (current >= 3 * max / 4)
					out = -4.0 + 4.0 * current / max;
				else
					out = 2.0 - 4.0 * current / max;
				return out;
			}
			
		private:
			int current = -1;
			int max;
		};
	
	} // namespace Generator
} // namespace Jamoma
