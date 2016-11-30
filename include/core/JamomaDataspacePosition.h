/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Position Dataspace
	
	@author 	Trond Lossius, Timothy Place, Nils Peters
	@copyright	Copyright (c) 2005-2016 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaDataspace.h"


namespace Jamoma {
	namespace Dataspace {
			
	
		/// Names of all units for the position dataspace.

		enum class PositionUnit : uint32_t {
			cart3D			= Hash("cart3D"),		///< Cartesian 3Db(xyz), using SpatDIF coordinate conventions
			xyz				= Hash("xyz"),			///< Cartesian 3Db(xyz), using SpatDIF coordinate conventions
			cart2D			= Hash("cart2D"),		///< Cartesian 2D (xy), assumes z=0
			xy				= Hash("xy")			///< Cartesian 2D (xy), assumes z=0
				
			/* *** Commented out until we have the basics worked out. ***
			spherical		= Hash("spherical"),	///< 3D spherical coordinates (azimuth, elevation, distance), using SpatDIF coordinate conventions
			aed				= Hash("aed"),			///< 3D spherical coordinates (azimuth, elevation, distance), using SpatDIF coordinate conventions
			polar			= Hash("polar"),		///< 2D polar coordinates (azimuth, distance)
			ad				= Hash("ad"),			///< 2D polar coordinates (azimuth, distance)
			openGL			= Hash("openGL"),		///< 3D cartesian coordinates, using OpenGL coordinate conventions
			cylindrical		= Hash("cylindrical"),	///< 3D cylindrical coordinates, expressed as polar coordinates and height (horizontal distance, azimuth, height(z))
			daz				= Hash("daz")			///< 3D cylindrical coordinates, expressed as polar coordinates and height (horizontal distance, azimuth, height(z))
			*/
		};


		/// A triplet of values of type T
		template<typename T>
		using PositionValue = std::array<T,3>;


		/// Cartesian 3D is the neutral unit, so it is a pass-through
		template <class T>
		class Cartesian3DUnit : public UnitBase<PositionValue<T>> {
		public:
			PositionValue<T> toNeutral(const PositionValue<T>& input) const override {
				return input;
			}
			
			PositionValue<T> fromNeutral(const PositionValue<T>& input) const override {
				return input;
			}
		};
		
		
		// Cartesian 2D always has z=0. As such it has 2, not 3 dimensions
		// This implies that
		//		toNeutral() => receives 2 values, returns 3
		//		fromNeutral	=> receives 3 values, returns 2
		// We implement this by padding the PositionValue with zeroes.

		template <class T>
		class Cartesian2DUnit : public UnitBase<PositionValue<T>> {
		public:
			PositionValue<T> toNeutral(const PositionValue<T>& input) const override {
				return {{ input[0], input[1], 0.0 }};
			}
			
			PositionValue<T> fromNeutral(const PositionValue<T>& input) const override {
				return {{ input[0], input[1], 0.0 }};
			}
		};
		
		
		///	The Position Dataspace.

		template <class T,PositionUnit U>
		class Position /*: public Dataspace*/ {
			
			/**	Mapping from unit names to actual unit converter objects.
				TODO: make this a static so that we don't have to spend resources on it for all instances
			 */
			std::unordered_map<PositionUnit, UnitBase<PositionValue<T>>*>	sUnits = {
				{PositionUnit::cart3D, 		new Cartesian3DUnit<T>()},
				{PositionUnit::xyz, 		new Cartesian3DUnit<T>()},
				{PositionUnit::cart2D, 		new Cartesian2DUnit<T>()},
				{PositionUnit::xy, 			new Cartesian2DUnit<T>()}
			};

			
			/**	The native unit to/from which we perform conversions.	*/
			const UnitBase<PositionValue<T>>* mUnit = sUnits[U];

			
		public:
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			PositionValue<T> operator()(const PositionValue<T>& x, const PositionUnit& unit = U)
			{
				return mUnit->fromNeutral( sUnits[unit]->toNeutral(x) );
			}

			PositionValue<T> operator()(const PositionValue<T>& x, uint32_t unit)
			{
				return (*this)(x, (PositionUnit)unit);
			}
		
			/**	Conversion function where the unit is passed as a string.	*/
			PositionValue<T> operator()(const PositionValue<T> x, const char* str)
			{
				return (*this)( x, (PositionUnit)Hash(str) );
			}

		};
	
	} // namespace Dataspace
} // namespace Jamoma
