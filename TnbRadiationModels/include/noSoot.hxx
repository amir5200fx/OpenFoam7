#pragma once
#ifndef _noSoot_Header
#define _noSoot_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::radiationModels::sootModels::noSoot

Description
	Dummy soot model for 'none'

SourceFiles
	noSoot.C

\*---------------------------------------------------------------------------*/

#include <sootModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace sootModels
		{

			/*---------------------------------------------------------------------------*\
								Class noSoot Declaration
			\*---------------------------------------------------------------------------*/

			class noSoot
				:
				public sootModel
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
				FoamRadiationModels_EXPORT noSoot(const dictionary& dict, const fvMesh& mesh, const word&);


				//- Destructor
				FoamRadiationModels_EXPORT virtual ~noSoot();


				// Member Functions

					// Edit

						//- Main update/correction routine
				FoamRadiationModels_EXPORT void correct();

				// Access

					//- Return Ysoot
				FoamRadiationModels_EXPORT const volScalarField& soot() const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace sootModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noSoot_Header
