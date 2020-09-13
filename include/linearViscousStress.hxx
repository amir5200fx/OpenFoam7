#pragma once
#ifndef _linearViscousStress_Header
#define _linearViscousStress_Header

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
	tnbLib::linearViscousStress

Description
	Linear viscous stress turbulence model base class

SourceFiles
	linearViscousStress.C

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <tmp.hxx>  // added by amir
#include <word.hxx>  // added by amir
#include <surfaceFieldsFwd.hxx>  // added by amir
#include <volFieldsFwd.hxx>  // added by amir
#include <fvMatricesFwd.hxx>  // added by amir

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class linearViscousStress Declaration
	\*---------------------------------------------------------------------------*/

	template<class BasicTurbulenceModel>
	class linearViscousStress
		:
		public BasicTurbulenceModel
	{

	public:

		typedef typename BasicTurbulenceModel::alphaField alphaField;
		typedef typename BasicTurbulenceModel::rhoField rhoField;
		typedef typename BasicTurbulenceModel::transportModel transportModel;


		// Constructors

			//- Construct from components
		linearViscousStress
		(
			const word& modelName,
			const alphaField& alpha,
			const rhoField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& transport,
			const word& propertiesName
		);


		//- Destructor
		virtual ~linearViscousStress()
		{}


		// Member Functions

			//- Re-read model coefficients if they have changed
		virtual bool read() = 0;

		//- Return the effective stress tensor
		virtual tmp<volSymmTensorField> devRhoReff() const;

		//- Return the source term for the momentum equation
		virtual tmp<fvVectorMatrix> divDevRhoReff(volVectorField& U) const;

		//- Return the source term for the momentum equation
		virtual tmp<fvVectorMatrix> divDevRhoReff
		(
			const volScalarField& rho,
			volVectorField& U
		) const;

		//- Solve the turbulence equations and correct the turbulence viscosity
		virtual void correct() = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <linearViscousStressI.hxx>

//#ifdef NoRepository
//#include <linearViscousStress.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linearViscousStress_Header
