#pragma once
#ifndef _ensightParts_Header
#define _ensightParts_Header

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
	tnbLib::ensightParts

Description
	A collection of several ensightPart elements

SourceFiles
	ensightParts.C
	ensightPartsTemplates.C

\*---------------------------------------------------------------------------*/

#include <ensightPart.hxx>
#include <ensightPartFaces.hxx>
#include <ensightPartCells.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class ensightParts;

	FoamConversion_EXPORT ensightGeoFile& operator<<(ensightGeoFile&, const ensightParts&);


	/*---------------------------------------------------------------------------*\
						   Class ensightParts Declaration
	\*---------------------------------------------------------------------------*/

	class ensightParts
	{
		// Private Data

			//- List of parts
		PtrList<ensightPart> partsList_;


	public:

		// Constructors

			//- Construct from polyMesh
		FoamConversion_EXPORT ensightParts(const polyMesh&);

		//- Construct from IOobject
		FoamConversion_EXPORT ensightParts(const IOobject&);

		//- Disallow default bitwise copy construction
		FoamConversion_EXPORT ensightParts(const ensightParts&) = delete;


		//- Destructor
		FoamConversion_EXPORT ~ensightParts();


		// Member Functions

			//- Clear old information and construct anew from polyMesh
		FoamConversion_EXPORT void recalculate(const polyMesh&);

		//- Renumber elements
		FoamConversion_EXPORT void renumber
		(
			const labelUList& origCellId,
			const labelUList& origFaceId
		);

		//- Number of parts
		label size() const
		{
			return partsList_.size();
		}

		//- Write the geometry
		FoamConversion_EXPORT void writeGeometry(ensightGeoFile&) const;

		//- Write summary information about the objects
		FoamConversion_EXPORT bool writeSummary(Ostream&) const;

		//- Write the lists
		FoamConversion_EXPORT void writeData(Ostream&) const;

		//- Write (volume) scalar field
		//  optionally write data for face parts
		//  optionally write data per node
		FoamConversion_EXPORT void writeScalarField
		(
			ensightFile&,
			const List<scalar>& field,
			const bool useFaceData = false,
			const bool perNode = false
		) const;

		//- Write (volume) vector field components
		//  optionally write data for face parts
		//  optionally write data per node
		FoamConversion_EXPORT void writeVectorField
		(
			ensightFile&,
			const List<scalar>& field0,
			const List<scalar>& field1,
			const List<scalar>& field2,
			const bool useFaceData = false,
			const bool perNode = false
		) const;


		//- Write generalized volume field components
		template<class Type>
		void writeField
		(
			ensightFile&,
			const GeometricField<Type, fvPatchField, volMesh>&
		) const;



		// Member Operators

			//- Disallow default bitwise assignment
		FoamConversion_EXPORT void operator=(const ensightParts&) = delete;


		// Friend Operators

			//- Write geometry
		friend FoamConversion_EXPORT ensightGeoFile& operator<<(ensightGeoFile&, const ensightParts&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ensightPartsI.hxx>

//#ifdef NoRepository
//#include <ensightPartsTemplates.cxx>
//#endif

#endif // !_ensightParts_Header
