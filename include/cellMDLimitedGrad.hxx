#pragma once
#ifndef _cellMDLimitedGrad_Header
#define _cellMDLimitedGrad_Header

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
	tnbLib::fv::cellMDLimitedGrad

Description
	cellMDLimitedGrad gradient scheme applied to a runTime selected base
	gradient scheme.

	The scalar limiter based on limiting the extrapolated face values
	between the maximum and minimum cell and cell neighbour values and is
	applied to the gradient in each face direction separately.

SourceFiles
	cellMDLimitedGrad.C

\*---------------------------------------------------------------------------*/

#include <gradScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamcellMDLimitedGrad_EXPORT __declspec(dllexport)
#else
#ifdef FoamcellMDLimitedGrad_EXPORT_DEFINE
#define FoamcellMDLimitedGrad_EXPORT __declspec(dllexport)
#else
#define FoamcellMDLimitedGrad_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class cellMDLimitedGrad Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class cellMDLimitedGrad
			:
			public fv::gradScheme<Type>
		{
			// Private Data

			tmp<fv::gradScheme<Type>> basicGradScheme_;

			//- Limiter coefficient
			const scalar k_;


		public:

			//- RunTime type information
			/*TypeName("cellMDLimited");*/
			static const char* typeName_() { return "cellMDLimited"; }
			static FoamcellMDLimitedGrad_EXPORT const ::tnbLib::word typeName;
			static FoamcellMDLimitedGrad_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from mesh and schemeData
			cellMDLimitedGrad(const fvMesh& mesh, Istream& schemeData)
				:
				gradScheme<Type>(mesh),
				basicGradScheme_(fv::gradScheme<Type>::New(mesh, schemeData)),
				k_(readScalar(schemeData))
			{
				if (k_ < 0 || k_ > 1)
				{
					FatalIOErrorInFunction
					(
						schemeData
					) << "coefficient = " << k_
						<< " should be >= 0 and <= 1"
						<< exit(FatalIOError);
				}
			}

			//- Disallow default bitwise copy construction
			cellMDLimitedGrad(const cellMDLimitedGrad&) = delete;


			// Member Functions

			static inline void limitFace
			(
				typename outerProduct<vector, Type>::type& g,
				const Type& maxDelta,
				const Type& minDelta,
				const vector& dcf
			);

			//- Return the gradient of the given field to the gradScheme::grad
			//  for optional caching
			virtual tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> calcGrad
				(
					const GeometricField<Type, fvPatchField, volMesh>& vsf,
					const word& name
				) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const cellMDLimitedGrad&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<>
		inline void cellMDLimitedGrad<scalar>::limitFace
		(
			vector& g,
			const scalar& maxDelta,
			const scalar& minDelta,
			const vector& dcf
		)
		{
			scalar extrapolate = dcf & g;

			if (extrapolate > maxDelta)
			{
				g = g + dcf * (maxDelta - extrapolate) / magSqr(dcf);
			}
			else if (extrapolate < minDelta)
			{
				g = g + dcf * (minDelta - extrapolate) / magSqr(dcf);
			}
		}


		template<class Type>
		inline void cellMDLimitedGrad<Type>::limitFace
		(
			typename outerProduct<vector, Type>::type& g,
			const Type& maxDelta,
			const Type& minDelta,
			const vector& dcf
		)
		{
			for (direction cmpt = 0; cmpt < Type::nComponents; cmpt++)
			{
				vector gi(g[cmpt], g[cmpt + 3], g[cmpt + 6]);
				cellMDLimitedGrad<scalar>::limitFace
				(
					gi,
					maxDelta.component(cmpt),
					minDelta.component(cmpt),
					dcf
				);
				g[cmpt] = gi.x();
				g[cmpt + 3] = gi.y();
				g[cmpt + 6] = gi.z();
			}
		}


		// * * * * * * * * Template Member Function Specialisations  * * * * * * * * //

		template<>
		tmp<volVectorField> cellMDLimitedGrad<scalar>::calcGrad
		(
			const volScalarField& vsf,
			const word& name
		) const;


		template<>
		tmp<volTensorField> cellMDLimitedGrad<vector>::calcGrad
		(
			const volVectorField& vsf,
			const word& name
		) const;


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellMDLimitedGrad_Header
