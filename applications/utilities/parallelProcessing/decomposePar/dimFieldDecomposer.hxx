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
	tnbLib::dimFieldDecomposer

Description
	Dimensioned field decomposer.

SourceFiles
	dimFieldDecomposer.C
	dimFieldDecomposerDecomposeFields.C

\*---------------------------------------------------------------------------*/

#ifndef dimFieldDecomposer_H
#define dimFieldDecomposer_H

#include <includeAllModules.hxx>

#include <fvMesh.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class IOobjectList;

	/*---------------------------------------------------------------------------*\
						Class fvFieldDecomposer Declaration
	\*---------------------------------------------------------------------------*/

	class dimFieldDecomposer
	{
		// Private Data

			//- Reference to complete mesh
		const fvMesh& completeMesh_;

		//- Reference to processor mesh
		const fvMesh& procMesh_;

		//- Reference to face addressing
		const labelList& faceAddressing_;

		//- Reference to cell addressing
		const labelList& cellAddressing_;


	public:

		// Constructors

			//- Construct from components
		dimFieldDecomposer
		(
			const fvMesh& completeMesh,
			const fvMesh& procMesh,
			const labelList& faceAddressing,
			const labelList& cellAddressing
		);

		//- Disallow default bitwise copy construction
		dimFieldDecomposer(const dimFieldDecomposer&) = delete;


		//- Destructor
		~dimFieldDecomposer();


		// Member Functions

			//- Decompose field
		template<class Type>
		tmp<DimensionedField<Type, volMesh>> decomposeField
		(
			const DimensionedField<Type, volMesh>& field
		) const;


		//- Decompose llist of fields
		template<class GeoField>
		void decomposeFields(const PtrList<GeoField>& fields) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const dimFieldDecomposer&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
	//#include "dimFieldDecomposerDecomposeFields.C"
#endif

#include "dimFieldDecomposerDecomposeFieldsI.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
