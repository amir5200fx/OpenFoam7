#pragma once
#ifndef _shellSurfaces_Header
#define _shellSurfaces_Header

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
	tnbLib::shellSurfaces

Description
	Encapsulates queries for volume refinement ('refine all cells within
	shell').

SourceFiles
	shellSurfaces.C

\*---------------------------------------------------------------------------*/

#include <searchableSurface.hxx>
#include <Tuple2.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class searchableSurfaces;

	/*---------------------------------------------------------------------------*\
							   Class shellSurfaces Declaration
	\*---------------------------------------------------------------------------*/

	class shellSurfaces
	{
	public:

		// Public data types

			//- Volume refinement controls
		enum refineMode
		{
			INSIDE,         // Refine all inside shell
			OUTSIDE,        // ,,         outside
			DISTANCE        // Refine based on distance to shell
		};


	private:

		// Private Data

			//- Reference to all geometry.
		const searchableSurfaces& allGeometry_;

		//- Indices of surfaces that are shells
		labelList shells_;

		//- Per shell whether to refine inside or outside
		List<refineMode> modes_;

		//- Per shell the list of ranges
		List<scalarField> distances_;

		//- Per shell per distance the refinement level
		labelListList levels_;


		// Private Data

			//- refineMode names
		static FoamSnappyHexMesh_EXPORT const NamedEnum<refineMode, 3> refineModeNames_;


		// Private Member Functions

			//- Helper function for initialisation.
		FoamSnappyHexMesh_EXPORT void setAndCheckLevels
		(
			const label shellI,
			const List<Tuple2<scalar, label>>&
		);

		FoamSnappyHexMesh_EXPORT void orient();

		FoamSnappyHexMesh_EXPORT void findHigherLevel
		(
			const pointField& pt,
			const label shellI,
			labelList& maxLevel
		) const;

	public:

		// Constructors

			//- Construct from geometry and dictionary
		FoamSnappyHexMesh_EXPORT shellSurfaces
		(
			const searchableSurfaces& allGeometry,
			const dictionary& shellsDict
		);


		// Member Functions

			// Access

				// const List<scalarField>& distances() const
				//{
				//    return distances_;
				//}
				//
				////- Per shell per distance the refinement level
				// const labelListList& levels() const
				//{
				//    return levels_;
				//}


			// Query

				//- Highest shell level
		FoamSnappyHexMesh_EXPORT label maxLevel() const;

		//- Find shell level higher than ptLevel
		FoamSnappyHexMesh_EXPORT void findHigherLevel
		(
			const pointField& pt,
			const labelList& ptLevel,
			labelList& maxLevel
		) const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_shellSurfaces_Header
