#pragma once
#ifndef _ensightPartCells_Header
#define _ensightPartCells_Header

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
	tnbLib::ensightPartCells

Description
	An implementation of ensightPart to hold volume mesh cells.

SourceFiles
	ensightPartCells.C

\*---------------------------------------------------------------------------*/

#include <ensightPart.hxx>
#include <typeInfo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class ensightPartCells Declaration
	\*---------------------------------------------------------------------------*/

	class ensightPartCells
		:
		public ensightPart
	{
		// Private Member Functions

			//- Classify the cell types, set elemLists.
		FoamConversion_EXPORT void classify
		(
			const polyMesh&,
			const labelUList& idLabels = labelUList::null()
		);

		//- Track points used
		FoamConversion_EXPORT virtual localPoints calcLocalPoints() const;

		//- Track the points used
		// virtual void makeLocalPointMap();

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
			tetra4Elements,
			pyramid5Elements,
			penta6Elements,
			hexa8Elements,
			nfacedElements
		};


		// Static Data Members

		static FoamConversion_EXPORT const polyMesh* const polyMeshNullPtr_;

		static FoamConversion_EXPORT const List<word> elemTypes_;


		// Protected data

			//- Mesh referenced
		const polyMesh& mesh_;


	public:

		//- Runtime type information
		//TypeName("ensightCells");
		static const char* typeName_() { return "ensightCells"; }
		static FoamConversion_EXPORT const ::tnbLib::word typeName;
		static FoamConversion_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct empty part with number and description
		FoamConversion_EXPORT ensightPartCells(label partNumber, const string& partDescription);

		//- Construct from polyMesh without zones
		FoamConversion_EXPORT ensightPartCells(label partNumber, const polyMesh&);

		//- Construct from polyMesh and list of (non-zoned) cells
		FoamConversion_EXPORT ensightPartCells
		(
			label partNumber,
			const polyMesh&,
			const labelUList&
		);

		//- Construct from polyMesh and cellZone
		FoamConversion_EXPORT ensightPartCells
		(
			label partNumber,
			const polyMesh&,
			const cellZone&
		);

		//- Copy constructor
		FoamConversion_EXPORT ensightPartCells(const ensightPartCells&);

		//- Reconstruct part characteristics (eg, element types) from Istream
		//  A part reconstructed in this manner can be used when writing fields,
		//  but cannot be used to write a new geometry
		//  \sa tnbLib::ensightPart::reconstruct
		FoamConversion_EXPORT ensightPartCells(Istream&);

		//- Reconstruct part characteristics on freestore from Istream
		static autoPtr<ensightPartCells> New(Istream& is)
		{
			return autoPtr<ensightPartCells>(new ensightPartCells(is));
		}


		//- Destructor
		FoamConversion_EXPORT virtual ~ensightPartCells();


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
		FoamConversion_EXPORT void operator=(const ensightPartCells&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ensightPartCells_Header
