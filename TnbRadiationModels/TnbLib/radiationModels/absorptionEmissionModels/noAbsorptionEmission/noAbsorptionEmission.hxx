#pragma once
#ifndef _noAbsorptionEmission_Header
#define _noAbsorptionEmission_Header

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
	tnbLib::radiationModels::absorptionEmissionsModels::noAbsorptionEmission

Description
	Dummy absorption-emission model for 'none'

SourceFiles
	noAbsorptionEmission.C

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
							  Class noAbsorptionEmission Declaration
			\*---------------------------------------------------------------------------*/

			class noAbsorptionEmission
				:
				public absorptionEmissionModel
			{

			public:

				//- Runtime type information
				//TypeName("none");
				static const char* typeName_() { return "none"; }
				static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
				static FoamRadiationModels_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamRadiationModels_EXPORT noAbsorptionEmission(const dictionary& dict, const fvMesh& mesh);


				//- Destructor
				FoamRadiationModels_EXPORT virtual ~noAbsorptionEmission();
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace absorptionEmissionModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noAbsorptionEmission_Header
