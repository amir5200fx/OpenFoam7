#pragma once
#ifndef _diagonalSolver_Header
#define _diagonalSolver_Header

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
	tnbLib::diagonalSolver

Description
	tnbLib::diagonalSolver

SourceFiles
	diagonalSolver.C

\*---------------------------------------------------------------------------*/

#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class diagonalSolver Declaration
	\*---------------------------------------------------------------------------*/

	class diagonalSolver
		:
		public lduMatrix::solver
	{

	public:

		//- Runtime type information
		//TypeName("diagonal");
		static const char* typeName_() { return "diagonal"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from matrix and solver controls
		FoamBase_EXPORT diagonalSolver
		(
			const word& fieldName,
			const lduMatrix& matrix,
			const FieldField<Field, scalar>& interfaceBouCoeffs,
			const FieldField<Field, scalar>& interfaceIntCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const dictionary& solverControls
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT diagonalSolver(const diagonalSolver&) = delete;


		// Member Functions

			//- Read and reset the solver parameters from the given stream
		void read(const dictionary&)
		{}

		//- Solve the matrix with this solver
		FoamBase_EXPORT solverPerformance solve
		(
			scalarField& psi,
			const scalarField& source,
			const direction cmpt = 0
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const diagonalSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_diagonalSolver_Header
