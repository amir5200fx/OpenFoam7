#pragma once
#ifndef _COxidationMurphyShaddix_Header
#define _COxidationMurphyShaddix_Header

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
	tnbLib::COxidationMurphyShaddix

Description
	Limited to C(s) + O2 -> CO2

	Loosely based on the reference:
		Murphy, J. J., Shaddix, C. R., Combustion kinetics of coal chars
		in oxygen-enriched environments, Combustion and Flame 144,
		pp710-729, 2006

\*---------------------------------------------------------------------------*/

#include <SurfaceReactionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamCOxidationMurphyShaddix_EXPORT __declspec(dllexport)
#else
#ifdef FoamCOxidationMurphyShaddix_EXPORT_DEFINE
#define FoamCOxidationMurphyShaddix_EXPORT __declspec(dllexport)
#else
#define FoamCOxidationMurphyShaddix_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward class declarations
	template<class CloudType>
	class COxidationMurphyShaddix;

	/*---------------------------------------------------------------------------*\
					  Class COxidationMurphyShaddix Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class COxidationMurphyShaddix
		:
		public SurfaceReactionModel<CloudType>
	{
		// Private Data

			// Model constants

				//- Reference diffusion constant
		const scalar D0_;

		//- Reference density for reference diffusion constant
		const scalar rho0_;

		//- Reference temperature for reference diffusion constant
		const scalar T0_;

		//- Exponent for diffusion equation
		const scalar Dn_;

		//- Kinetic rate coefficient
		const scalar A_;

		//- Kinetic rate activation energy
		const scalar E_;

		//- Reaction order
		const scalar n_;

		//- Effective molecular weight of gaseous volatiles
		const scalar WVol_;


		// Static constants

			//- Maximum number of iterations
		static label maxIters_;

		//- Tolerance used in inner iterations
		static scalar tolerance_;


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
		//TypeName("COxidationMurphyShaddix");
		static const char* typeName_() { return "COxidationMurphyShaddix"; }
		static FoamCOxidationMurphyShaddix_EXPORT const ::tnbLib::word typeName;
		static FoamCOxidationMurphyShaddix_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		COxidationMurphyShaddix
		(
			const dictionary& dict,
			CloudType& owner
		);

		//- Construct copy
		COxidationMurphyShaddix
		(
			const COxidationMurphyShaddix<CloudType>& srm
		);

		//- Construct and return a clone
		virtual autoPtr<SurfaceReactionModel<CloudType>> clone() const
		{
			return autoPtr<SurfaceReactionModel<CloudType>>
				(
					new COxidationMurphyShaddix<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~COxidationMurphyShaddix();


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

#include <COxidationMurphyShaddixI.hxx>

//#ifdef NoRepository
//#include <COxidationMurphyShaddix.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_COxidationMurphyShaddix_Header
