#pragma once
#ifndef _liquidMixtureProperties_Header
#define _liquidMixtureProperties_Header

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
	tnbLib::liquidMixtureProperties

Description
	A mixture of liquids

	An example of a two component liquid mixture:
	\verbatim
		<parentDictionary>
		{
			H2O; // employ default coefficients

			C7H16
			{
				// ... user defined properties for C7H16
			}
		}
	\endverbatim

SourceFiles
	liquidMixtureProperties.C

See also
	tnbLib::liquidProperties

\*---------------------------------------------------------------------------*/

#include <liquidProperties.hxx>
#include <PtrList.hxx>
#include <scalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class liquidMixtureProperties Declaration
	\*---------------------------------------------------------------------------*/

	class liquidMixtureProperties
	{
		// Private Data

			//- Maximum reduced temperature
		static FoamThermophysicalModels_EXPORT const scalar TrMax;

		//- The names of the liquids
		List<word> components_;

		//- The liquid properties
		PtrList<liquidProperties> properties_;


	public:

		// Constructors

			//- Construct from dictionary
		FoamThermophysicalModels_EXPORT liquidMixtureProperties(const dictionary& dict);

		//- Construct copy
		FoamThermophysicalModels_EXPORT liquidMixtureProperties(const liquidMixtureProperties& lm);

		//- Construct and return a clone
		virtual autoPtr<liquidMixtureProperties> clone() const
		{
			return autoPtr<liquidMixtureProperties>
				(
					new liquidMixtureProperties(*this)
					);
		}


		//- Destructor
		virtual ~liquidMixtureProperties()
		{}


		// Selectors

			//- Select construct from dictionary
		static FoamThermophysicalModels_EXPORT autoPtr<liquidMixtureProperties> New(const dictionary&);


		// Member Functions

			//- Return the liquid names
		inline const List<word>& components() const
		{
			return components_;
		}

		//- Return the liquid properties
		inline const PtrList<liquidProperties>& properties() const
		{
			return properties_;
		}

		//- Return the number of liquids in the mixture
		inline label size() const
		{
			return components_.size();
		}

		//- Calculate the critical temperature of mixture
		FoamThermophysicalModels_EXPORT scalar Tc(const scalarField& X) const;

		//- Invert the vapour pressure relationship to retrieve the boiling
		//  temperature of the mixture as a function of pressure
		FoamThermophysicalModels_EXPORT scalar pvInvert(const scalar p, const scalarField& X) const;

		//- Return pseudocritical temperature according to Kay's rule
		FoamThermophysicalModels_EXPORT scalar Tpc(const scalarField& X) const;

		//- Return pseudocritical pressure (modified Prausnitz and Gunn)
		FoamThermophysicalModels_EXPORT scalar Ppc(const scalarField& X) const;

		//- Return pseudo triple point temperature (mole averaged formulation)
		FoamThermophysicalModels_EXPORT scalar Tpt(const scalarField& X) const;

		//- Return mixture accentric factor
		FoamThermophysicalModels_EXPORT scalar omega(const scalarField& X) const;

		//- Return the surface molar fractions
		FoamThermophysicalModels_EXPORT scalarField Xs
		(
			const scalar p,
			const scalar Tg,
			const scalar Tl,
			const scalarField& Xg,
			const scalarField& Xl
		) const;

		//- Calculate the mean molecular weight [kg/kmol]
		//  from mole fractions
		FoamThermophysicalModels_EXPORT scalar W(const scalarField& X) const;

		//- Returns the mass fractions corresponding to the given mole fractions
		FoamThermophysicalModels_EXPORT scalarField Y(const scalarField& X) const;

		//- Returns the mole fractions corresponding to the given mass fractions
		FoamThermophysicalModels_EXPORT scalarField X(const scalarField& Y) const;

		//- Calculate the mixture density [kg/m^3]
		FoamThermophysicalModels_EXPORT scalar rho
		(
			const scalar p,
			const scalar T,
			const scalarField& X
		) const;

		//- Calculate the mixture vapour pressure [Pa]
		FoamThermophysicalModels_EXPORT scalar pv
		(
			const scalar p,
			const scalar T,
			const scalarField& X
		) const;

		//- Calculate the mixture latent heat [J/kg]
		FoamThermophysicalModels_EXPORT scalar hl
		(
			const scalar p,
			const scalar T,
			const scalarField& X
		) const;

		//- Calculate the mixture heat capacity [J/kg/K]
		FoamThermophysicalModels_EXPORT scalar Cp
		(
			const scalar p,
			const scalar T,
			const scalarField& X
		) const;

		//- Estimate mixture surface tension [N/m]
		FoamThermophysicalModels_EXPORT scalar sigma
		(
			const scalar p,
			const scalar T,
			const scalarField& X
		) const;

		//- Calculate the mixture viscosity [Pa s]
		FoamThermophysicalModels_EXPORT scalar mu
		(
			const scalar p,
			const scalar T,
			const scalarField& X
		) const;

		//- Estimate thermal conductivity  [W/m/K]
		//  Li's method, Eq. 10-12.27 - 10.12-19
		FoamThermophysicalModels_EXPORT scalar kappa
		(
			const scalar p,
			const scalar T,
			const scalarField& X
		) const;

		//- Vapour diffussivity [m2/s]
		FoamThermophysicalModels_EXPORT scalar D
		(
			const scalar p,
			const scalar T,
			const scalarField& X
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_liquidMixtureProperties_Header
