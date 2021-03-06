#pragma once
#ifndef _COxidationIntrinsicRate_Header
#define _COxidationIntrinsicRate_Header

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
	tnbLib::COxidationIntrinsicRate

Description
	Intrinsic char surface reaction mndel

		C(s) + Sb*O2 -> CO2

	where Sb is the stoichiometry of the reaction

\*---------------------------------------------------------------------------*/

#include <SurfaceReactionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamCOxidationIntrinsicRate_EXPORT __declspec(dllexport)
#else
#ifdef FoamCOxidationIntrinsicRate_EXPORT_DEFINE
#define FoamCOxidationIntrinsicRate_EXPORT __declspec(dllexport)
#else
#define FoamCOxidationIntrinsicRate_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// Forward class declarations
	template<class CloudType>
	class COxidationIntrinsicRate;

	/*---------------------------------------------------------------------------*\
					   Class COxidationIntrinsicRate Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class COxidationIntrinsicRate
		:
		public SurfaceReactionModel<CloudType>
	{
		// Private Data

			// Model constants

				//- Stoichiometry of reaction []
		const scalar Sb_;

		//- Mass diffusion limited rate constant
		const scalar C1_;

		//- Mean pore radius [m]
		const scalar rMean_;

		//- Char porosity [] = 1 - rho_apparent/rho_true
		const scalar theta_;

		//- Pre-exponential factor
		const scalar Ai_;

		//- Activation energy
		const scalar Ei_;

		//- Char specific internal area [m2/kg]
		const scalar Ag_;

		//- Pore tortuosity []; default to sqrt(2)
		const scalar tau_;


		// Addressing

			//- Cs positions in global/local lists
		label CsLocalId_;

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


	public:

		//- Runtime type information
		//TypeName("COxidationIntrinsicRate");
		static const char* typeName_() { return "COxidationIntrinsicRate"; }
		static FoamCOxidationIntrinsicRate_EXPORT const ::tnbLib::word typeName;
		static FoamCOxidationIntrinsicRate_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		COxidationIntrinsicRate
		(
			const dictionary& dict,
			CloudType& owner
		);

		//- Construct copy
		COxidationIntrinsicRate
		(
			const COxidationIntrinsicRate<CloudType>& srm
		);

		//- Construct and return a clone
		virtual autoPtr<SurfaceReactionModel<CloudType>> clone() const
		{
			return autoPtr<SurfaceReactionModel<CloudType>>
				(
					new COxidationIntrinsicRate<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~COxidationIntrinsicRate();


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

#include <COxidationIntrinsicRateI.hxx>

//#ifdef NoRepository
//#include <COxidationIntrinsicRate.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_COxidationIntrinsicRate_Header
