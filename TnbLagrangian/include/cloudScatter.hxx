#pragma once
#ifndef _cloudScatter_Header
#define _cloudScatter_Header

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
	tnbLib::radiationModels::scatterModels::cloud

Description
	Cloud radiation scatter model

SourceFiles
	scatterModel.C

\*---------------------------------------------------------------------------*/

#include <scatterModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace scatterModels
		{

			/*---------------------------------------------------------------------------*\
										Class cloud Declaration
			\*---------------------------------------------------------------------------*/

			class cloud
				:
				public scatterModel
			{
				// Private Data

					//- Absorption model dictionary
				dictionary coeffsDict_;

				//- Cloud names
				wordList cloudNames_;


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

					//- Return scatter coefficient
				FoamLagrangian_EXPORT tmp<volScalarField> sigmaEff() const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace scatterModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cloudScatter_Header
