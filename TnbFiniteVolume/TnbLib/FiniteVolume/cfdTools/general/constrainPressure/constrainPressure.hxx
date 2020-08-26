#pragma once
#ifndef _constrainPressure_Header
#define _constrainPressure_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::constrainPressure

Description

SourceFiles
	constrainPressure.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <IOMRFZoneList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	/*---------------------------------------------------------------------------*\
							   Class NullMRF Declaration
	\*---------------------------------------------------------------------------*/

	class NullMRF
	{
	public:

		// Constructors

			//- Construct null
		NullMRF()
		{}


		// Member Functions

			//- Return the argument unchanged
		template<class Type>
		inline const Type& relative(const Type& U) const
		{
			return U;
		}

		//- Return the argument unchanged
		template<class Type>
		inline const Type& relative(const Type& U, const label patchi) const
		{
			return U;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class RhoType, class RAUType, class MRFType>
	void constrainPressure
	(
		volScalarField& p,
		const RhoType& rho,
		const volVectorField& U,
		const surfaceScalarField& phiHbyA,
		const RAUType& rhorAU,
		const MRFType& MRF
	);

	template<class RAUType>
	void constrainPressure
	(
		volScalarField& p,
		const volScalarField& rho,
		const volVectorField& U,
		const surfaceScalarField& phiHbyA,
		const RAUType& rhorAU
	);

	template<class RAUType, class MRFType>
	void constrainPressure
	(
		volScalarField& p,
		const volVectorField& U,
		const surfaceScalarField& phiHbyA,
		const RAUType& rAU,
		const MRFType& MRF
	);

	template<class RAUType>
	void constrainPressure
	(
		volScalarField& p,
		const volVectorField& U,
		const surfaceScalarField& phiHbyA,
		const RAUType& rAU
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <constrainPressure.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constrainPressure_Header
