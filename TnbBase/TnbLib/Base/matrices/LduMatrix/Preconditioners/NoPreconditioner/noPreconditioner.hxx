#pragma once
#ifndef _noPreconditioner_Header
#define _noPreconditioner_Header

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
	tnbLib::noPreconditioner

Description
	Null preconditioner for both symmetric and asymmetric matrices.

SourceFiles
	noPreconditioner.C

\*---------------------------------------------------------------------------*/

#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class noPreconditioner Declaration
	\*---------------------------------------------------------------------------*/

	class noPreconditioner
		:
		public lduMatrix::preconditioner
	{

	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from matrix components and preconditioner solver controls
		FoamBase_EXPORT noPreconditioner
		(
			const lduMatrix::solver&,
			const dictionary& solverControlsUnused
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT noPreconditioner(const noPreconditioner&) = delete;


		//- Destructor
		virtual ~noPreconditioner()
		{}


		// Member Functions

			//- Return wA the preconditioned form of residual rA
		FoamBase_EXPORT virtual void precondition
		(
			scalarField& wA,
			const scalarField& rA,
			const direction cmpt = 0
		) const;

		//- Return wT the transpose-matrix preconditioned form of residual rT.
		virtual void preconditionT
		(
			scalarField& wT,
			const scalarField& rT,
			const direction cmpt = 0
		) const
		{
			return precondition(wT, rT, cmpt);
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const noPreconditioner&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noPreconditioner_Header
