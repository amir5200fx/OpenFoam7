#pragma once
#ifndef _pureMixture_Header
#define _pureMixture_Header

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
	tnbLib::pureMixture

Description
	tnbLib::pureMixture

SourceFiles
	pureMixture.C

\*---------------------------------------------------------------------------*/

#include <basicMixture.hxx>
#include <scalar.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class pureMixture Declaration
	\*---------------------------------------------------------------------------*/

	template<class ThermoType>
	class pureMixture
		:
		public basicMixture
	{
		// Private Data

		ThermoType mixture_;

		//- Construct as copy (not implemented)
		pureMixture(const pureMixture<ThermoType>&);


	public:

		//- The type of thermodynamics this mixture is instantiated for
		typedef ThermoType thermoType;


		// Constructors

			//- Construct from dictionary, mesh and phase name
		pureMixture(const dictionary&, const fvMesh&, const word&);


		// Member Functions

			//- Return the instantiated type name
		static word typeName()
		{
			return "pureMixture<" + ThermoType::typeName() + '>';
		}

		const ThermoType& mixture() const
		{
			return mixture_;
		}

		const ThermoType& cellMixture(const label) const
		{
			return mixture_;
		}

		const ThermoType& patchFaceMixture
		(
			const label,
			const label
		) const
		{
			return mixture_;
		}

		const ThermoType& cellVolMixture
		(
			const scalar,
			const scalar,
			const label
		) const
		{
			return mixture_;
		}

		const ThermoType& patchFaceVolMixture
		(
			const scalar,
			const scalar,
			const label,
			const label
		) const
		{
			return mixture_;
		}

		//- Read dictionary
		void read(const dictionary&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#include <pureMixtureI.hxx>

//#ifdef NoRepository
//#include <pureMixture.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pureMixture_Header
