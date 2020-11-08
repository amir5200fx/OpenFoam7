#pragma once
#ifndef _displacementLayeredMotionMotionSolver_Header
#define _displacementLayeredMotionMotionSolver_Header

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
	tnbLib::displacementLayeredMotionMotionSolver

Description
	Mesh motion solver for an (multi-block) extruded fvMesh. Gets given the
	structure of the mesh blocks and boundary conditions on these blocks.

	The displacementLayeredMotionCoeffs subdict of dynamicMeshDict specifies
	per region (=cellZone) the boundary conditions on two opposing patches
	(=faceZones). It then interpolates the boundary values using topological
	walking so requires the cellZone to be a layered mesh.

	The boundary conditions on faceZones are currently:

	follow: the faceZone follows the overall mesh displacement.
			Use this for faceZones on boundary faces (so it uses the
			proper boundary conditions on the pointDisplacement).

	uniformFollow: like 'follow' but takes the average value of
			a specified 'patch' (which is not necessarily colocated)

	fixedValue: fixed value.

	timeVaryingUniformFixedValue: table-driven fixed value.

	slip: the second of a pair of faceZones follows the tangential movement
		  specified by the first faceZone. (= removes the normal component).

SourceFiles
	displacementLayeredMotionMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <displacementMotionSolver.hxx>
#include <PackedBoolList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward class declarations

	/*---------------------------------------------------------------------------*\
				 Class displacementLayeredMotionMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class displacementLayeredMotionMotionSolver
		:
		public displacementMotionSolver
	{
		// Private Member Functions

		FoamDynamicMesh_EXPORT void calcZoneMask
		(
			const label cellZoneI,
			PackedBoolList& isZonePoint,
			PackedBoolList& isZoneEdge
		) const;

		FoamDynamicMesh_EXPORT void walkStructured
		(
			const label cellZoneI,
			const PackedBoolList& isZonePoint,
			const PackedBoolList& isZoneEdge,
			const labelList& seedPoints,
			const vectorField& seedData,
			scalarField& distance,
			vectorField& data
		) const;

		FoamDynamicMesh_EXPORT tmp<vectorField> faceZoneEvaluate
		(
			const faceZone& fz,
			const labelList& meshPoints,
			const dictionary& dict,
			const PtrList<pointVectorField>& patchDisp,
			const label patchi
		) const;

		FoamDynamicMesh_EXPORT void cellZoneSolve
		(
			const label cellZoneI,
			const dictionary& zoneDict
		);


	public:

		//- Runtime type information
		//TypeName("displacementLayeredMotion");
		static const char* typeName_() { return "displacementLayeredMotion"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyMesh and dictionary
		FoamDynamicMesh_EXPORT displacementLayeredMotionMotionSolver
		(
			const polyMesh&,
			const dictionary&
		);

		//- Disallow default bitwise copy construction
		FoamDynamicMesh_EXPORT displacementLayeredMotionMotionSolver
		(
			const displacementLayeredMotionMotionSolver&
		);


		//- Destructor
		FoamDynamicMesh_EXPORT ~displacementLayeredMotionMotionSolver();


		// Member Functions

			//- Return point location obtained from the current motion field
		FoamDynamicMesh_EXPORT virtual tmp<pointField> curPoints() const;

		//- Solve for motion
		FoamDynamicMesh_EXPORT virtual void solve();

		//- Update topology
		FoamDynamicMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const displacementLayeredMotionMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_displacementLayeredMotionMotionSolver_Header
