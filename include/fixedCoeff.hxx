#pragma once
#ifndef _fixedCoeff_Header
#define _fixedCoeff_Header

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
	tnbLib::porosityModels::fixedCoeff

Description
	Fixed coefficient form of porosity model

		\f[
			S = - \rho_ref (\alpha + \beta |U|) U
		\f]

	In the case of compressible flow, a value for the reference density is
	required

SourceFiles
	fixedCoeff.C

\*---------------------------------------------------------------------------*/

#include <porosityModel.hxx>
#include <dimensionedTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace porosityModels
	{

		/*---------------------------------------------------------------------------*\
								  Class fixedCoeff Declaration
		\*---------------------------------------------------------------------------*/

		class fixedCoeff
			:
			public porosityModel
		{
			// Private Data

				//- Alpha coefficient XYZ components (user-supplied) [1/s]
			dimensionedVector alphaXYZ_;

			//- Beta coefficient XYZ components (user-supplied) [1/m]
			dimensionedVector betaXYZ_;

			//- Model alpha coefficient - converted from alphaXYZ [1/s]
			List<tensorField> alpha_;

			//- Model beta coefficient - converted from betaXYZ [1/m]
			List<tensorField> beta_;


			// Private Member Functions

				//- Apply
			void apply
			(
				scalarField& Udiag,
				vectorField& Usource,
				const scalarField& V,
				const vectorField& U,
				const scalar rho
			) const;

			//- Apply
			void apply
			(
				tensorField& AU,
				const vectorField& U,
				const scalar rho
			) const;


		public:

			//- Runtime type information
			TypeName("fixedCoeff");

			// Constructors

			fixedCoeff
			(
				const word& name,
				const word& modelType,
				const fvMesh& mesh,
				const dictionary& dict,
				const word& cellZoneName
			);

			//- Disallow default bitwise copy construction
			fixedCoeff(const fixedCoeff&) = delete;


			//- Destructor
			virtual ~fixedCoeff();


			// Member Functions

				//- Transform the model data wrt mesh changes
			virtual void calcTransformModelData();

			//- Calculate the porosity force
			virtual void calcForce
			(
				const volVectorField& U,
				const volScalarField& rho,
				const volScalarField& mu,
				vectorField& force
			) const;

			//- Add resistance
			virtual void correct(fvVectorMatrix& UEqn) const;

			//- Add resistance
			virtual void correct
			(
				fvVectorMatrix& UEqn,
				const volScalarField& rho,
				const volScalarField& mu
			) const;

			//- Add resistance
			virtual void correct
			(
				const fvVectorMatrix& UEqn,
				volTensorField& AU
			) const;


			// I-O

				//- Write
			bool writeData(Ostream& os) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const fixedCoeff&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace porosityModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedCoeff_Header
