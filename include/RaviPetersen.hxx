#pragma once
#ifndef _RaviPetersen_Header
#define _RaviPetersen_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::laminarFlameSpeedModels::RaviPetersen

Description
	Laminar flame speed obtained from Ravi and Petersen's correlation.

	The correlation for the laminar flame speed \f$Su\f$ is of the following
	form:
	\f[
		Su = \left( \sum \alpha_i \phi^i \right)
		\left( \frac{T}{T_{ref}} \right)^{\left( \sum \beta_j \phi^j \right)}
	\f]

	Where \f$\phi\f$ is the equivalence ratio, and \f$\alpha\f$ and \f$\beta\f$
	are polynomial coefficients given for a number of pressure and equivalence
	ratio points.

SourceFiles
	RaviPetersen.C

\*---------------------------------------------------------------------------*/

#include <laminarFlameSpeed.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarFlameSpeedModels
	{

		/*---------------------------------------------------------------------------*\
								Class RaviPetersen Declaration
		\*---------------------------------------------------------------------------*/

		class RaviPetersen
			:
			public laminarFlameSpeed
		{
			// Private Data

			dictionary coeffsDict_;

			//- Correlation pressure values
			List<scalar> pPoints_;

			//- Correlation equivalence ratios
			List<scalar> EqRPoints_;

			//- Correlation alpha coefficients
			List<List<List<scalar>>> alpha_;

			//- Correlation beta coefficients
			List<List<List<scalar>>> beta_;

			//- Reference temperature
			scalar TRef_;


			// Private Member Functions

				//- Check that input points are ordered
			FoamThermophysicalModels_EXPORT void checkPointsMonotonicity
			(
				const word& name,
				const List<scalar>& x
			) const;

			//- Check that the coefficient arrays are of the correct shape
			FoamThermophysicalModels_EXPORT void checkCoefficientArrayShape
			(
				const word& name,
				const List<List<List<scalar>>>& x
			) const;

			//- Find and interpolate a value in the data point arrays
			FoamThermophysicalModels_EXPORT inline bool interval
			(
				const List<scalar>& xPoints,
				const scalar x,
				label& xIndex,
				scalar& xXi,
				scalar& xLim
			) const;

			//- Evaluate a polynomial
			FoamThermophysicalModels_EXPORT inline scalar polynomial
			(
				const List<scalar>& coeffs,
				const scalar x
			) const;

			//- Evaluate a polynomial differential
			FoamThermophysicalModels_EXPORT inline scalar dPolynomial
			(
				const List<scalar>& coeffs,
				const scalar x
			) const;

			//- Calculate normalised temperature to the power of the B polynomial
			FoamThermophysicalModels_EXPORT inline scalar THatPowB
			(
				const label EqRIndex,
				const label pIndex,
				const scalar EqR,
				const scalar Tu
			) const;

			//- Return the flame speed within the correlation range
			FoamThermophysicalModels_EXPORT inline scalar correlationInRange
			(
				const label EqRIndex,
				const label pIndex,
				const scalar EqR,
				const scalar Tu
			) const;

			//- Extrapolate the flame speed correlation outside its range
			FoamThermophysicalModels_EXPORT inline scalar correlationOutOfRange
			(
				const label EqRIndex,
				const label pIndex,
				const scalar EqR,
				const scalar EqRLim,
				const scalar Tu
			) const;

			//- Return the laminar flame speed [m/s]
			FoamThermophysicalModels_EXPORT inline scalar speed
			(
				const scalar EqR,
				const scalar p,
				const scalar Tu
			) const;


			//- Construct as copy (not implemented)
			FoamThermophysicalModels_EXPORT RaviPetersen(const RaviPetersen&);
			FoamThermophysicalModels_EXPORT void operator=(const RaviPetersen&);


		public:

			//- Runtime type information
			//TypeName("RaviPetersen");
			static const char* typeName_() { return "RaviPetersen"; }
			static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
			static FoamThermophysicalModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

				//- Construct from dictionary and psiuReactionThermo
			FoamThermophysicalModels_EXPORT RaviPetersen
			(
				const dictionary&,
				const psiuReactionThermo&
			);


			//- Destructor
			FoamThermophysicalModels_EXPORT virtual ~RaviPetersen();


			// Member Functions

				//- Return the laminar flame speed [m/s]
			FoamThermophysicalModels_EXPORT tmp<volScalarField> operator()() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End laminarFlameSpeedModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_RaviPetersen_Header
