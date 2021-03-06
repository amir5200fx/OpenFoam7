#pragma once
#ifndef _PoissonPatchDistMethod_Header
#define _PoissonPatchDistMethod_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::patchDistMethods::Poisson

Description
	Calculation of approximate distance to nearest patch for all cells and
	boundary by solving Poisson's equation.

	References:
	\verbatim
		D.B. Spalding,
		"Calculation of turbulent heat transfer in cluttered spaces",
		Proc. 10th Int. Heat Transfer Conference, Brighton, UK, (1994).

		E. Fares and W. Schroder,
		"Differential Equation for Approximate Wall Distance",
		Int.J.Numer.Meth., 39:743-762, (2002).

		P.G. Tucker,
		"Differential equation based wall distance computation for DES and
		 RANS",
		J.Comp.Phys., Vol. 190, Issue 1, 1 st September, pp. 229-248 (2003)
	\endverbatim

	Example of the wallDist specification in fvSchemes:
	\verbatim
		laplacianSchemes
		{
			.
			.
			laplacian(yPsi) Gauss linear corrected;
			.
			.
		}

		wallDist
		{
			method Poisson;

			// Optional entry enabling the calculation
			// of the normal-to-wall field
			nRequired false;
		}
	\endverbatim
	Also the solver specification for yPsi is required in fvSolution, e.g.
	for simple cases:
	\verbatim
		yPsi
		{
			solver          PCG;
			preconditioner  DIC;
			tolerance       1e-5;
			relTol          0;
		}

	or for more complex cases:

		yPsi
		{
			solver          GAMG;
			smoother        GaussSeidel;
			cacheAgglomeration true;
			nCellsInCoarsestLevel 10;
			agglomerator    faceAreaPair;
			mergeLevels     1;
			tolerance       1e-5;
			relTol          0;
		}
	\endverbatim

See also
	tnbLib::patchDistMethod::meshWave
	tnbLib::wallDist

SourceFiles
	PoissonPatchDistMethod.C

\*---------------------------------------------------------------------------*/

#include <patchDistMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace patchDistMethods
	{

		/*---------------------------------------------------------------------------*\
								  Class Poisson Declaration
		\*---------------------------------------------------------------------------*/

		class Poisson
			:
			public patchDistMethod
		{
			// Private Member Data

				//- Cache yPsi for moving meshes
			tmp<volScalarField> tyPsi_;


		public:

			//- Runtime type information
			/*TypeName("Poisson");*/
			static const char* typeName_() { return "Poisson"; }
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
			static FoamFiniteVolume_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

			//- Construct from coefficients dictionary, mesh
			//  and fixed-value patch set
			FoamFiniteVolume_EXPORT Poisson
			(
				const dictionary& dict,
				const fvMesh& mesh,
				const labelHashSet& patchIDs
			);

			//- Construct from mesh and fixed-value patch set
			FoamFiniteVolume_EXPORT Poisson
			(
				const fvMesh& mesh,
				const labelHashSet& patchIDs
			);

			//- Disallow default bitwise copy construction
			FoamFiniteVolume_EXPORT Poisson(const Poisson&) = delete;


			// Member Functions

				//- Correct the given distance-to-patch field
			FoamFiniteVolume_EXPORT virtual bool correct(volScalarField& y);

			//- Correct the given distance-to-patch and normal-to-patch fields
			FoamFiniteVolume_EXPORT virtual bool correct(volScalarField& y, volVectorField& n);


			// Member Operators

			//- Disallow default bitwise assignment
			FoamFiniteVolume_EXPORT void operator=(const Poisson&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace patchDistMethods
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PoissonPatchDistMethod_Header
