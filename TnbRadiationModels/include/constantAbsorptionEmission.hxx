#pragma once
#ifndef _constantAbsorptionEmission_Header
#define _constantAbsorptionEmission_Header

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
	tnbLib::radiationModels::absorptionEmissionModels::constant

Description
	Constant radiation absorption and emission coefficients for continuous
	phase

SourceFiles
	constantAbsorptionEmission.C

\*---------------------------------------------------------------------------*/

#include <absorptionEmissionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{

			/*---------------------------------------------------------------------------*\
									  Class constant Declaration
			\*---------------------------------------------------------------------------*/

			class constant
				:
				public absorptionEmissionModel
			{
				// Private Data

					//- Absorption model dictionary
				dictionary coeffsDict_;

				//- Absorption coefficient / [1/m]
				dimensionedScalar a_;

				//- Emission coefficient / [1/m]
				dimensionedScalar e_;

				//- Emission contribution / [kg/m/s^3]
				dimensionedScalar E_;


			public:

				//- Runtime type information
				//TypeName("constant");
				static const char* typeName_() { return "constant"; }
				static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
				static FoamRadiationModels_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamRadiationModels_EXPORT constant(const dictionary& dict, const fvMesh& mesh);


				//- Destructor
				FoamRadiationModels_EXPORT virtual ~constant();


				// Member Functions

					// Access

						// Absorption coefficient

							//- Absorption coefficient for continuous phase
				FoamRadiationModels_EXPORT tmp<volScalarField> aCont(const label bandI = 0) const;


				// Emission coefficient

					//- Emission coefficient for continuous phase
				FoamRadiationModels_EXPORT tmp<volScalarField> eCont(const label bandI = 0) const;


				// Emission contribution

					//- Emission contribution for continuous phase
				FoamRadiationModels_EXPORT tmp<volScalarField> ECont(const label bandI = 0) const;


				// Member Functions

				inline bool isGrey() const
				{
					return true;
				}
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace absorptionEmissionModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantAbsorptionEmission_Header
