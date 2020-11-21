#pragma once
#ifndef _surfZone_Header
#define _surfZone_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::surfZone

Description
	A surface zone on a MeshedSurface.

	Similar in concept to a faceZone, but the face list is contiguous.

SourceFiles
	surfZone.C

\*---------------------------------------------------------------------------*/

#include <word.hxx>
#include <label.hxx>
#include <className.hxx>
#include <surfZoneIdentifier.hxx>
#include <autoPtr.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class surfZone;

	FoamFvMesh_EXPORT Istream& operator>>(Istream&, surfZone&);
	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const surfZone&);

	/*---------------------------------------------------------------------------*\
							  Class surfZone Declaration
	\*---------------------------------------------------------------------------*/

	class surfZone
		:
		public surfZoneIdentifier
	{
		// Private Data

			//- Size of this group in the face list
		label size_;

		//- Start label of this group in the face list
		label start_;


	public:

		//- Runtime type information
		/*ClassName("surfZone");*/
		static const char* typeName_() { return "surfZone"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct null
		FoamFvMesh_EXPORT surfZone();

		//- Construct from components
		FoamFvMesh_EXPORT surfZone
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const word& geometricType = word::null
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT surfZone(Istream& is, const label index);

		//- Construct from dictionary
		FoamFvMesh_EXPORT surfZone
		(
			const word& name,
			const dictionary& dict,
			const label index
		);

		//- Construct from another zone, resetting the index
		FoamFvMesh_EXPORT surfZone(const surfZone&, const label index);

		//- Return clone
		autoPtr<surfZone> clone() const
		{
			NotImplemented;
			return autoPtr<surfZone>(nullptr);
		}

		static autoPtr<surfZone> New(Istream& is)
		{
			word name(is);
			dictionary dict(is);

			return autoPtr<surfZone>(new surfZone(name, dict, 0));
		}


		// Member Functions

			//- Return start label of this zone in the face list
		label start() const
		{
			return start_;
		}

		//- Return start label of this zone in the face list
		label& start()
		{
			return start_;
		}

		//- Return size of this zone in the face list
		label size() const
		{
			return size_;
		}

		//- Return size of this zone in the face list
		label& size()
		{
			return size_;
		}

		//- Write
		FoamFvMesh_EXPORT void write(Ostream&) const;

		//- Write dictionary
		FoamFvMesh_EXPORT void writeDict(Ostream&) const;


		// Member Operators

		FoamFvMesh_EXPORT bool operator!=(const surfZone&) const;

		//- compare.
		FoamFvMesh_EXPORT bool operator==(const surfZone&) const;


		// IOstream Operators

		friend FoamFvMesh_EXPORT Istream& operator>>(Istream&, surfZone&);
		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const surfZone&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfZone_Header
