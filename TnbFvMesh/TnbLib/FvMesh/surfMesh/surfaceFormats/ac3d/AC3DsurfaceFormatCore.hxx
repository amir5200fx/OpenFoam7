#pragma once
#ifndef _AC3DsurfaceFormatCore_Header
#define _AC3DsurfaceFormatCore_Header

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
	tnbLib::fileFormats::AC3DsurfaceFormatCore

Description
	Internal class used by the AC3DsurfaceFormat

SourceFiles
	AC3DsurfaceFormatCore.C

\*---------------------------------------------------------------------------*/

#include <IFstream.hxx>
#include <Ostream.hxx>
#include <OFstream.hxx>
#include <MeshedSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							Class AC3DsurfaceFormatCore Declaration
		\*---------------------------------------------------------------------------*/

		class AC3DsurfaceFormatCore
		{
		protected:

			// Protected Member Functions

				//- Read a type via IStringStream
			template<class Type>
			static Type parse(const string&);

			//- Read cmd, args from IFstream
			static FoamFvMesh_EXPORT bool readCmd(IFstream&, string& cmd, string& args);

			//- Cue up to cmd, reading args
			static FoamFvMesh_EXPORT bool cueTo(IFstream&, const string& cmd, string& args);

			//- Cue up to cmd, reading args or exit with a FatalError
			//  returns the command args
			static FoamFvMesh_EXPORT string cueToOrDie
			(
				IFstream&,
				const string& cmd,
				const string& errorMsg = string::null
			);

			//- Write header with materials
			static FoamFvMesh_EXPORT void writeHeader(Ostream&, const UList<surfZone>&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <AC3DsurfaceFormatCoreI.hxx>

//#ifdef NoRepository
//#include <AC3DsurfaceFormatCoreTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_AC3DsurfaceFormatCore_Header
