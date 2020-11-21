#pragma once
#ifndef _compressibleTransportModel_Header
#define _compressibleTransportModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
	tnbLib::compressibleTransportModel

Description
	Base-class for all transport models used by the compressible turbulence
	models.

SourceFiles
	compressibleTransportModel.C

\*---------------------------------------------------------------------------*/

#include <primitiveFieldsFwd.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>

#include <tmp.hxx> // added by amir
#include <typeInfo.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class compressibleTransportModel Declaration
	\*---------------------------------------------------------------------------*/

	class compressibleTransportModel
	{
	public:

		//- Runtime type information
		//TypeName("compressibleTransportModel");
		static const char* typeName_() { return "compressibleTransportModel"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamTransportModels_EXPORT compressibleTransportModel
		();

		//- Disallow default bitwise copy construction
		FoamTransportModels_EXPORT compressibleTransportModel(const compressibleTransportModel&);


		//- Destructor
		FoamTransportModels_EXPORT virtual ~compressibleTransportModel();


		// Member Functions

			//- Return the dynamic laminar viscosity
		FoamTransportModels_EXPORT virtual tmp<volScalarField> mu() const = 0;

		//- Return the dynamic laminar viscosity for patch
		FoamTransportModels_EXPORT virtual tmp<scalarField> mu(const label patchi) const = 0;

		//- Return the laminar viscosity
		FoamTransportModels_EXPORT virtual tmp<volScalarField> nu() const = 0;

		//- Return the laminar viscosity for patch
		FoamTransportModels_EXPORT virtual tmp<scalarField> nu(const label patchi) const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamTransportModels_EXPORT void operator=(const compressibleTransportModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_compressibleTransportModel_Header
