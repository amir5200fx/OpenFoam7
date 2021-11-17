#pragma once
#ifndef _ensightCloudField_Header
#define _ensightCloudField_Header

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

InApplication
    foamToEnsight

Description

SourceFiles
    ensightCloudField.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <Cloud.hxx>
#include <IOobject.hxx>
#include <Time.hxx>
#include <IOField.hxx>
#include <OFstream.hxx>
#include <IOmanip.hxx>

#include "itoa.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Type>
	void ensightCloudField
	(
		const IOobject& fieldObject,
		const fileName& postProcPath,
		const word& prepend,
		const label timeIndex,
		const word& cloudName,
		Ostream& ensightCaseFile,
		const bool dataExists
	);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "ensightCloudFieldI.hxx"

//#ifdef NoRepository
//#include "ensightCloudField.C"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ensightCloudField_Header
