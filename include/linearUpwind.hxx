#pragma once
#ifndef _linearUpwind_Header
#define _linearUpwind_Header

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
	tnbLib::linearUpwind

Description
	linearUpwind interpolation scheme class derived from upwind and returns
	upwind weighting factors and also applies a gradient-based explicit
	correction.

SourceFiles
	linearUpwind.C

\*---------------------------------------------------------------------------*/

#include <upwind.hxx>
#include <gaussGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class linearUpwind Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class linearUpwind
		:
		public upwind<Type>
	{
		// Private Data

		word gradSchemeName_;


	public:

		//- Runtime type information
		TypeName("linearUpwind");


		// Constructors

			//- Construct from faceFlux
		linearUpwind
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux
		)
			:
			upwind<Type>(mesh, faceFlux),
			gradSchemeName_("grad")
		{}

		//- Construct from Istream.
		//  The name of the flux field is read from the Istream and looked-up
		//  from the mesh objectRegistry
		linearUpwind
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
			:
			upwind<Type>(mesh, schemeData),
			gradSchemeName_(schemeData)
		{}

		//- Construct from faceFlux and Istream
		linearUpwind
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		)
			:
			upwind<Type>(mesh, faceFlux, schemeData),
			gradSchemeName_(schemeData)
		{}

		//- Disallow default bitwise copy construction
		linearUpwind(const linearUpwind&) = delete;


		// Member Functions

			//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return true;
		}

		//- Return the explicit correction to the face-interpolate
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			correction
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const linearUpwind&) = delete;
	};


	// Specialize for volVectorField to support cached gradients
	template<>
	tmp<surfaceVectorField> linearUpwind<vector>::correction
	(
		const volVectorField& vf
	) const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linearUpwind_Header
