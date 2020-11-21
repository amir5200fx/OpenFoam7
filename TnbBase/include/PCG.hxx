#pragma once
#ifndef _PCG_Header
#define _PCG_Header

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
	tnbLib::PCG

Description
	Preconditioned conjugate gradient solver for symmetric lduMatrices
	using a run-time selectable preconditioner.

SourceFiles
	PCG.C

\*---------------------------------------------------------------------------*/

#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class PCG Declaration
	\*---------------------------------------------------------------------------*/

	class PCG
		:
		public lduMatrix::solver
	{

	public:

		//- Runtime type information
		//TypeName("PCG");
		static const char* typeName_() { return "PCG"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from matrix components and solver controls
		FoamBase_EXPORT PCG
		(
			const word& fieldName,
			const lduMatrix& matrix,
			const FieldField<Field, scalar>& interfaceBouCoeffs,
			const FieldField<Field, scalar>& interfaceIntCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const dictionary& solverControls
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT PCG(const PCG&) = delete;


		//- Destructor
		virtual ~PCG()
		{}


		// Member Functions

			//- Solve the matrix with this solver
		FoamBase_EXPORT virtual solverPerformance solve
		(
			scalarField& psi,
			const scalarField& source,
			const direction cmpt = 0
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const PCG&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PCG_Header
