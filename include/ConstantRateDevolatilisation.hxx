#pragma once
#ifndef _ConstantRateDevolatilisation_Header
#define _ConstantRateDevolatilisation_Header

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
	tnbLib::ConstantRateDevolatilisation

Description
	Constant rate devolatisation model
	- need to set vapourisation temperature to 600 K

\*---------------------------------------------------------------------------*/

#include <DevolatilisationModel.hxx>

#include <primitiveFieldsFwd.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
					 Class ConstantRateDevolatilisation Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class ConstantRateDevolatilisation
		:
		public DevolatilisationModel<CloudType>
	{
		// Private Data

			// Model constants

				//- List of volatile data - (name A0)
		List<Tuple2<word, scalar>> volatileData_;

		//- List of initial volatile mass fractions
		List<scalar> YVolatile0_;

		//- Mapping between local and cloud gaseous species
		List<label> volatileToGasMap_;

		//- Volatile residual coefficient (0-1)
		//  When the fraction of volatiles are depleted below this
		//  threshold, combustion can occur
		const scalar residualCoeff_;


	public:

		//- Runtime type information
		TypeName("constantRateDevolatilisation");


		// Constructors

			//- Construct from dictionary
		ConstantRateDevolatilisation(const dictionary& dict, CloudType& owner);

		//- Construct copy
		ConstantRateDevolatilisation
		(
			const ConstantRateDevolatilisation<CloudType>& dm
		);

		//- Construct and return a clone
		virtual autoPtr<DevolatilisationModel<CloudType>> clone() const
		{
			return autoPtr<DevolatilisationModel<CloudType>>
				(
					new ConstantRateDevolatilisation<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~ConstantRateDevolatilisation();


		// Member Functions

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

#ifdef NoRepository
#include <ConstantRateDevolatilisation.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ConstantRateDevolatilisation_Header
