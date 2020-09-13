#pragma once
#ifndef _temperatureDependentSurfaceTension_Header
#define _temperatureDependentSurfaceTension_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::surfaceTensionModels::temperatureDependent

Description
	Temperature-dependent surface tension model.

	The surface tension is evaluated from the specified tnbLib::Function1 for the
	temperature field looked-up from the mesh database the name of which
	may optionally be provided.

Usage
	\table
		Property     | Description               | Required    | Default value
		T            | Temperature field name    | no          | T
		sigma        | Surface tension function  | yes         |
	\endtable

	Example of the surface tension specification:
	\verbatim
		sigma
		{
			type                temperatureDependent;
			sigma               constant 0.07;
		}
	\endverbatim

See also
	tnbLib::surfaceTensionModel
	tnbLib::Function1

SourceFiles
	temperatureDependentSurfaceTension.C

\*---------------------------------------------------------------------------*/

#include <surfaceTensionModel.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace surfaceTensionModels
	{

		/*---------------------------------------------------------------------------*\
								   Class temperatureDependent Declaration
		\*---------------------------------------------------------------------------*/

		class temperatureDependent
			:
			public surfaceTensionModel
		{
			// Private Data

				//- Name of temperature field, default = "T"
			word TName_;

			//- Surface-tension function
			autoPtr<Function1<scalar>> sigma_;


		public:

			//- Runtime type information
			TypeName("temperatureDependent");


			// Constructors

				//- Construct from dictionary and mesh
			temperatureDependent
			(
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			virtual ~temperatureDependent();


			// Member Functions

				//- Surface tension coefficient
			virtual tmp<volScalarField> sigma() const;

			//- Update surface tension coefficient from given dictionary
			virtual bool readDict(const dictionary& dict);

			//- Write in dictionary format
			virtual bool writeData(Ostream& os) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace surfaceTensionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_temperatureDependentSurfaceTension_Header
