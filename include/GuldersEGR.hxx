#pragma once
#ifndef _GuldersEGR_Header
#define _GuldersEGR_Header

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
	tnbLib::laminarFlameSpeedModels::GuldersEGR

Description
	Laminar flame speed obtained from Gulder's correlation with EGR modelling.

SourceFiles
	GuldersEGR.C

\*---------------------------------------------------------------------------*/

#include <laminarFlameSpeed.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarFlameSpeedModels
	{

		/*---------------------------------------------------------------------------*\
								   Class GuldersEGR Declaration
		\*---------------------------------------------------------------------------*/

		class GuldersEGR
			:
			public laminarFlameSpeed
		{
			// Private Data

			dictionary coeffsDict_;

			scalar W_;
			scalar eta_;
			scalar xi_;
			scalar f_;
			scalar alpha_;
			scalar beta_;


			// Private Member Functions

			FoamThermophysicalModels_EXPORT inline scalar SuRef
			(
				scalar phi
			) const;

			FoamThermophysicalModels_EXPORT inline scalar Su0pTphi
			(
				scalar p,
				scalar Tu,
				scalar phi,
				scalar Yres
			) const;

			FoamThermophysicalModels_EXPORT tmp<volScalarField> Su0pTphi
			(
				const volScalarField& p,
				const volScalarField& Tu,
				scalar phi
			) const;

			FoamThermophysicalModels_EXPORT tmp<volScalarField> Su0pTphi
			(
				const volScalarField& p,
				const volScalarField& Tu,
				const volScalarField& phi,
				const volScalarField& egr
			) const;

			//- Construct as copy (not implemented)
			FoamThermophysicalModels_EXPORT GuldersEGR(const GuldersEGR&);

			FoamThermophysicalModels_EXPORT void operator=(const GuldersEGR&);


		public:

			//- Runtime type information
			//TypeName("GuldersEGR");
			static const char* typeName_() { return "GuldersEGR"; }
			static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
			static FoamThermophysicalModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

				//- Construct from dictionary and psiuReactionThermo
			FoamThermophysicalModels_EXPORT GuldersEGR
			(
				const dictionary&,
				const psiuReactionThermo&
			);


			//- Destructor
			FoamThermophysicalModels_EXPORT virtual ~GuldersEGR();


			// Member Functions

				//- Return the laminar flame speed [m/s]
			FoamThermophysicalModels_EXPORT tmp<volScalarField> operator()() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End laminarFlameSpeedModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GuldersEGR_Header
