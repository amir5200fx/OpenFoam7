#pragma once
#ifndef _scatterModel_Header
#define _scatterModel_Header

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
	tnbLib::radiationModels::scatterModel

Description
	Base class for radiation scattering

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{

		/*---------------------------------------------------------------------------*\
								Class scatterModel Declaration
		\*---------------------------------------------------------------------------*/

		class scatterModel
		{

		protected:

			// Protected data

				//- Reference to the fvMesh
			const fvMesh& mesh_;

		public:

			//- Runtime type information
			TypeName("scatterModel");

			// Declare runtime constructor selection table

			declareRunTimeSelectionTable
			(
				autoPtr,
				scatterModel,
				dictionary,
				(
					const dictionary& dict,
					const fvMesh& mesh
					),
					(dict, mesh)
			);


			// Constructors

				//- Construct from components
			scatterModel(const dictionary& dict, const fvMesh& mesh);


			// Selector

			static autoPtr<scatterModel> New
			(
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			virtual ~scatterModel();


			// Member Functions

				//- Return scatter coefficient
			virtual tmp<volScalarField> sigmaEff() const = 0;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_scatterModel_Header
