#pragma once
#ifndef _VTKedgeFormat_Header
#define _VTKedgeFormat_Header

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
	tnbLib::fileFormats::VTKedgeFormat

Description
	Provide a means of writing VTK legacy format.

SourceFiles
	VTKedgeFormat.C

\*---------------------------------------------------------------------------*/

#include <edgeMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							 Class VTKedgeFormat Declaration
		\*---------------------------------------------------------------------------*/

		class VTKedgeFormat
			:
			public edgeMesh
		{
		protected:

			// Protected Member Functions

				//- Write header information with points
			static FoamFvMesh_EXPORT void writeHeader
			(
				Ostream&,
				const pointField&
			);

			//- Write edges
			static FoamFvMesh_EXPORT void writeEdges(Ostream&, const UList<edge>&);


		public:


			// Constructors

				//- Construct from file name
			FoamFvMesh_EXPORT VTKedgeFormat(const fileName&);

			//- Disallow default bitwise copy construction
			FoamFvMesh_EXPORT VTKedgeFormat(const VTKedgeFormat&) = delete;


			// Selectors

				//- Read file and return surface
			static autoPtr<edgeMesh> New(const fileName& name)
			{
				return autoPtr<edgeMesh>
					(
						new VTKedgeFormat(name)
						);
			}


			//- Destructor
			virtual ~VTKedgeFormat()
			{}


			// Member Functions

				//- Write surface mesh components by proxy
			static FoamFvMesh_EXPORT void write(const fileName&, const edgeMesh&);

			//- Read from file
			virtual FoamFvMesh_EXPORT bool read(const fileName&);

			//- Write object file
			virtual void write(const fileName& name) const
			{
				write(name, *this);
			}


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvMesh_EXPORT void operator=(const VTKedgeFormat&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_VTKedgeFormat_Header
