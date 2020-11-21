#pragma once
#ifndef _DICGaussSeidelSmoother_Header
#define _DICGaussSeidelSmoother_Header

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
	tnbLib::DICGaussSeidelSmoother

Description
	Combined DIC/GaussSeidel smoother for symmetric matrices in which DIC
	smoothing is followed by GaussSeidel to ensure that any "spikes" created
	by the DIC sweeps are smoothed-out.

SourceFiles
	DICGaussSeidelSmoother.C

\*---------------------------------------------------------------------------*/

#include <DICSmoother.hxx>
#include <GaussSeidelSmoother.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class DICGaussSeidelSmoother Declaration
	\*---------------------------------------------------------------------------*/

	class DICGaussSeidelSmoother
		:
		public lduMatrix::smoother
	{
		// Private Data

		DICSmoother dicSmoother_;

		GaussSeidelSmoother gsSmoother_;


	public:

		//- Runtime type information
		//TypeName("DICGaussSeidel");
		static const char* typeName_() { return "DICGaussSeidel"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from matrix components
		FoamBase_EXPORT DICGaussSeidelSmoother
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

#endif // !_DICGaussSeidelSmoother_Header
