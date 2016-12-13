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
			xy				= Hash("xy"),			///< Cartesian 2D (xy), assumes z=0
			spherical		= Hash("spherical"),	///< 3D spherical coordinates (azimuth, elevation, distance), using SpatDIF coordinate conventions
			aed				= Hash("aed"),			///< 3D spherical coordinates (azimuth, elevation, distance), using SpatDIF coordinate conventions
			polar			= Hash("polar"),		///< 2D polar coordinates (azimuth, distance)
			ad				= Hash("ad"),			///< 2D polar coordinates (azimuth, distance)
			openGL			= Hash("openGL"),		///< 3D cartesian coordinates, using OpenGL coordinate conventions
			cylindrical		= Hash("cylindrical"),	///< 3D cylindrical coordinates, expressed as polar coordinates and height (horizontal distance, azimuth, height(z))
			daz				= Hash("daz")			///< 3D cylindrical coordinates, expressed as polar coordinates and height (horizontal distance, azimuth, height(z))
		};


		/// A triplet of values of type T
		template<typename T>
		using PositionValue = std::array<T,3>;

		
#pragma mark - Cartesian 3D - xyz

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
		

#pragma mark - Cartesian 2D - xy
		
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
		

#pragma mark - Spherical - aed
		
		// Spherical : azimunt, elevation, distance, using degrees
		// TODO: This can be optimised by doing a temp calculation so that the same doesn't have to be done several times over.
		template <class T>
		class SphericalUnit : public UnitBase<PositionValue<T>> {
		public:
			PositionValue<T> toNeutral(const PositionValue<T>& input) const override {
				return {{
					sin(input[0] * kDegToRad) * cos(input[1] * kDegToRad) * input[2],	// x
					cos(input[0] * kDegToRad) * cos(input[1] * kDegToRad) * input[2],	// y
					sin(input[1] * input[2])											// z
				}};
			}
			
			PositionValue<T> fromNeutral(const PositionValue<T>& input) const override {
				return {{
					atan2(input[0], input[1]) * kRadToDeg,
					atan2(input[2], sqrt(input[0] * input[0] + input[1] * input[1])) * kRadToDeg,
					sqrt(input[0] * input[0] + input[1] * input[1] + input[2] * input[2])
				}};
			}
		};
		

#pragma mark - Polar - ad
		
		// Polar : azimunt, distance, using degrees
		// Polar has 2, not 3 dimensions
		// This implies that
		//		toNeutral() => receives 2 values, returns 3
		//		fromNeutral	=> receives 3 values, returns 2
		// We implement this by padding the PositionValue with zeroes.
		template <class T>
		class PolarUnit : public UnitBase<PositionValue<T>> {
		public:
			PositionValue<T> toNeutral(const PositionValue<T>& input) const override {
				return {{
					sin(input[0] * kDegToRad) * input[1],	// x
					cos(input[0] * kDegToRad) * input[1],	// y
					0.0										// z
				}};
			}
			
			PositionValue<T> fromNeutral(const PositionValue<T>& input) const override {
				return {{
					atan2(input[0], input[1]) * kRadToDeg,				// a
					sqrt(input[0] * input[0] + input[1] * input[1]),	// d
					0.0
				}};
			}
		};
		
		
#pragma mark - OpenGL
		
		// OpenGL
		template <class T>
		class OpenGlUnit : public UnitBase<PositionValue<T>> {
		public:
			PositionValue<T> toNeutral(const PositionValue<T>& input) const override {
				return {{ input[0], -input[2], input[1] }};
			}
			
			PositionValue<T> fromNeutral(const PositionValue<T>& input) const override {
				return {{ input[0], input[2], -input[1] }};
			}
		};
		

#pragma mark - Cylindical - daz
		
		// Cylindrical : diameter azimuth height
		// As defined in ISO 31-11 http://en.wikipedia.org/wiki/ISO_31-11#Coordinate_systems
		template <class T>
		class CylindricalUnit : public UnitBase<PositionValue<T>> {
		public:
			PositionValue<T> toNeutral(const PositionValue<T>& input) const override {
				return {{
					sin(input[1] * kDegToRad) * input[0],	// x
					cos(input[1] * kDegToRad) * input[0],	// y
					input[2]								// z
				}};
			}
			
			PositionValue<T> fromNeutral(const PositionValue<T>& input) const override {
				return {{
					sqrt(input[0] * input[0] + input[1] * input[1]),	// d
					atan2(input[0], input[1]) * kRadToDeg,				// a
					input[2]											// z
				}};
			}
		};


#pragma mark - Position dataspace
		
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
				{PositionUnit::xy, 			new Cartesian2DUnit<T>()},
				{PositionUnit::spherical, 	new SphericalUnit<T>()},
				{PositionUnit::aed,			new SphericalUnit<T>()},
				{PositionUnit::polar,		new PolarUnit<T>()},
				{PositionUnit::ad,			new PolarUnit<T>()},
				{PositionUnit::openGL,		new OpenGlUnit<T>()},
				{PositionUnit::cylindrical, new CylindricalUnit<T>()},
				{PositionUnit::daz,			new CylindricalUnit<T>()}
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
