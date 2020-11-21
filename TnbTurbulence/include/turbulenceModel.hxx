#pragma once
#ifndef _turbulenceModel_Header
#define _turbulenceModel_Header

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
	tnbLib::turbulenceModel

Description
	Abstract base class for turbulence models (RAS, LES and laminar).

SourceFiles
	turbulenceModel.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <primitiveFieldsFwd.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <fvMatricesFwd.hxx>
#include <nearWallDist.hxx>
#include <geometricOneField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declarations
	class fvMesh;

	/*---------------------------------------------------------------------------*\
							   Class turbulenceModel Declaration
	\*---------------------------------------------------------------------------*/

	class turbulenceModel
		:
		public IOdictionary
	{
	protected:

		// Protected data

		const Time& runTime_;
		const fvMesh& mesh_;

		const volVectorField& U_;
		const surfaceScalarField& alphaRhoPhi_;
		const surfaceScalarField& phi_;

		//- Near wall distance boundary field
		nearWallDist y_;


	public:

		//- Runtime type information
		//TypeName("turbulenceModel");
		static const char* typeName_() { return "turbulenceModel"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Default name of the turbulence properties dictionary
		static FoamTurbulence_EXPORT const word propertiesName;


		// Constructors

			//- Construct from components
		FoamTurbulence_EXPORT turbulenceModel
		(
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const word& propertiesName
		);

		//- Disallow default bitwise copy construction
		FoamTurbulence_EXPORT turbulenceModel(const turbulenceModel&) = delete;


		//- Destructor
		virtual ~turbulenceModel()
		{}


		// Member Functions

			//- Read model coefficients if they have changed
		FoamTurbulence_EXPORT virtual bool read() = 0;

		const Time& time() const
		{
			return runTime_;
		}

		const fvMesh& mesh() const
		{
			return mesh_;
		}

		//- Const access to the coefficients dictionary
		FoamTurbulence_EXPORT virtual const dictionary& coeffDict() const = 0;

		//- Helper function to return the name of the turbulence G field
		inline word GName() const
		{
			return word(type() + ":G");
		}

		//- Access function to velocity field
		inline const volVectorField& U() const
		{
			return U_;
		}

		//- Access function to phase flux field
		inline const surfaceScalarField& alphaRhoPhi() const
		{
			return alphaRhoPhi_;
		}

		//- Return the volumetric flux field
		FoamTurbulence_EXPORT virtual tmp<surfaceScalarField> phi() const;

		//- Return the near wall distances
		const nearWallDist& y() const
		{
			return y_;
		}

		//- Return the laminar viscosity
		FoamTurbulence_EXPORT virtual tmp<volScalarField> nu() const = 0;

		//- Return the laminar viscosity on patch
		FoamTurbulence_EXPORT virtual tmp<scalarField> nu(const label patchi) const = 0;

		//- Return the turbulence viscosity
		FoamTurbulence_EXPORT virtual tmp<volScalarField> nut() const = 0;

		//- Return the turbulence viscosity on patch
		FoamTurbulence_EXPORT virtual tmp<scalarField> nut(const label patchi) const = 0;

		//- Return the effective viscosity
		FoamTurbulence_EXPORT virtual tmp<volScalarField> nuEff() const = 0;

		//- Return the effective viscosity on patch
		FoamTurbulence_EXPORT virtual tmp<scalarField> nuEff(const label patchi) const = 0;

		//- Return the laminar dynamic viscosity
		FoamTurbulence_EXPORT virtual tmp<volScalarField> mu() const = 0;

		//- Return the laminar dynamic viscosity on patch
		FoamTurbulence_EXPORT virtual tmp<scalarField> mu(const label patchi) const = 0;

		//- Return the turbulence dynamic viscosity
		FoamTurbulence_EXPORT virtual tmp<volScalarField> mut() const = 0;

		//- Return the turbulence dynamic viscosity on patch
		FoamTurbulence_EXPORT virtual tmp<scalarField> mut(const label patchi) const = 0;

		//- Return the effective dynamic viscosity
		FoamTurbulence_EXPORT virtual tmp<volScalarField> muEff() const = 0;

		//- Return the effective dynamic viscosity on patch
		FoamTurbulence_EXPORT virtual tmp<scalarField> muEff(const label patchi) const = 0;

		//- Return the turbulence kinetic energy
		FoamTurbulence_EXPORT virtual tmp<volScalarField> k() const = 0;

		//- Return the turbulence kinetic energy dissipation rate
		FoamTurbulence_EXPORT virtual tmp<volScalarField> epsilon() const = 0;

		//- Return the Reynolds stress tensor
		FoamTurbulence_EXPORT virtual tmp<volSymmTensorField> R() const = 0;

		//- Validate the turbulence fields after construction
		//  Update derived fields as required
		FoamTurbulence_EXPORT virtual void validate();

		//- Solve the turbulence equations and correct the turbulence viscosity
		FoamTurbulence_EXPORT virtual void correct() = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamTurbulence_EXPORT void operator=(const turbulenceModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbulenceModel_Header
