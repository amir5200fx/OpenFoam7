#pragma once
#ifndef _compressibleTurbulenceModel_Header
#define _compressibleTurbulenceModel_Header

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
	tnbLib::compressibleTurbulenceModel

Description
	Abstract base class for turbulence models (RAS, LES and laminar).

SourceFiles
	compressibleTurbulenceModel.C

\*---------------------------------------------------------------------------*/

#include <turbulenceModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declarations
	class fvMesh;

	/*---------------------------------------------------------------------------*\
					Class compressibleTurbulenceModel Declaration
	\*---------------------------------------------------------------------------*/

	class compressibleTurbulenceModel
		:
		public turbulenceModel
	{

	protected:

		// Protected data

		const volScalarField& rho_;


		// Protected member functions

			//- ***HGW Temporary function to be removed when the run-time selectable
			//  thermal transport layer is complete
		virtual void correctNut()
		{}


	public:

		//- Runtime type information
		//TypeName("compressibleTurbulenceModel");
		static const char* typeName_() { return "compressibleTurbulenceModel"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamTurbulence_EXPORT compressibleTurbulenceModel
		(
			const volScalarField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const word& propertiesName
		);

		//- Disallow default bitwise copy construction
		FoamTurbulence_EXPORT compressibleTurbulenceModel
		(
			const compressibleTurbulenceModel&
		) = delete;


		//- Destructor
		virtual ~compressibleTurbulenceModel()
		{}


		// Member Functions

			//- Return the density field
		const volScalarField& rho() const
		{
			return rho_;
		}

		//- Return the volumetric flux field
		FoamTurbulence_EXPORT virtual tmp<surfaceScalarField> phi() const;

		//- Return the effective stress tensor including the laminar stress
		FoamTurbulence_EXPORT virtual tmp<volSymmTensorField> devRhoReff() const = 0;

		//- Return the source term for the momentum equation
		FoamTurbulence_EXPORT virtual tmp<fvVectorMatrix> divDevRhoReff(volVectorField& U) const = 0;

		//- Correct the turbulence thermal diffusivity for energy transport
		FoamTurbulence_EXPORT virtual void correctEnergyTransport();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamTurbulence_EXPORT void operator=(const compressibleTurbulenceModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_compressibleTurbulenceModel_Header
