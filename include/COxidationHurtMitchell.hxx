#pragma once
#ifndef _COxidationHurtMitchell_Header
#define _COxidationHurtMitchell_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::COxidationHurtMitchell

Description
	Char oxidation model given by Hurt and Mitchell:

	Based on the reference:
		Hurt R. and Mitchell R., "Unified high-temperature char combustion
		kinetics for a suite of coals of various rank", 24th Symposium in
		Combustion, The Combustion Institute, 1992, p 1243-1250

	Model specifies the rate of char combustion.

		C(s) + Sb*O2 -> CO2

	where Sb is the stoichiometry of the reaction

	Model validity:
		Gas temperature: Tc > 1500 K
		Particle sizes:  75 um -> 200 um
		Pox > 0.3 atm

\*---------------------------------------------------------------------------*/

#include <SurfaceReactionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamCOxidationHurtMitchell_EXPORT __declspec(dllexport)
#else
#ifdef FoamCOxidationHurtMitchell_EXPORT_DEFINE
#define FoamCOxidationHurtMitchell_EXPORT __declspec(dllexport)
#else
#define FoamCOxidationHurtMitchell_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward class declarations
	template<class CloudType>
	class COxidationHurtMitchell;

	/*---------------------------------------------------------------------------*\
					  Class COxidationHurtMitchell Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class COxidationHurtMitchell
		:
		public SurfaceReactionModel<CloudType>
	{
		// Private Data

			// Model constants

				//- Stoichiometry of reaction
		const scalar Sb_;


		// Addressing

			//- Cs position in global/local lists
		label CsLocalId_;

		//- Ash position in global/local lists
		label ashLocalId_;

		//- O2 position in global list
		label O2GlobalId_;

		//- CO2 positions in global list
		label CO2GlobalId_;


		// Local copies of thermo properties

			//- Molecular weight of C [kg/kmol]
		scalar WC_;

		//- Molecular weight of O2 [kg/kmol]
		scalar WO2_;

		//- Formation enthalpy for CO2 [J/kg]
		scalar HcCO2_;

		//- Heat of reaction [J/kg] (optional)
		scalar heatOfReaction_;


	public:

		//- Runtime type information
		//TypeName("COxidationHurtMitchell");
		static const char* typeName_() { return "COxidationHurtMitchell"; }
		static FoamCOxidationHurtMitchell_EXPORT const ::tnbLib::word typeName;
		static FoamCOxidationHurtMitchell_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		COxidationHurtMitchell
		(
			const dictionary& dict,
			CloudType& owner
		);

		//- Construct copy
		COxidationHurtMitchell
		(
			const COxidationHurtMitchell<CloudType>& srm
		);

		//- Construct and return a clone
		virtual autoPtr<SurfaceReactionModel<CloudType>> clone() const
		{
			return autoPtr<SurfaceReactionModel<CloudType>>
				(
					new COxidationHurtMitchell<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~COxidationHurtMitchell();


		// Member Functions

			//- Update surface reactions
		virtual scalar calculate
		(
			const scalar dt,
			const label celli,
			const scalar d,
			const scalar T,
			const scalar Tc,
			const scalar pc,
			const scalar rhoc,
			const scalar mass,
			const scalarField& YGas,
			const scalarField& YLiquid,
			const scalarField& YSolid,
			const scalarField& YMixture,
			const scalar N,
			scalarField& dMassGas,
			scalarField& dMassLiquid,
			scalarField& dMassSolid,
			scalarField& dMassSRCarrier
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <COxidationHurtMitchellI.hxx>

//#ifdef NoRepository
//#include <COxidationHurtMitchell.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_COxidationHurtMitchell_Header
