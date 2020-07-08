#pragma once
#ifndef _DICSmoother_Header
#define _DICSmoother_Header

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
	tnbLib::DICSmoother

Description
	Simplified diagonal-based incomplete Cholesky smoother for symmetric
	matrices.

	To improve efficiency, the residual is evaluated after every nSweeps
	sweeps.

SourceFiles
	DICSmoother.C

\*---------------------------------------------------------------------------*/

#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class DICSmoother Declaration
	\*---------------------------------------------------------------------------*/

	class DICSmoother
		:
		public lduMatrix::smoother
	{
		// Private Data

			//- The reciprocal preconditioned diagonal
		scalarField rD_;


	public:

		//- Runtime type information
		TypeName("DIC");


		// Constructors

			//- Construct from matrix components
		DICSmoother
		(
			const word& fieldName,
			const lduMatrix& matrix,
			const FieldField<Field, scalar>& interfaceBouCoeffs,
			const FieldField<Field, scalar>& interfaceIntCoeffs,
			const lduInterfaceFieldPtrsList& interfaces
		);


		// Member Functions

			//- Smooth the solution for a given number of sweeps
		void smooth
		(
			scalarField& psi,
			const scalarField& source,
			const direction cmpt,
			const label nSweeps
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DICSmoother_Header
