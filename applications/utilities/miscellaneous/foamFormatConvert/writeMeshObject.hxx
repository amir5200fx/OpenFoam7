#pragma once
#ifndef _writeMeshObject_Header
#define _writeMeshObject_Header

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

Global
    writeMeshObject

Description
    Write a mesh object in the format specified in controlDict.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>
#include <word.hxx>
#include <Time.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type, class CheckType = Type>
	inline bool writeMeshObject
	(
		const word& name,
		const fileName& meshDir,
		Time& runTime,
		bool disableHeaderChecking = false
	)
	{
		IOobject io
		(
			name,
			runTime.timeName(),
			meshDir,
			runTime,
			IOobject::MUST_READ,
			IOobject::NO_WRITE,
			false
		);

		bool writeOk = false;

		if
			(
				io.typeHeaderOk<Type>(false)
				&& io.headerClassName() == CheckType::typeName
				)
		{
			Info << "        Reading " << io.headerClassName()
				<< " : " << name << endl;

			// Switch off type checking (for reading e.g. faceZones as
			// generic list of dictionaries).
			word oldTypeName;
			if (disableHeaderChecking)
			{
				oldTypeName = Type::typeName;
				const_cast<word&>(Type::typeName) = word::null;
			}

			Type meshObject(io);

			if (disableHeaderChecking)
			{
				const_cast<word&>(Type::typeName) = oldTypeName;
				// Fake type back to what was in field
				const_cast<word&>(meshObject.type()) = io.headerClassName();
			}

			Info << "        Writing " << name << endl;
			writeOk = meshObject.regIOobject::write();
		}

		return writeOk;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_writeMeshObject_Header
