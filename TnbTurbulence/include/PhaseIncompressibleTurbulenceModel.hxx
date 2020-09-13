#pragma once
#ifndef _PhaseIncompressibleTurbulenceModel_Header
#define _PhaseIncompressibleTurbulenceModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::PhaseIncompressibleTurbulenceModel

Description
	Templated abstract base class for multiphase incompressible
	turbulence models.

SourceFiles
	PhaseIncompressibleTurbulenceModel.C

\*---------------------------------------------------------------------------*/

#include <TurbulenceModelTemplate.hxx>
#include <incompressibleTurbulenceModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				   Class PhaseIncompressibleTurbulenceModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class TransportModel>
	class PhaseIncompressibleTurbulenceModel
		:
		public TurbulenceModel
		<
		volScalarField,
		geometricOneField,
		incompressibleTurbulenceModel,
		TransportModel
		>
	{

	public:

		typedef volScalarField alphaField;
		typedef geometricOneField rhoField;
		typedef TransportModel transportModel;


		// Constructors

			//- Construct
		PhaseIncompressibleTurbulenceModel
		(
			const word& type,
			const alphaField& alpha,
			const geometricOneField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const TransportModel& trasportModel,
			const word& propertiesName
		);


		// Selectors

			//- Return a reference to the selected turbulence model
		static autoPtr<PhaseIncompressibleTurbulenceModel> New
		(
			const alphaField& alpha,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const TransportModel& trasportModel,
			const word& propertiesName = turbulenceModel::propertiesName
		);


		//- Destructor
		virtual ~PhaseIncompressibleTurbulenceModel()
		{}


		// Member Functions

			//- Return the phase-pressure'
			// (derivative of phase-pressure w.r.t. phase-fraction)
		virtual tmp<volScalarField> pPrime() const;

		//- Return the face-phase-pressure'
		// (derivative of phase-pressure w.r.t. phase-fraction)
		virtual tmp<surfaceScalarField> pPrimef() const;

		//- Return the effective stress tensor
		virtual tmp<volSymmTensorField> devReff() const;

		//- Return the source term for the momentum equation
		virtual tmp<fvVectorMatrix> divDevReff(volVectorField& U) const;

		//- Return the effective stress tensor
		virtual tmp<volSymmTensorField> devRhoReff() const;

		//- Return the source term for the momentum equation
		virtual tmp<fvVectorMatrix> divDevRhoReff(volVectorField& U) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PhaseIncompressibleTurbulenceModelI.hxx>

//#ifdef NoRepository
//#include <PhaseIncompressibleTurbulenceModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PhaseIncompressibleTurbulenceModel_Header
