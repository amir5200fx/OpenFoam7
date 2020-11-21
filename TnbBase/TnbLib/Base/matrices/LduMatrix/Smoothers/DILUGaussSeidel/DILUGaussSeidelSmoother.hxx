#pragma once
#ifndef _DILUGaussSeidelSmoother_Header
#define _DILUGaussSeidelSmoother_Header

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
	tnbLib::DILUGaussSeidelSmoother

Description
	Combined DILU/GaussSeidel smoother for asymmetric matrices in which
	DILU smoothing is followed by GaussSeidel to ensure that any "spikes"
	created by the DILU sweeps are smoothed-out.

SourceFiles
	DILUGaussSeidelSmoother.C

\*---------------------------------------------------------------------------*/

#include <DILUSmoother.hxx>
#include <GaussSeidelSmoother.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class DILUGaussSeidelSmoother Declaration
	\*---------------------------------------------------------------------------*/

	class DILUGaussSeidelSmoother
		:
		public lduMatrix::smoother
	{
		// Private Data

		DILUSmoother diluSmoother_;

		GaussSeidelSmoother gsSmoother_;


	public:

		//- Runtime type information
		//TypeName("DILUGaussSeidel");
		static const char* typeName_() { return "DILUGaussSeidel"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from matrix components
		FoamBase_EXPORT DILUGaussSeidelSmoother
		(
			const word& fieldName,
			const lduMatrix& matrix,
			const FieldField<Field, scalar>& interfaceBouCoeffs,
			const FieldField<Field, scalar>& interfaceIntCoeffs,
			const lduInterfaceFieldPtrsList& interfaces
		);


		// Member Functions

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

#endif // !_DILUGaussSeidelSmoother_Header
