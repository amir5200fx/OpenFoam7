#pragma once
#ifndef _meshWriter_Header
#define _meshWriter_Header

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

Namespace
	tnbLib::meshWriters

Description
	A namespace for holding various types of mesh writers.


Class
	tnbLib::meshWriter

Description
	write OpenFOAM meshes and/or results to another CFD format
	- currently just STAR-CD

\par Files

	"constant/boundaryRegion" is an IOMap<dictionary> that contains
	the boundary type and names. eg,
	\verbatim
		(
			0
			{
				BoundaryType    wall;
				Label           Default_Boundary_Region;
			}

			1
			{
				BoundaryType    inlet;
				Label           inlet_1;
			}

			...

			4
			{
				BoundaryType    pressure;
				Label           outlet;
			}
		)
	\endverbatim


SourceFiles
	meshWriterI.H
	meshWriter.C
	meshWriterIO.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>
#include <boundaryRegion.hxx>
#include <cellTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class meshWriter Declaration
	\*---------------------------------------------------------------------------*/

	class meshWriter
	{
	protected:

		// Protected data

			//- Mesh reference
		const polyMesh& mesh_;

		//- Scaling factor for points (eg, [m] -> [mm])
		scalar scaleFactor_;

		//- Write bnd file
		bool writeBoundary_;

		//- boundaryRegion persistent data saved as a dictionary
		boundaryRegion boundaryRegion_;

		//- cellTable persistent data saved as a dictionary
		cellTable cellTable_;

		//- cellTable IDs for each cell
		labelList cellTableId_;

		//- Pointers to cell shape models
		static FoamConversion_EXPORT const cellModel* unknownModel;
		static FoamConversion_EXPORT const cellModel* tetModel;
		static FoamConversion_EXPORT const cellModel* pyrModel;
		static FoamConversion_EXPORT const cellModel* prismModel;
		static FoamConversion_EXPORT const cellModel* hexModel;


	public:

		// Static Data Members

			//- Specify a default mesh name
		static FoamConversion_EXPORT string defaultMeshName;

		// Constructors

			//- Create a writer object
		FoamConversion_EXPORT meshWriter
		(
			const polyMesh&,
			const scalar scaleFactor = 1.0
		);

		//- Disallow default bitwise copy construction
		FoamConversion_EXPORT meshWriter(const meshWriter&) = delete;


		//- Destructor
		FoamConversion_EXPORT virtual ~meshWriter();


		// Member Functions

			// Edit

				//- Set points scaling
		void scaleFactor(const scalar scaling)
		{
			scaleFactor_ = scaling;
		}

		//- Suppress writing bnd file
		void noBoundary()
		{
			writeBoundary_ = false;
		}

		// Write

			//- Write volume mesh. Subclass must supply this method
		virtual bool write
		(
			const fileName& timeName = fileName::null
		) const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamConversion_EXPORT void operator=(const meshWriter&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_meshWriter_Header
