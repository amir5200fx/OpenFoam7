#pragma once
#ifndef _TDILUPreconditioner_Header
#define _TDILUPreconditioner_Header

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
	tnbLib::TDILUPreconditioner

Description
	Simplified diagonal-based incomplete LU preconditioner for asymmetric
	matrices.

	The inverse (reciprocal for scalar) of the preconditioned diagonal is
	calculated and stored.

SourceFiles
	TDILUPreconditioner.C

\*---------------------------------------------------------------------------*/

#include <LduMatrixTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class TDILUPreconditioner Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type, class DType, class LUType>
	class TDILUPreconditioner
		:
		public LduMatrix<Type, DType, LUType>::preconditioner
	{
		// Private Data

			//- The inverse (reciprocal for scalar) preconditioned diagonal
		Field<DType> rD_;


	public:

		//- Runtime type information
		//TypeName("DILU");
		static const char* typeName_() { return "DILU"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from matrix components and preconditioner data dictionary
		TDILUPreconditioner
		(
			const typename LduMatrix<Type, DType, LUType>::solver& sol,
			const dictionary& preconditionerDict
		);


		// Destructor

		virtual ~TDILUPreconditioner()
		{}


		// Member Functions

			//- Calculate the reciprocal of the preconditioned diagonal
		static void calcInvD
		(
			Field<DType>& rD,
			const LduMatrix<Type, DType, LUType>& matrix
		);

		//- Return wA the preconditioned form of residual rA
		virtual void precondition
		(
			Field<Type>& wA,
			const Field<Type>& rA
		) const;

		//- Return wT the transpose-matrix preconditioned form of
		//  residual rT.
		virtual void preconditionT
		(
			Field<Type>& wT,
			const Field<Type>& rT
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <TDILUPreconditionerI.hxx>

//#ifdef NoRepository
//#include <TDILUPreconditioner.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TDILUPreconditioner_Header
