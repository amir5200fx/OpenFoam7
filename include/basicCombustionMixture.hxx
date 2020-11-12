#pragma once
#ifndef _basicCombustionMixture_Header
#define _basicCombustionMixture_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
	tnbLib::basicCombustionMixture

Description
	Specialization of the basicSpecieMixture for combustion.

SourceFiles
	basicCombustionMixture.C

\*---------------------------------------------------------------------------*/

#include <basicSpecieMixture.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class basicCombustionMixture Declaration
	\*---------------------------------------------------------------------------*/

	class basicCombustionMixture
		:
		public basicSpecieMixture
	{

	public:

		//- Run time type information
		//TypeName("basicCombustionMixture");
		static const char* typeName_() { return "basicCombustionMixture"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- The base class of the mixture
		typedef basicCombustionMixture basicMixtureType;


		// Constructors

			//- Construct from dictionary, specie names, mesh and phase name
		FoamThermophysicalModels_EXPORT basicCombustionMixture
		(
			const dictionary&,
			const wordList& specieNames,
			const fvMesh&,
			const word&
		);


		//- Destructor
		virtual ~basicCombustionMixture()
		{}


		// Member Functions

		inline scalar fres(const scalar ft, const scalar stoicRatio) const;

		inline tmp<volScalarField> fres
		(
			const volScalarField& ft,
			const dimensionedScalar& stoicRatio
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <basicCombustionMixtureI.hxx>

#endif // !_basicCombustionMixture_Header
