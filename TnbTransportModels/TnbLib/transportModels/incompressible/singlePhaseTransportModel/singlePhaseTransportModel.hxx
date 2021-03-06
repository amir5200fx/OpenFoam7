#pragma once
#ifndef _singlePhaseTransportModel_Header
#define _singlePhaseTransportModel_Header

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
	tnbLib::singlePhaseTransportModel

Description
	A simple single-phase transport model based on viscosityModel.

	Used by the incompressible single-phase solvers like simpleFoam,
	turbFoam etc.

SourceFiles
	singlePhaseTransportModel.C

\*---------------------------------------------------------------------------*/

#include <transportModel.hxx>
#include <IOdictionary.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class viscosityModel;

	/*---------------------------------------------------------------------------*\
					Class singlePhaseTransportModel Declaration
	\*---------------------------------------------------------------------------*/

	class singlePhaseTransportModel
		:
		public IOdictionary,
		public transportModel
	{
		// Private Data

		autoPtr<viscosityModel> viscosityModelPtr_;


	public:

		//- Runtime type information
		//TypeName("singlePhaseTransportModel");
		static const char* typeName_() { return "singlePhaseTransportModel"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamTransportModels_EXPORT singlePhaseTransportModel
		(
			const volVectorField& U,
			const surfaceScalarField& phi
		);

		//- Disallow default bitwise copy construction
		FoamTransportModels_EXPORT singlePhaseTransportModel(const singlePhaseTransportModel&);


		//- Destructor
		FoamTransportModels_EXPORT virtual ~singlePhaseTransportModel();


		// Member Functions

			//- Return the laminar viscosity
		FoamTransportModels_EXPORT virtual tmp<volScalarField> nu() const;

		//- Return the laminar viscosity for patch
		FoamTransportModels_EXPORT virtual tmp<scalarField> nu(const label patchi) const;

		//- Correct the laminar viscosity
		FoamTransportModels_EXPORT virtual void correct();

		//- Read transportProperties dictionary
		FoamTransportModels_EXPORT virtual bool read();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamTransportModels_EXPORT void operator=(const singlePhaseTransportModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_singlePhaseTransportModel_Header
