#pragma once
#ifndef _ensightOutputFunctions_Header
#define _ensightOutputFunctions_Header

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

Description
    Miscellaneous collection of functions and template related to Ensight data

SourceFiles
    ensightOutputFunctions.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <ensightFile.hxx>
#include <ensightParts.hxx>
#include <Cloud.hxx>
#include <polyMesh.hxx>
#include <IOobject.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void ensightCaseEntry
	(
		OFstream& caseFile,
		const string& ensightType,
		const word& fieldName,
		const fileName& dataMask,
		const fileName& local = fileName::null,
		const label cloudNo = -1,
		const label timeSet = 1
	);


	void ensightParticlePositions
	(
		const polyMesh& mesh,
		const fileName& dataDir,
		const fileName& subDir,
		const word& cloudName,
		IOstream::streamFormat format
	);


	//- Write Lagrangian parcels
	template<class Type>
	void ensightLagrangianField
	(
		const IOobject& fieldObject,
		const fileName& dataDir,
		const fileName& subDir,
		const word& cloudName,
		IOstream::streamFormat format
	);

	//- Write generalized field components
	template<class Type>
	void ensightVolField
	(
		const ensightParts& partsList,
		const IOobject& fieldObject,
		const fvMesh& mesh,
		const fileName& dataDir,
		const fileName& subDir,
		IOstream::streamFormat format
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // namespace tnbLib

//#ifdef NoRepository
//#include "ensightOutputFunctions.C"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "ensightOutputFunctionsI.hxx"

#endif // !_ensightOutputFunctions_Header
