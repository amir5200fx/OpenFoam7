#pragma once
#ifndef _nonBlockingGaussSeidelSmoother_Header
#define _nonBlockingGaussSeidelSmoother_Header

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
	tnbLib::nonBlockingGaussSeidelSmoother

Description
	Variant of gaussSeidelSmoother that expects processor boundary
	cells to be sorted last and so can block later. Only when the
	cells are actually visited does it need the results to be present.
	It is expected that there is little benefit to be gained from doing
	this on a patch by patch basis since the number of processor interfaces
	is quite small and the overhead of checking whether a processor interface
	is finished might be quite high (call into mpi). Also this would
	require a dynamic memory allocation to store the state of the outstanding
	requests.

SourceFiles
	nonBlockingGaussSeidelSmoother.C

\*---------------------------------------------------------------------------*/

#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class nonBlockingGaussSeidelSmoother Declaration
	\*---------------------------------------------------------------------------*/

	class nonBlockingGaussSeidelSmoother
		:
		public lduMatrix::smoother
	{
		// Private Data

			//- Starting cell when to block
		label blockStart_;

	public:

		//- Runtime type information
		//TypeName("nonBlockingGaussSeidel");
		static const char* typeName_() { return "nonBlockingGaussSeidel"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamBase_EXPORT nonBlockingGaussSeidelSmoother
		(
			const word& fieldName,
			const lduMatrix& matrix,
			const FieldField<Field, scalar>& interfaceBouCoeffs,
			const FieldField<Field, scalar>& interfaceIntCoeffs,
			const lduInterfaceFieldPtrsList& interfaces
		);


		// Member Functions

			//- Smooth for the given number of sweeps
		static FoamBase_EXPORT void smooth
		(
			const word& fieldName,
			scalarField& psi,
			const lduMatrix& matrix,
			const label blockStart,
			const scalarField& source,
			const FieldField<Field, scalar>& interfaceBouCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const direction cmpt,
			const label nSweeps
		);

		//- Smooth the solution for a given number of sweeps
		FoamBase_EXPORT virtual void smooth
		(
			scalarField& psi,
			const scalarField& Source,
			const direction cmpt,
			const label nSweeps
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nonBlockingGaussSeidelSmoother_Header
