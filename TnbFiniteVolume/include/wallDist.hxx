#pragma once
#ifndef _wallDist_Header
#define _wallDist_Header

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
	tnbLib::wallDist

Description
	Interface to run-time selectable methods to calculate the distance-to-wall
	and normal-to-wall fields.

	Example of the wallDist specification in fvSchemes:
	\verbatim
		wallDist
		{
			method meshWave;

			// Optional entry enabling the calculation
			// of the normal-to-wall field
			nRequired false;
		}
	\endverbatim

See also
	tnbLib::patchDistMethod::meshWave
	tnbLib::patchDistMethod::Poisson
	tnbLib::patchDistMethod::advectionDiffusion

SourceFiles
	wallDist.C

\*---------------------------------------------------------------------------*/

#include <MeshObject.hxx>
#include <patchDistMethod.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class wallDist Declaration
	\*---------------------------------------------------------------------------*/

	class wallDist
		:
		public MeshObject<fvMesh, UpdateableMeshObject, wallDist>
	{
		// Private Data

			//- Set of patch IDs
		const labelHashSet patchIDs_;

		//- Name for the patch set, e.g. "wall"
		const word patchTypeName_;

		//- Run-time selected method to generate the distance-to-wall field
		mutable autoPtr<patchDistMethod> pdm_;

		//- Distance-to-wall field
		mutable volScalarField y_;

		//- Flag to indicate if the distance-to-wall field is required
		mutable bool nRequired_;

		//- Normal-to-wall field
		mutable tmp<volVectorField> n_;


		// Private Member Functions

			//- Construct the normal-to-wall field as required
		FoamFiniteVolume_EXPORT void constructn() const;


	public:

		// Declare name of the class and its debug switch
		/*ClassName("wallDist");*/
		static const char* typeName_() { return "wallDist"; } 
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName; 
		static FoamFiniteVolume_EXPORT int debug;


		// Constructors

			//- Construct from mesh and optional patch type name
		FoamFiniteVolume_EXPORT wallDist
		(
			const fvMesh& mesh,
			const word& patchTypeName = "wall"
		);

		//- Construct from mesh, patch IDs and optional patch type name
		FoamFiniteVolume_EXPORT wallDist
		(
			const fvMesh& mesh,
			const labelHashSet& patchIDs,
			const word& patchTypeName = "patch"
		);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT wallDist(const wallDist&) = delete;


		//- Destructor
		virtual ~wallDist();
		FoamFiniteVolume_EXPORT

		// Member Functions

		//- Return the patchIDs
		const labelHashSet& patchIDs() const
		{
			return patchIDs_;
		}

		//- Return reference to cached distance-to-wall field
		const volScalarField& y() const
		{
			return y_;
		}

		//- Return reference to cached normal-to-wall field
		FoamFiniteVolume_EXPORT const volVectorField& n() const;

		//- Update the y-field when the mesh moves
		FoamFiniteVolume_EXPORT virtual bool movePoints();

		//- Update the y-field when the mesh changes
		FoamFiniteVolume_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

		//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const wallDist&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallDist_Header
