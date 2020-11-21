#pragma once
#ifndef _ensightPartFaces_Header
#define _ensightPartFaces_Header

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
	tnbLib::ensightPartFaces

Description
	An implementation of ensightPart to hold volume mesh faces.

SourceFiles
	ensightPartFaces.C

\*---------------------------------------------------------------------------*/

#include <ensightPart.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class ensightPartFaces Declaration
	\*---------------------------------------------------------------------------*/

	class ensightPartFaces
		:
		public ensightPart
	{
		// Private Member Functions

			//- Track points used
		FoamConversion_EXPORT virtual localPoints calcLocalPoints() const;

		//- Element connectivity
		FoamConversion_EXPORT virtual void writeConnectivity
		(
			ensightGeoFile&,
			const word& key,
			const labelUList& idList,
			const labelUList& pointMap
		) const;


	protected:

		//- Addressable ensight element types
		enum elemType
		{
			tria3Elements,
			quad4Elements,
			nsidedElements
		};


		// Static Data Members

		static FoamConversion_EXPORT const List<word> elemTypes_;


		// Protected data

			//- Faces referenced
		const faceList& faces_;

		//- Can skip local point renumbering when points are contiguous
		const bool contiguousPoints_;


		// Protected Member Functions

			//- Classify the face shapes, set elemLists.
		FoamConversion_EXPORT void classify(const faceList&);

		//- Helper: write connectivity
		FoamConversion_EXPORT void writeConnectivity
		(
			ensightGeoFile&,
			const word& key,
			const faceList&,
			const labelUList& idList,
			const labelUList& pointMap
		) const;


	public:

		//- Runtime type information
		//TypeName("ensightFaces");
		static const char* typeName_() { return "ensightFaces"; }
		static FoamConversion_EXPORT const ::tnbLib::word typeName;
		static FoamConversion_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct empty part with number and description
		FoamConversion_EXPORT ensightPartFaces(label partNumber, const string& partDescription);

		//- Construct part with number, description, points and faces
		//  Can skip local point renumbering when points are contiguous
		FoamConversion_EXPORT ensightPartFaces
		(
			label partNumber,
			const string& partDescription,
			const pointField&,
			const faceList&,
			const bool contiguousPoints = false
		);

		//- Construct from polyMesh and polyPatch
		FoamConversion_EXPORT ensightPartFaces
		(
			label partNumber,
			const polyMesh&,
			const polyPatch&
		);

		//- Copy constructor
		FoamConversion_EXPORT ensightPartFaces(const ensightPartFaces&);

		//- Reconstruct part characteristics (eg, element types) from Istream
		//  A part reconstructed in this manner can be used when writing fields,
		//  but cannot be used to write a new geometry
		//  \sa tnbLib::ensightPart::reconstruct
		FoamConversion_EXPORT ensightPartFaces(Istream&);

		//- Reconstruct part characteristics on freestore from Istream
		static autoPtr<ensightPartFaces> New(Istream& is)
		{
			return autoPtr<ensightPartFaces>(new ensightPartFaces(is));
		}


		//- Destructor
		FoamConversion_EXPORT virtual ~ensightPartFaces();


		// Member Functions

			//- Write geometry
		FoamConversion_EXPORT virtual void writeGeometry(ensightGeoFile&) const;

		//- Static listing of the element types
		virtual const List<word>& elementTypes() const
		{
			return elemTypes_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamConversion_EXPORT void operator=(const ensightPartFaces&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ensightPartFaces_Header
