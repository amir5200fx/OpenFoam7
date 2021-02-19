#pragma once
#ifndef _powerLawLopesdaCosta_Header
#define _powerLawLopesdaCosta_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::porosityModels::powerLawLopesdaCosta

Description
	Variant of the power law porosity model with spatially varying
	drag coefficient

	given by:

		\f[
			S = -\rho C_d \Sigma |U|^{(C_1 - 1)} U
		\f]

	where
	\vartable
		\Sigma | Porosity surface area per unit volume
		C_d    | Model linear coefficient
		C_1    | Model exponent coefficient
	\endvartable

	Reference:
	\verbatim
		Costa, J. C. P. L. D. (2007).
		Atmospheric flow over forested and non-forested complex terrain.
	\endverbatim

See also
	tnbLib::RASModels::kEpsilonLopesdaCosta

SourceFiles
	powerLawLopesdaCosta.C
	powerLawLopesdaCostaTemplates.C

\*---------------------------------------------------------------------------*/

#include <AtmosphericModels_Module.hxx>
#include <porosityModel.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace porosityModels
	{

		/*---------------------------------------------------------------------------*\
						  Class powerLawLopesdaCostaZone Declaration
		\*---------------------------------------------------------------------------*/

		class powerLawLopesdaCostaZone
		{
		protected:

			// Protected data

				//- Automatically generated zone name for this porous zone
			const word zoneName_;

			//- Porosity surface area per unit volume zone field
			scalarField Sigma_;


		public:

			//- Constructor
			FoamAtmosphericModels_EXPORT powerLawLopesdaCostaZone
			(
				const word& name,
				const word& modelType,
				const fvMesh& mesh,
				const dictionary& dict
			);

			// Member Functions

				//- Return the porosity surface area per unit volume zone field
			FoamAtmosphericModels_EXPORT const scalarField& Sigma() const;
		};


		/*---------------------------------------------------------------------------*\
							  Class powerLawLopesdaCosta Declaration
		\*---------------------------------------------------------------------------*/

		class powerLawLopesdaCosta
			:
			public powerLawLopesdaCostaZone,
			public porosityModel
		{
			// Private Data

				//- Cd coefficient
			scalar Cd_;

			//- C1 coefficient
			scalar C1_;

			//- Name of density field
			word rhoName_;


			// Private Member Functions

				//- Apply resistance
			template<class RhoFieldType>
			void apply
			(
				scalarField& Udiag,
				const scalarField& V,
				const RhoFieldType& rho,
				const vectorField& U
			) const;

			//- Apply resistance
			template<class RhoFieldType>
			void apply
			(
				tensorField& AU,
				const RhoFieldType& rho,
				const vectorField& U
			) const;


		public:

			//- Runtime type information
			//TypeName("powerLawLopesdaCosta");
			static const char* typeName_() { return "powerLawLopesdaCosta"; }
			static FoamAtmosphericModels_EXPORT const ::tnbLib::word typeName;
			static FoamAtmosphericModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

			FoamAtmosphericModels_EXPORT powerLawLopesdaCosta
			(
				const word& name,
				const word& modelType,
				const fvMesh& mesh,
				const dictionary& dict,
				const word& cellZoneName
			);

			//- Disallow default bitwise copy construction
			powerLawLopesdaCosta(const powerLawLopesdaCosta&) = delete;


			//- Destructor
			FoamAtmosphericModels_EXPORT virtual ~powerLawLopesdaCosta();


			// Member Functions

			//- Transform the model data wrt mesh changes
			FoamAtmosphericModels_EXPORT virtual void calcTransformModelData();

			//- Calculate the porosity force
			FoamAtmosphericModels_EXPORT virtual void calcForce
			(
				const volVectorField& U,
				const volScalarField& rho,
				const volScalarField& mu,
				vectorField& force
			) const;

			//- Add resistance
			FoamAtmosphericModels_EXPORT virtual void correct(fvVectorMatrix& UEqn) const;

			//- Add resistance
			FoamAtmosphericModels_EXPORT virtual void correct
			(
				fvVectorMatrix& UEqn,
				const volScalarField& rho,
				const volScalarField& mu
			) const;

			//- Add resistance
			FoamAtmosphericModels_EXPORT virtual void correct
			(
				const fvVectorMatrix& UEqn,
				volTensorField& AU
			) const;


			// I-O

			//- Write
			FoamAtmosphericModels_EXPORT bool writeData(Ostream& os) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const powerLawLopesdaCosta&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace porosityModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <powerLawLopesdaCostaI.hxx>

#endif // !_powerLawLopesdaCosta_Header
