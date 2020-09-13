#pragma once
#ifndef _nonlinearEddyViscosity_Header
#define _nonlinearEddyViscosity_Header

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

Class
	tnbLib::nonlinearEddyViscosity

Description
	Eddy viscosity turbulence model with non-linear correction base class

SourceFiles
	nonlinearEddyViscosity.C

\*---------------------------------------------------------------------------*/

#include <eddyViscosity.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class nonlinearEddyViscosity Declaration
	\*---------------------------------------------------------------------------*/

	template<class BasicTurbulenceModel>
	class nonlinearEddyViscosity
		:
		public eddyViscosity<BasicTurbulenceModel>
	{

	protected:

		// Protected data

			// Fields

		volSymmTensorField nonlinearStress_;


		// Protected Member Functions

		virtual void correctNonlinearStress(const volTensorField& gradU) = 0;


	public:

		typedef typename BasicTurbulenceModel::alphaField alphaField;
		typedef typename BasicTurbulenceModel::rhoField rhoField;
		typedef typename BasicTurbulenceModel::transportModel transportModel;


		// Constructors

			//- Construct from components
		nonlinearEddyViscosity
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
		virtual ~nonlinearEddyViscosity()
		{}


		// Member Functions

			//- Return the Reynolds stress tensor
		virtual tmp<volSymmTensorField> R() const;

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
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <nonlinearEddyViscosityI.hxx>

//#ifdef NoRepository
//#include <nonlinearEddyViscosity.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nonlinearEddyViscosity_Header
