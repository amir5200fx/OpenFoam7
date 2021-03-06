#pragma once
#ifndef _LiquidEvaporation_Header
#define _LiquidEvaporation_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::LiquidEvaporation

Description
	Liquid evaporation model
	- uses ideal gas assumption

\*---------------------------------------------------------------------------*/

#include <PhaseChangeModelTemplate.hxx>
#include <liquidMixtureProperties.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamLiquidEvaporation_EXPORT __declspec(dllexport)
#else
#ifdef FoamLiquidEvaporation_EXPORT_DEFINE
#define FoamLiquidEvaporation_EXPORT __declspec(dllexport)
#else
#define FoamLiquidEvaporation_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						 Class LiquidEvaporation Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class LiquidEvaporation
		:
		public PhaseChangeModel<CloudType>
	{
	protected:

		// Protected data

			//- Global liquid properties data
		const liquidMixtureProperties& liquids_;

		//- List of active liquid names
		List<word> activeLiquids_;

		//- Mapping between liquid and carrier species
		List<label> liqToCarrierMap_;

		//- Mapping between local and global liquid species
		List<label> liqToLiqMap_;


		// Protected Member Functions

			//- Sherwood number as a function of Reynolds and Schmidt numbers
		scalar Sh(const scalar Re, const scalar Sc) const;

		//- Calculate the carrier phase component volume fractions at celli
		tmp<scalarField> calcXc(const label celli) const;


	public:

		//- Runtime type information
		//TypeName("liquidEvaporation");
		static const char* typeName_() { return "liquidEvaporation"; }
		static FoamLiquidEvaporation_EXPORT const ::tnbLib::word typeName;
		static FoamLiquidEvaporation_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		LiquidEvaporation(const dictionary& dict, CloudType& cloud);

		//- Construct copy
		LiquidEvaporation(const LiquidEvaporation<CloudType>& pcm);

		//- Construct and return a clone
		virtual autoPtr<PhaseChangeModel<CloudType>> clone() const
		{
			return autoPtr<PhaseChangeModel<CloudType>>
				(
					new LiquidEvaporation<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~LiquidEvaporation();


		// Member Functions

			//- Update model
		virtual void calculate
		(
			const scalar dt,
			const label celli,
			const scalar Re,
			const scalar Pr,
			const scalar d,
			const scalar nu,
			const scalar T,
			const scalar Ts,
			const scalar pc,
			const scalar Tc,
			const scalarField& X,
			scalarField& dMassPC
		) const;

		//- Return the enthalpy per unit mass
		virtual scalar dh
		(
			const label idc,
			const label idl,
			const scalar p,
			const scalar T
		) const;

		//- Return vapourisation temperature
		virtual scalar Tvap(const scalarField& X) const;

		//- Return maximum/limiting temperature
		virtual scalar TMax(const scalar p, const scalarField& X) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <LiquidEvaporationI.hxx>

//#ifdef NoRepository
//#include <LiquidEvaporation.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LiquidEvaporation_Header
