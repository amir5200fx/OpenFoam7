#pragma once
#ifndef _wideBandCombustion_Header
#define _wideBandCombustion_Header

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
	tnbLib::radiationModels::absorptionEmission::wideBandCombustion

Description
	wideBandCombustion radiation absorption and emission coefficients for
	continuous phase. Exactly as wideBand, but with additional effects of the
	combustion heat release rate included.

See also
	tnbLib::radiationModels::absorptionEmissionModels::wideBand

SourceFiles
	wideBandCombustion.C

\*---------------------------------------------------------------------------*/

#include <CombustionModels_Module.hxx>
#include <wideBand.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{

			/*---------------------------------------------------------------------------*\
								   Class wideBandCombustion Declaration
			\*---------------------------------------------------------------------------*/

			class wideBandCombustion
				:
				public wideBand
			{
			private:

				//- Proportion of the heat released rate emitted
				FixedList<scalar, maxBands_> iEhrrCoeffs_;


			public:

				//- Runtime type information
				//TypeName("wideBandCombustion");
				static const char* typeName_() { return "wideBandCombustion"; }
				static FoamCombustionModels_EXPORT const ::tnbLib::word typeName;
				static FoamCombustionModels_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamCombustionModels_EXPORT wideBandCombustion(const dictionary& dict, const fvMesh& mesh);


				//- Destructor
				FoamCombustionModels_EXPORT virtual ~wideBandCombustion();


				// Member Functions

					//- Emission contribution for continuous phase
				FoamCombustionModels_EXPORT tmp<volScalarField> ECont(const label bandi = 0) const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace absorptionEmissionModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wideBandCombustion_Header
