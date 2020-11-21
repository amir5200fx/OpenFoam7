#pragma once
#ifndef _dynamicMeshPointInterpolator_Header
#define _dynamicMeshPointInterpolator_Header

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
	tnbLib::dynamicMeshPointInterpolator

Description
	Interpolates pointVectorFields.

SourceFiles
	dynamicMeshPointInterpolator.C

\*---------------------------------------------------------------------------*/

#include <primitiveFields.hxx>
#include <pointFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;
	class interpolationWeights;

	/*---------------------------------------------------------------------------*\
							   Class dynamicInterpolatedFvMesh Declaration
	\*---------------------------------------------------------------------------*/

	class dynamicMeshPointInterpolator
	{
		// Private Data

			//- Reference to mesh
		const polyMesh& mesh_;

		//- Name of displacement field
		const word fieldName_;

		const word interpolationScheme_;

		//- Times with pre-specified displacement
		wordList timeNames_;

		//- Times with pre-specified displacement
		scalarField timeVals_;

		//- User-specified interpolator
		mutable autoPtr<interpolationWeights> interpolatorPtr_;

		//- Cached interpolation times
		mutable labelList currentIndices_;

		//- Cached interpolation weights
		mutable scalarField currentWeights_;


	public:

		// Constructors

			//- Construct from mesh and dictionary
		FoamDynamicMesh_EXPORT dynamicMeshPointInterpolator
		(
			const polyMesh& mesh,
			const dictionary& dict
		);


		//- Destructor
		FoamDynamicMesh_EXPORT ~dynamicMeshPointInterpolator();


		// Member Functions

			//- Return interpolated pointField for the currentTime
		FoamDynamicMesh_EXPORT tmp<pointVectorField> curPointField() const;

		//- Write
		FoamDynamicMesh_EXPORT void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicMeshPointInterpolator_Header
