#pragma once
#ifndef _thixotropicViscosity_Header
#define _thixotropicViscosity_Header

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
	tnbLib::regionModels::surfaceFilmModels::thixotropicViscosity

Description
	Thixotropic viscosity model based on the evolution of the structural
	parameter \f$ \lambda \f$:

		\f[
			\lambda = a(1 - \lambda)^b - c \lambda \dot{\gamma}^d
		\f]

	The viscosity is then calculated using the expression

		\f[
			\mu = \frac{\mu_{\infty}}{{1 - K \lambda}^2}
		\f]

	Where the parameter K is given by:

		\f[
			K = 1 - \sqrt{\frac{\mu_{\infty}}{\mu_{0}}}
		\f]

	Here:
	\vartable
		\lambda         | structural parameter
		a               | model coefficient
		b               | model coefficient
		c               | model coefficient
		d               | model coefficient
		\dot{\gamma}    | stress rate [1/s]
		\mu_{0}         | limiting viscosity when \f$ \lambda = 1 \f$
		\mu_{\infty}    | limiting viscosity when \f$ \lambda = 0 \f$
	\endvartable

	Reference:
	\verbatim
		Barnes H A, 1997.  Thixotropy - a review.  J. Non-Newtonian Fluid
		Mech 70, pp 1-33
	\endverbatim

SourceFiles
	thixotropicViscosity.C

\*---------------------------------------------------------------------------*/

#include <filmViscosityModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								Class thixotropicViscosity Declaration
			\*---------------------------------------------------------------------------*/

			class thixotropicViscosity
				:
				public filmViscosityModel
			{
			protected:

				// Protected data

					//- Model `a' coefficient
				dimensionedScalar a_;

				//- Model `b' coefficient
				dimensionedScalar b_;

				//- Model `d' coefficient
				dimensionedScalar d_;

				//- Model `c' coefficient (read after d since dims depend on d value)
				dimensionedScalar c_;

				//- Limiting viscosity when lambda = 1
				dimensionedScalar mu0_;

				//- Limiting viscosity when lambda = 0
				dimensionedScalar muInf_;

				//- Model coeffiicient
				dimensionedScalar K_;

				//- Structural parameter
				//  0 = freestream value (most liquid)
				//  1 = fully built (most solid)
				volScalarField lambda_;


			public:

				//- Runtime type information
				//TypeName("thixotropic");
				static const char* typeName_() { return "thixotropic"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT thixotropicViscosity
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict,
					volScalarField& mu
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT thixotropicViscosity(const thixotropicViscosity&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~thixotropicViscosity();


				// Member Functions

					//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					const volScalarField& p,
					const volScalarField& T
				);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const thixotropicViscosity&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_thixotropicViscosity_Header
