#pragma once
#ifndef _NoDevolatilisation_Header
#define _NoDevolatilisation_Header

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
	tnbLib::NoDevolatilisation

Description
	Dummy devolatilisation model for 'none'

\*---------------------------------------------------------------------------*/

#include <DevolatilisationModel.hxx>
#include <primitiveFieldsFwd.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoDevolatilisation_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoDevolatilisation_EXPORT_DEFINE
#define FoamNoDevolatilisation_EXPORT __declspec(dllexport)
#else
#define FoamNoDevolatilisation_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						 Class NoDevolatilisation Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoDevolatilisation
		:
		public DevolatilisationModel<CloudType>
	{

	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamNoDevolatilisation_EXPORT const ::tnbLib::word typeName;
		static FoamNoDevolatilisation_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		NoDevolatilisation(const dictionary&, CloudType& owner);

		//- Construct copy
		NoDevolatilisation(const NoDevolatilisation<CloudType>& dm);

		//- Construct and return a clone
		virtual autoPtr<DevolatilisationModel<CloudType>> clone() const
		{
			return autoPtr<DevolatilisationModel<CloudType>>
				(
					new NoDevolatilisation<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoDevolatilisation();


		// Member Functions

			//- Flag to indicate whether model activates devolatilisation model
		virtual bool active() const;

		//- Update model
		virtual void calculate
		(
			const scalar dt,
			const scalar age,
			const scalar mass0,
			const scalar mass,
			const scalar T,
			const scalarField& YGasEff,
			const scalarField& YLiquidEff,
			const scalarField& YSolidEff,
			label& canCombust,
			scalarField& dMassDV
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoDevolatilisationI.hxx>

//#ifdef NoRepository
//#include <NoDevolatilisation.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoDevolatilisation_Header
