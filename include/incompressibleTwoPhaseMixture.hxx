#pragma once
#ifndef _incompressibleTwoPhaseMixture_Header
#define _incompressibleTwoPhaseMixture_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::incompressibleTwoPhaseMixture

Description
	A two-phase incompressible transportModel

SourceFiles
	incompressibleTwoPhaseMixture.C

\*---------------------------------------------------------------------------*/

#include <transportModel.hxx>
#include <viscosityModel.hxx>
#include <twoPhaseMixture.hxx>
#include <IOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class incompressibleTwoPhaseMixture Declaration
	\*---------------------------------------------------------------------------*/

	class incompressibleTwoPhaseMixture
		:
		public IOdictionary,
		public transportModel,
		public twoPhaseMixture
	{
	protected:

		// Protected data

		autoPtr<viscosityModel> nuModel1_;
		autoPtr<viscosityModel> nuModel2_;

		dimensionedScalar rho1_;
		dimensionedScalar rho2_;

		const volVectorField& U_;
		const surfaceScalarField& phi_;

		volScalarField nu_;


		// Protected Member Functions

			//- Calculate and return the laminar viscosity
		FoamTransportModels_EXPORT void calcNu();


	public:

		//TypeName("incompressibleTwoPhaseMixture");
		static const char* typeName_() { return "incompressibleTwoPhaseMixture"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamTransportModels_EXPORT incompressibleTwoPhaseMixture
		(
			const volVectorField& U,
			const surfaceScalarField& phi
		);


		//- Destructor
		virtual ~incompressibleTwoPhaseMixture()
		{}


		// Member Functions

			//- Return const-access to phase1 viscosityModel
		const viscosityModel& nuModel1() const
		{
			return nuModel1_();
		}

		//- Return const-access to phase2 viscosityModel
		const viscosityModel& nuModel2() const
		{
			return nuModel2_();
		}

		//- Return const-access to phase1 density
		const dimensionedScalar& rho1() const
		{
			return rho1_;
		}

		//- Return const-access to phase2 density
		const dimensionedScalar& rho2() const
		{
			return rho2_;
		};

		//- Return const-access to the mixture velocity
		const volVectorField& U() const
		{
			return U_;
		}

		//- Return the dynamic laminar viscosity
		FoamTransportModels_EXPORT tmp<volScalarField> mu() const;

		//- Return the face-interpolated dynamic laminar viscosity
		FoamTransportModels_EXPORT tmp<surfaceScalarField> muf() const;

		//- Return the kinematic laminar viscosity
		virtual tmp<volScalarField> nu() const
		{
			return nu_;
		}

		//- Return the laminar viscosity for patch
		virtual tmp<scalarField> nu(const label patchi) const
		{
			return nu_.boundaryField()[patchi];
		}

		//- Return the face-interpolated kinematic laminar viscosity
		FoamTransportModels_EXPORT tmp<surfaceScalarField> nuf() const;

		//- Correct the laminar viscosity
		virtual void correct()
		{
			calcNu();
		}

		//- Read base transportProperties dictionary
		FoamTransportModels_EXPORT virtual bool read();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_incompressibleTwoPhaseMixture_Header
