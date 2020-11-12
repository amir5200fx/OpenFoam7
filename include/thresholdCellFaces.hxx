#pragma once
#ifndef _thresholdCellFaces_Header
#define _thresholdCellFaces_Header

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
	tnbLib::thresholdCellFaces

Description
	Selects the mesh cell faces specified by a threshold value.
	Non-triangulated by default.

SourceFiles
	thresholdCellFaces.C

\*---------------------------------------------------------------------------*/

#include <MeshedSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
						   Class thresholdCellFaces Declaration
	\*---------------------------------------------------------------------------*/

	class thresholdCellFaces
		:
		public MeshedSurface<face>
	{
		// Private Typedefs

		typedef MeshedSurface<face> MeshStorage;

		//- Reference to mesh
		const polyMesh& mesh_;

		//- For every face the original cell in mesh
		labelList meshCells_;


		// Private Member Functions

		FoamSampling_EXPORT void calculate
		(
			const scalarField&,
			const scalar lowerThreshold,
			const scalar upperThreshold,
			const bool triangulate
		);

	public:

		//- Runtime type information
		//TypeName("thresholdCellFaces");
		static const char* typeName_() { return "thresholdCellFaces"; }
		static FoamSampling_EXPORT const ::tnbLib::word typeName;
		static FoamSampling_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh, field and threshold value
		FoamSampling_EXPORT thresholdCellFaces
		(
			const polyMesh&,
			const scalarField&,
			const scalar lowerThreshold,
			const scalar upperThreshold,
			const bool triangulate = false
		);


		// Member Functions

			//- For every face original cell in mesh
		labelList& meshCells()
		{
			return meshCells_;
		}

		//- For every face original cell in mesh
		const labelList& meshCells() const
		{
			return meshCells_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_thresholdCellFaces_Header
