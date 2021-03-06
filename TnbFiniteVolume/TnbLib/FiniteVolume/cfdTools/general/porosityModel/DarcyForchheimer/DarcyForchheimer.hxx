#pragma once
#ifndef _DarcyForchheimer_Header
#define _DarcyForchheimer_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::porosityModels::DarcyForchheimer

Description
	Darcy-Forchheimer law porosity model, given by:

		\f[
			S = - (\mu d + \frac{\rho |U|}{2} f) U
		\f]

	where
	\vartable
		d        | Darcy coefficient [1/m^2]
		f        | Forchheimer coefficient [1/m]
	\endvartable

	Since negative Darcy/Forchheimer parameters are invalid, they can be used
	to specify a multiplier (of the max component).

	The orientation of the porous region is defined with the same notation as
	a co-ordinate system, but only a Cartesian co-ordinate system is valid.

SourceFiles
	DarcyForchheimer.C
	DarcyForchheimerTemplates.C

\*---------------------------------------------------------------------------*/

#include <porosityModel.hxx>
#include <dimensionedTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace porosityModels
	{

		/*---------------------------------------------------------------------------*\
							  Class DarcyForchheimer Declaration
		\*---------------------------------------------------------------------------*/

		class DarcyForchheimer
			:
			public porosityModel
		{
			// Private Data

				//- Darcy coeffient XYZ components (user-supplied) [1/m^2]
			dimensionedVector dXYZ_;

			//- Forchheimer coeffient XYZ components (user-supplied) [1/m]
			dimensionedVector fXYZ_;

			//- Darcy coefficient - converted from dXYZ [1/m^2]
			List<tensorField> D_;

			//- Forchheimer coefficient - converted from fXYZ [1/m]
			List<tensorField> F_;

			//- Name of density field
			word rhoName_;

			//- Name of dynamic viscosity field
			word muName_;

			//- Name of kinematic viscosity field
			word nuName_;


			// Private Member Functions

				//- Apply
			template<class RhoFieldType>
			void apply
			(
				scalarField& Udiag,
				vectorField& Usource,
				const scalarField& V,
				const RhoFieldType& rho,
				const scalarField& mu,
				const vectorField& U
			) const;

			//- Apply
			template<class RhoFieldType>
			void apply
			(
				tensorField& AU,
				const RhoFieldType& rho,
				const scalarField& mu,
				const vectorField& U
			) const;


		public:

			//- Runtime type information
			//TypeName("DarcyForchheimer");
			static const char* typeName_() { return "DarcyForchheimer"; }
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
			static FoamFiniteVolume_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

			FoamFiniteVolume_EXPORT DarcyForchheimer
			(
				const word& name,
				const word& modelType,
				const fvMesh& mesh,
				const dictionary& dict,
				const word& cellZoneName
			);

			//- Disallow default bitwise copy construction
			FoamFiniteVolume_EXPORT DarcyForchheimer(const DarcyForchheimer&) = delete;


			//- Destructor
			FoamFiniteVolume_EXPORT virtual ~DarcyForchheimer();


			// Member Functions

				//- Transform the model data wrt mesh changes
			FoamFiniteVolume_EXPORT virtual void calcTransformModelData();

			//- Calculate the porosity force
			FoamFiniteVolume_EXPORT virtual void calcForce
			(
				const volVectorField& U,
				const volScalarField& rho,
				const volScalarField& mu,
				vectorField& force
			) const;

			//- Add resistance
			FoamFiniteVolume_EXPORT virtual void correct(fvVectorMatrix& UEqn) const;

			//- Add resistance
			FoamFiniteVolume_EXPORT virtual void correct
			(
				fvVectorMatrix& UEqn,
				const volScalarField& rho,
				const volScalarField& mu
			) const;

			//- Add resistance
			FoamFiniteVolume_EXPORT virtual void correct
			(
				const fvVectorMatrix& UEqn,
				volTensorField& AU
			) const;


			// I-O

				//- Write
			FoamFiniteVolume_EXPORT bool writeData(Ostream& os) const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFiniteVolume_EXPORT void operator=(const DarcyForchheimer&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace porosityModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <DarcyForchheimerI.hxx>

//#ifdef NoRepository
//#include <DarcyForchheimerTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DarcyForchheimer_Header
