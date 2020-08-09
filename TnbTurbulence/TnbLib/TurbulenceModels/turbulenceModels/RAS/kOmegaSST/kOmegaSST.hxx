#pragma once
#ifndef _kOmegaSST_Header
#define _kOmegaSST_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::RASModels::kOmegaSST

Description
	Specialisation for RAS of the generic kOmegaSSTBase base class.
	For more information, see Description of kOmegaSSTBase.H

See also
	tnbLib::kOmegaSST

SourceFiles
	kOmegaSST.C

\*---------------------------------------------------------------------------*/

#include <kOmegaSSTBase.hxx>
#include <RASModel.hxx>
#include <eddyViscosity.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		/*---------------------------------------------------------------------------*\
								  Class kOmegaSST Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class kOmegaSST
			:
			public tnbLib::kOmegaSST
			<
			eddyViscosity<RASModel<BasicTurbulenceModel>>,
			BasicTurbulenceModel
			>
		{

		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			TypeName("kOmegaSST");


			// Constructors

				//- Construct from components
			kOmegaSST
			(
				const alphaField& alpha,
				const rhoField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName = turbulenceModel::propertiesName,
				const word& type = typeName
			);


			//- Destructor
			virtual ~kOmegaSST()
			{}
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#ifdef NoRepository
#include <kOmegaSST.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_kOmegaSST_Header
