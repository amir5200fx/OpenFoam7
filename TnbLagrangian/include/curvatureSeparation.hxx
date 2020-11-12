#pragma once
#ifndef _curvatureSeparation_Header
#define _curvatureSeparation_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::curvatureSeparation

Description
	Curvature film separation model

	Assesses film curvature via the mesh geometry and calculates a force
	balance of the form:

		F_sum = F_inertial + F_body + F_surface

	If F_sum < 0, the film separates. Similarly, if F_sum > 0 the film will
	remain attached.

	Based on description given by
		Owen and D. J. Ryley. The flow of thin liquid films around corners.
		International Journal of Multiphase Flow, 11(1):51-62, 1985.


SourceFiles
	curvatureSeparation.C

\*---------------------------------------------------------------------------*/

#include <injectionModel.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
							   Class curvatureSeparation Declaration
			\*---------------------------------------------------------------------------*/

			class curvatureSeparation
				:
				public injectionModel
			{
			protected:

				// Protected data

					//- Gradient of surface normals
				volTensorField gradNHat_;

				//- Minimum gravity driven film thickness (non-dimensionalised delta/R1)
				scalar deltaByR1Min_;

				//- List of radii for patches - if patch not defined, radius
				// calculated based on mesh geometry
				List<Tuple2<label, scalar>> definedPatchRadii_;

				//- Magnitude of gravity vector
				scalar magG_;

				//- Direction of gravity vector
				vector gHat_;


				// Protected Member Functions

					//- Calculate local (inverse) radius of curvature
				FoamLagrangian_EXPORT tmp<volScalarField> calcInvR1(const volVectorField& U) const;

				//- Calculate the cosine of the angle between gravity vector and
				//  cell out flow direction
				FoamLagrangian_EXPORT tmp<scalarField> calcCosAngle(const surfaceScalarField& phi) const;


			public:

				//- Runtime type information
				//TypeName("curvatureSeparation");
				static const char* typeName_() { return "curvatureSeparation"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT curvatureSeparation
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT curvatureSeparation(const curvatureSeparation&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~curvatureSeparation();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					scalarField& massToInject,
					scalarField& diameterToInject
				);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const curvatureSeparation&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_curvatureSeparation_Header
