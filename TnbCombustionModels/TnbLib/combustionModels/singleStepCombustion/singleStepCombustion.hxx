#pragma once
#ifndef _singleStepCombustion_Header
#define _singleStepCombustion_Header

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
	tnbLib::combustionModels::singleStepCombustion

Description
	Base class for combustion models using singleStepReactingMixture.

SourceFiles
	singleStepCombustion.C

\*---------------------------------------------------------------------------*/

#include <ThermoCombustionTemplate.hxx>
#include <singleStepReactingMixture.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace combustionModels
	{

		/*---------------------------------------------------------------------------*\
							Class singleStepCombustion Declaration
		\*---------------------------------------------------------------------------*/

		template<class ReactionThermo, class ThermoType>
		class singleStepCombustion
			:
			public ThermoCombustion<ReactionThermo>
		{
		protected:

			// Protected data

				//- Pointer to singleStepReactingMixture mixture
			singleStepReactingMixture<ThermoType>* singleMixturePtr_;

			//- Fuel consumption rate
			volScalarField wFuel_;

			//- Semi-implicit (true) or explicit (false) treatment
			bool semiImplicit_;


		public:

			// Constructors

				//- Construct from components
			singleStepCombustion
			(
				const word& modelType,
				ReactionThermo& thermo,
				const compressibleTurbulenceModel& turb,
				const word& combustionProperties
			);

			//- Disallow default bitwise copy construction
			singleStepCombustion(const singleStepCombustion&);


			//- Destructor
			virtual ~singleStepCombustion();


			// Member Functions

				//- Fuel consumption rate matrix
			virtual tmp<fvScalarMatrix> R(volScalarField& Y) const;

			//- Heat release rate [kg/m/s^3]
			virtual tmp<volScalarField> Qdot() const;

			//- Update properties from given dictionary
			virtual bool read();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const singleStepCombustion&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace combustionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <singleStepCombustionI.hxx>

//#ifdef NoRepository
//#include "singleStepCombustion.cxx"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_singleStepCombustion_Header
