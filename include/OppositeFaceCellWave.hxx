#pragma once
#ifndef _OppositeFaceCellWave_Header
#define _OppositeFaceCellWave_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::OppositeFaceCellWave

Description
	Version of FaceCellWave that walks through prismatic cells only.

	Used to determine mesh structure. In the front walking routines
	(faceToCell and faceToCell) it
	- walks across prismatic cells only
	- and only to a single opposite face

	Notes:
	A cell with a split faces will be marked but not walked through (since
	there is no single opposite face.

SourceFiles
	OppositeFaceCellWave.C

\*---------------------------------------------------------------------------*/

#include <FaceCellWave.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class OppositeFaceCellWaveName Declaration
	\*---------------------------------------------------------------------------*/

	//TemplateName(OppositeFaceCellWave);
	class OppositeFaceCellWaveName
	{
	public:
		OppositeFaceCellWaveName()
		{
		}

		static const char* typeName_() { return "OppositeFaceCellWave"; }
		static FoamRenumber_EXPORT const ::tnbLib::word typeName;
		static FoamRenumber_EXPORT int debug;
	};


	/*---------------------------------------------------------------------------*\
						Class OppositeFaceCellWave Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type, class TrackingData = int>
	class OppositeFaceCellWave
		:
		public FaceCellWave<Type, TrackingData>,
		public OppositeFaceCellWaveName
	{
	protected:

		// Protected data

			//- For every entry in changedCells (i.e. the cell front) gives
			//  the face that it needs to transfer to
		DynamicList<label> changedOppositeFaces_;


		// Protected Member Functions

			 //- Determine 'opposite' faces (= faces not sharing a vertex) on cell
		void opposingFaceLabels
		(
			const label celli,
			const label facei,
			DynamicList<label>&
		) const;


	public:

		// Constructors

			//- Construct from mesh and list of changed faces with the Type
			//  for these faces. Iterates until nothing changes or maxIter reached.
			//  (maxIter can be 0)
		OppositeFaceCellWave
		(
			const polyMesh&,
			const labelList& initialChangedFaces,
			const List<Type>& changedFacesInfo,
			UList<Type>& allFaceInfo,
			UList<Type>& allCellInfo,
			const label maxIter,
			TrackingData& td = FaceCellWave<Type, TrackingData>::dummyTrackData_
		);


		//- Destructor
		virtual ~OppositeFaceCellWave()
		{};


		// Member Functions

			//- Propagate from face to cell. Returns total number of cells
			//  (over all processors) changed.
		virtual label faceToCell();

		//- Propagate from cell to face. Returns total number of faces
		//  (over all processors) changed. (Faces on processorpatches are
		//  counted double)
		virtual label cellToFace();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <OppositeFaceCellWave.cxx>
//#endif

#include <OppositeFaceCellWaveI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_OppositeFaceCellWave_Header
