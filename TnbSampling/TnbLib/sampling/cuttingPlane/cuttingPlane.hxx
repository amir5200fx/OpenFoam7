#pragma once
#ifndef _cuttingPlane_Header
#define _cuttingPlane_Header

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
	tnbLib::cuttingPlane

Description
	Constructs plane through mesh.

	No attempt at resolving degenerate cases. Since the cut faces are
	usually quite ugly, they will always be triangulated.

Note
	When the cutting plane coincides with a mesh face, the cell edge on the
	positive side of the plane is taken.

SourceFiles
	cuttingPlane.C

\*---------------------------------------------------------------------------*/

#include <plane.hxx>
#include <pointField.hxx>
#include <faceList.hxx>
#include <MeshedSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class primitiveMesh;

	/*---------------------------------------------------------------------------*\
						   Class cuttingPlane Declaration
	\*---------------------------------------------------------------------------*/

	class cuttingPlane
		:
		public plane,
		public MeshedSurface<face>
	{
		// Private Typedef

		typedef MeshedSurface<face> MeshStorage;


		// Private Data

			//- List of cells cut by the plane
		labelList cutCells_;


		// Private Member Functions

			//- Determine cut cells, possibly restricted to a list of cells
		FoamSampling_EXPORT void calcCutCells
		(
			const primitiveMesh&,
			const scalarField& dotProducts,
			const labelUList& cellIdLabels = labelUList::null()
		);

		//- Determine intersection points (cutPoints).
		FoamSampling_EXPORT void intersectEdges
		(
			const primitiveMesh&,
			const scalarField& dotProducts,
			List<label>& edgePoint
		);

		//- Walk circumference of cell, starting from startEdgeI crossing
		//  only cut edges. Record cutPoint labels in faceVerts.
		static FoamSampling_EXPORT bool walkCell
		(
			const primitiveMesh&,
			const labelUList& edgePoint,
			const label celli,
			const label startEdgeI,
			DynamicList<label>& faceVerts
		);

		//- Determine cuts for all cut cells.
		FoamSampling_EXPORT void walkCellCuts
		(
			const primitiveMesh& mesh,
			const bool triangulate,
			const labelUList& edgePoint
		);


	protected:

		// Constructors

			//- Construct plane description without cutting
		FoamSampling_EXPORT cuttingPlane(const plane&);


		// Protected Member Functions

			//- Recut mesh with existing planeDesc, restricted to a list of cells
		FoamSampling_EXPORT void reCut
		(
			const primitiveMesh&,
			const bool triangulate,
			const labelUList& cellIdLabels = labelUList::null()
		);

		//- Remap action on triangulation or cleanup
		FoamSampling_EXPORT virtual void remapFaces(const labelUList& faceMap);


	public:

		// Constructors

			//- Construct from plane and mesh reference,
			//  possibly restricted to a list of cells
		FoamSampling_EXPORT cuttingPlane
		(
			const plane&,
			const primitiveMesh&,
			const bool triangulate,
			const labelUList& cellIdLabels = labelUList::null()
		);


		// Member Functions

			//- Return plane used
		const plane& planeDesc() const
		{
			return static_cast<const plane&>(*this);
		}

		//- Return List of cells cut by the plane
		const labelList& cutCells() const
		{
			return cutCells_;
		}

		//- Return true or false to question: have any cells been cut?
		bool cut() const
		{
			return cutCells_.size();
		}

		//- Sample the cell field
		template<class Type>
		tmp<Field<Type>> sample(const Field<Type>&) const;

		template<class Type>
		tmp<Field<Type>> sample(const tmp<Field<Type>>&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cuttingPlaneI.hxx>

//#ifdef NoRepository
//#include <cuttingPlaneTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cuttingPlane_Header
