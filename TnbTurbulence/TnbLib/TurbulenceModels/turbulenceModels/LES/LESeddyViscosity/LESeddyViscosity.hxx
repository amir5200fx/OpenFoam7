#pragma once
#ifndef _LESeddyViscosity_Header
#define _LESeddyViscosity_Header

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
	tnbLib::LESModels::LESeddyViscosity

Description
	Eddy viscosity LES SGS model base class

SourceFiles
	LESeddyViscosity.C

\*---------------------------------------------------------------------------*/

#include <LESModel.hxx>
#include <eddyViscosity.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
								   Class LESeddyViscosity Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class LESeddyViscosity
			:
			public eddyViscosity<LESModel<BasicTurbulenceModel>>
		{
		protected:

			// Protected data

			dimensionedScalar Ce_;


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			// Constructors

				//- Construct from components
			LESeddyViscosity
			(
				const word& type,
				const alphaField& alpha,
				const rhoField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName = turbulenceModel::propertiesName
			);

			//- Disallow default bitwise copy construction
			LESeddyViscosity(const LESeddyViscosity&) = delete;


			//- Destructor
			virtual ~LESeddyViscosity()
			{}


			// Member Functions

				//- Read model coefficients if they have changed
			virtual bool read();

			//- Return sub-grid disipation rate
			virtual tmp<volScalarField> epsilon() const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const LESeddyViscosity&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <LESeddyViscosityI.hxx>

//#ifdef NoRepository
//#include <LESeddyViscosity.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LESeddyViscosity_Header
