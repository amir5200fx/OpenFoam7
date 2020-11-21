#pragma once
#ifndef _cloudAbsorptionEmission_Header
#define _cloudAbsorptionEmission_Header

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
	tnbLib::radiationModels::absorptionEmissionModels::cloud

Description
	Retrieves absorption/emission data from a cloud object

SourceFiles
	cloudAbsorptionEmission.C

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
										Class cloud Declaration
			\*---------------------------------------------------------------------------*/

			class cloud
				:
				public absorptionEmissionModel
			{
				// Private Data

					//- Coefficients dictionary
				dictionary coeffsDict_;

				//- Cloud name(s)
				const wordList cloudNames_;


			public:

				//- Runtime type information
				//TypeName("cloud");
				static const char* typeName_() { return "cloud"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamLagrangian_EXPORT cloud(const dictionary& dict, const fvMesh& mesh);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~cloud();


				// Member Functions

					//- Absorption coefficient for dispersed phase
				FoamLagrangian_EXPORT virtual tmp<volScalarField> aDisp(const label bandI = 0) const;

				//- Emission coefficient for dispersed phase
				FoamLagrangian_EXPORT virtual tmp<volScalarField> eDisp(const label bandI = 0) const;

				//- Return emission contribution for dispersed phase
				FoamLagrangian_EXPORT virtual tmp<volScalarField> EDisp(const label bandI = 0) const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace absorptionEmissionModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cloudAbsorptionEmission_Header
