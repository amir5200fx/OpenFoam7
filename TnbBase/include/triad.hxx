#pragma once
#ifndef _triad_Header
#define _triad_Header 

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::triad

Description
	Representation of a 3D Cartesian coordinate system as a Vector of vectors.

See also
	tnbLib::quaternion

SourceFiles
	triadI.H
	triad.C

\*---------------------------------------------------------------------------*/

#include <vector.hxx>
#include <tensor.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class Istream;
	class Ostream;

	// Forward declaration of friend functions and operators
	class triad;
	FoamBase_EXPORT Istream& operator>>(Istream&, triad&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const triad&);

	class quaternion;

	/*---------------------------------------------------------------------------*\
							   Class triad Declaration
	\*---------------------------------------------------------------------------*/

	class triad
		:
		public Vector<vector>
	{

	public:

		// Constructors

			//- Construct null
		inline triad();

		//- Construct from components
		inline triad(const Vector<vector>& vv);

		//- Construct from coordinate axes
		inline triad(const vector& x, const vector& y, const vector& z);

		//- Construct from a primary axis with the other two unset
		inline triad(const vector& pa);

		//- Construct from a quaternion
		FoamBase_EXPORT triad(const quaternion& q);

		//- Construct from a tensor
		FoamBase_EXPORT triad(const tensor& t);

		//- Construct from Istream
		inline triad(Istream&);


		// Static Data Members

		static FoamBase_EXPORT const triad I;
		static FoamBase_EXPORT const triad unset;


		// Member Functions

			//- Is the vector in the direction d set
		inline bool set(const direction d) const;

		//- Are all the vector set
		inline bool set() const;

		//- Return the primary direction of the vector v
		static inline direction primaryDirection(const vector& v);

		//- Return the vector orthogonal to the two provided
		static inline vector orthogonal(const vector& v1, const vector& v2);

		//- Orthogonalize this triad so that it is ortho-normal
		FoamBase_EXPORT void orthogonalize();

		//- Normalize each set axis vector to have a unit magnitude
		FoamBase_EXPORT void normalize();

		//- Align this triad with the given vector v
		//  by rotating the most aligned axis to be coincident with v
		FoamBase_EXPORT void align(const vector& v);

		//- Sort the axes such that they are closest to the x, y and z axes
		FoamBase_EXPORT triad sortxyz() const;

		//- Convert to a quaternion
		FoamBase_EXPORT operator quaternion() const;


		// Member Operators

		inline void operator=(const Vector<vector>&);

		FoamBase_EXPORT void operator=(const tensor& t);

		//- Add the triad t2 to this triad
		//  without normalizing or orthogonalizing
		FoamBase_EXPORT void operator+=(const triad& t2);


		// IOstream Operators

		inline friend Istream& operator>>(Istream&, triad&);
		inline friend Ostream& operator<<(Ostream&, const triad&);
	};


	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	//- Return a quantity of the difference between two triads
	FoamBase_EXPORT scalar diff(const triad& A, const triad& B);

	//- Data associated with quaternion type are contiguous
	template<>
	inline bool contiguous<triad>() { return true; }


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <triadI.hxx>

#endif // !_triad_Header
