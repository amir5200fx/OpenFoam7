#pragma once
#ifndef _turbulentTransportModel_Header
#define _turbulentTransportModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
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

Typedef
	tnbLib::incompressible::turbulenceModel

Typedef
	tnbLib::incompressible::RASModel

Typedef
	tnbLib::incompressible::LESModel

Description
	Typedefs for turbulence, RAS and LES models for incompressible flow
	based on the standard laminar transport package.

SourceFiles
	turbulentTransportModel.C
	turbulentTransportModels.C

\*---------------------------------------------------------------------------*/

#include <IncompressibleTurbulenceModelTemplate.hxx>
#include <laminarModelTemplate.hxx>
#include <RASModel.hxx>
#include <LESModel.hxx>
#include <transportModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace incompressible
	{
		typedef IncompressibleTurbulenceModel<transportModel> turbulenceModel;

		typedef laminarModel<turbulenceModel> laminarModel;
		typedef RASModel<turbulenceModel> RASModel;
		typedef LESModel<turbulenceModel> LESModel;

		template<class BasicIncompressibleTurbulenceModel>
		autoPtr<BasicIncompressibleTurbulenceModel> New
		(
			const volVectorField& U,
			const surfaceScalarField& phi,
			const typename BasicIncompressibleTurbulenceModel::transportModel&
			transport,
			const word& propertiesName = turbulenceModel::propertiesName
		);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <turbulentTransportModelI.hxx>

//#ifdef NoRepository
//#include <turbulentTransportModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbulentTransportModel_Header
