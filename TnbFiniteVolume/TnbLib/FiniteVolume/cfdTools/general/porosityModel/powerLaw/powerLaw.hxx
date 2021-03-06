#pragma once
#ifndef _powerLaw_Header
#define _powerLaw_Header

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
	tnbLib::porosityModels::powerLaw

Description
	Power law porosity model, given by:

		\f[
			S = - \rho C_0 |U|^{(C_1 - 1)} U
		\f]

	where
	\vartable
		C_0      | model linear coefficient
		C_1      | model exponent coefficient
	\endvartable

SourceFiles
	powerLaw.C
	powerLawTemplates.C

\*---------------------------------------------------------------------------*/

#include <porosityModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace porosityModels
	{

		/*---------------------------------------------------------------------------*\
							  Class powerLaw Declaration
		\*---------------------------------------------------------------------------*/

		class powerLaw
			:
			public porosityModel
		{
			// Private Data

				//- C0 coefficient
			scalar C0_;

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
			//TypeName("powerLaw");
			static const char* typeName_() { return "powerLaw"; }
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
			static FoamFiniteVolume_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

			FoamFiniteVolume_EXPORT powerLaw
			(
				const word& name,
				const word& modelType,
				const fvMesh& mesh,
				const dictionary& dict,
				const word& cellZoneName
			);

			//- Disallow default bitwise copy construction
			FoamFiniteVolume_EXPORT powerLaw(const powerLaw&) = delete;


			//- Destructor
			FoamFiniteVolume_EXPORT virtual ~powerLaw();


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
			FoamFiniteVolume_EXPORT void operator=(const powerLaw&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace porosityModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <powerLawI.hxx>

//#ifdef NoRepository
//#include <powerLawTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_powerLaw_Header
