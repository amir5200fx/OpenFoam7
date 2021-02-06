#pragma once
#ifndef _greyMeanCombustion_Header
#define _greyMeanCombustion_Header

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
	tnbLib::radiationModels::absorptionEmission::greyMeanCombustion

Description
	greyMeanCombustion radiation absorption and emission coefficients for
	continuous phase. Exactly as greyMean, but with additional effects of the
	combustion heat release rate included.

See also
	tnbLib::radiationModels::absorptionEmissionModels::greyMean

SourceFiles
	greyMeanCombustion.C

\*---------------------------------------------------------------------------*/

#include <CombustionModels_Module.hxx>
#include <greyMean.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{

			/*---------------------------------------------------------------------------*\
									Class greyMeanCombustion Declaration
			\*---------------------------------------------------------------------------*/

			class greyMeanCombustion
				:
				public greyMean
			{
			private:

				// Private Data

					//- Emission constant coefficient
				const scalar EhrrCoeff_;


			public:

				//- Runtime type information
				//TypeName("greyMeanCombustion");
				static const char* typeName_() { return "greyMeanCombustion"; }
				static FoamCombustionModels_EXPORT const ::tnbLib::word typeName;
				static FoamCombustionModels_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamCombustionModels_EXPORT greyMeanCombustion(const dictionary& dict, const fvMesh& mesh);


				//- Destructor
				FoamCombustionModels_EXPORT virtual ~greyMeanCombustion();


				// Member Functions

					//- Emission contribution for continuous phase
				FoamCombustionModels_EXPORT tmp<volScalarField> ECont(const label bandI = 0) const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace absorptionEmissionModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_greyMeanCombustion_Header
