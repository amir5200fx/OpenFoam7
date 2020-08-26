#pragma once
#ifndef _STARCDsurfaceFormatCore_Header
#define _STARCDsurfaceFormatCore_Header

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
	tnbLib::fileFormats::STARCDsurfaceFormatCore

Description
	Internal class used by the STARCDsurfaceFormat

SourceFiles
	STARCDsurfaceFormatCore.C

\*---------------------------------------------------------------------------*/

#include <IFstream.hxx>
#include <Ostream.hxx>
#include <OFstream.hxx>
#include <MeshedSurface.hxx>
#include <STARCDCore.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
						   Class STARCDsurfaceFormatCore Declaration
		\*---------------------------------------------------------------------------*/

		class STARCDsurfaceFormatCore
			:
			public STARCDCore
		{
		protected:

			// Protected Member Functions

			static Map<word> readInpCellTable(IFstream&);

			static void writeCase
			(
				Ostream&,
				const pointField&,
				const label nFaces,
				const UList<surfZone>&
			);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_STARCDsurfaceFormatCore_Header
