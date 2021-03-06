#pragma once
#ifndef _pairPotentialList_Header
#define _pairPotentialList_Header

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
	tnbLib::pairPotentialList

Description

SourceFiles
	pairPotentialListI.H
	pairPotentialList.C

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <word.hxx>
#include <pairPotential.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class pairPotentialList Declaration
	\*---------------------------------------------------------------------------*/

	class pairPotentialList
		:
		public PtrList<pairPotential>
	{
		// Private Data

		label nIds_;

		scalar rCutMax_;

		scalar rCutMaxSqr_;

		autoPtr<pairPotential> electrostaticPotential_;


		// Private Member Functions

		inline label pairPotentialIndex
		(
			const label a,
			const label b
		) const;

		FoamLagrangian_EXPORT void readPairPotentialDict
		(
			const List<word>& idList,
			const dictionary& pairPotentialDict,
			const polyMesh& mesh
		);


	public:

		// Constructors

		FoamLagrangian_EXPORT pairPotentialList();

		//- Construct from idList and potential dictionaries
		FoamLagrangian_EXPORT pairPotentialList
		(
			const List<word>& idList,
			const dictionary& pairPotentialDict,
			const polyMesh& mesh
		);

		//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const pairPotentialList&) = delete;


		//- Destructor
		FoamLagrangian_EXPORT ~pairPotentialList();


		// Member Functions

		FoamLagrangian_EXPORT void buildPotentials
		(
			const List<word>& idList,
			const dictionary& pairPotentialDict,
			const polyMesh& mesh
		);


		// Access

		inline scalar rCutMax() const;

		inline scalar rCutMaxSqr() const;

		FoamLagrangian_EXPORT bool rCutMaxSqr(scalar rIJMagSqr) const;

		FoamLagrangian_EXPORT const pairPotential& pairPotentialFunction
		(
			const label a,
			const label b
		) const;

		// Return true if rIJ is within rCut for this pair.
		FoamLagrangian_EXPORT bool rCutSqr
		(
			const label a,
			const label b,
			const scalar rIJMagSqr
		) const;

		FoamLagrangian_EXPORT scalar rMin(const label a, const label b) const;

		FoamLagrangian_EXPORT scalar dr(const label a, const label b) const;

		FoamLagrangian_EXPORT scalar rCutSqr(const label a, const label b) const;

		FoamLagrangian_EXPORT scalar rCut(const label a, const label b) const;

		FoamLagrangian_EXPORT scalar force
		(
			const label a,
			const label b,
			const scalar rIJMag
		) const;

		FoamLagrangian_EXPORT scalar energy
		(
			const label a,
			const label b,
			const scalar rIJMag
		) const;

		inline const pairPotential& electrostatic() const;


		// Member Operators

			//- Disallow default bitwise copy construction
		FoamLagrangian_EXPORT pairPotentialList(const pairPotentialList&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pairPotentialListI.hxx>

#endif // !_pairPotentialList_Header
