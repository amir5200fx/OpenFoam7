#pragma once
#ifndef _pairGAMGAgglomeration_Header
#define _pairGAMGAgglomeration_Header

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
	tnbLib::pairGAMGAgglomeration

Description
	Agglomerate using the pair algorithm.

SourceFiles
	pairGAMGAgglomeration.C
	pairGAMGAgglomerate.C

\*---------------------------------------------------------------------------*/

#include <GAMGAgglomeration.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class pairGAMGAgglomeration Declaration
	\*---------------------------------------------------------------------------*/

	class pairGAMGAgglomeration
		:
		public GAMGAgglomeration
	{
		// Private Data

			//- Number of levels to merge, 1 = don't merge, 2 = merge pairs etc.
		label mergeLevels_;

		//- Direction of cell loop for the current level
		static FoamBase_EXPORT bool forward_;


	protected:

		// Protected Member Functions

			//- Agglomerate all levels starting from the given face weights
		FoamBase_EXPORT void agglomerate
		(
			const lduMesh& mesh,
			const scalarField& faceWeights
		);


	public:

		//- Runtime type information
		//TypeName("pair");
		static const char* typeName_() { return "pair"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given mesh and controls
		FoamBase_EXPORT pairGAMGAgglomeration
		(
			const lduMesh& mesh,
			const dictionary& controlDict
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT pairGAMGAgglomeration(const pairGAMGAgglomeration&) = delete;

		//- Calculate and return agglomeration
		static FoamBase_EXPORT tmp<labelField> agglomerate
		(
			label& nCoarseCells,
			const lduAddressing& fineMatrixAddressing,
			const scalarField& faceWeights
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const pairGAMGAgglomeration&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pairGAMGAgglomeration_Header
