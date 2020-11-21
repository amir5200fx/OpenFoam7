#pragma once
#ifndef _VTKsurfaceFormatCore_Header
#define _VTKsurfaceFormatCore_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::fileFormats::VTKsurfaceFormatCore

Description
	Internal class used by the VTKsurfaceFormat

SourceFiles
	VTKsurfaceFormatCore.C

\*---------------------------------------------------------------------------*/

#include <Ostream.hxx>
#include <OFstream.hxx>
#include <MeshedSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							Class VTKsurfaceFormatCore Declaration
		\*---------------------------------------------------------------------------*/

		class VTKsurfaceFormatCore
		{
		protected:

			// Protected Member Functions

				//- Write header information with points
			static FoamFvMesh_EXPORT void writeHeader
			(
				Ostream&,
				const pointField&
			);

			//- Write trailing information with zone information
			static FoamFvMesh_EXPORT void writeTail(Ostream&, const UList<surfZone>&);

			//- Write trailing information with zone Ids
			static FoamFvMesh_EXPORT void writeTail(Ostream&, const labelUList& zoneIds);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_VTKsurfaceFormatCore_Header
