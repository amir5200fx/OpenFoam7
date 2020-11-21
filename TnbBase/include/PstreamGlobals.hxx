#pragma once
#ifndef _PstreamGlobals_Header
#define _PstreamGlobals_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::PstreamGlobals

Description
	Global functions and variables for working with parallel streams,
	but principally for mpi

SourceFiles
	PstreamGlobals.C

\*---------------------------------------------------------------------------*/

#include <DynamicList.hxx>

#define MPI_hpux
#include <mpi.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class PstreamGlobals Declaration
	\*---------------------------------------------------------------------------*/

	namespace PstreamGlobals
	{
		FoamBase_EXPORT extern MPI_Comm MPI_COMM_FOAM;

		FoamBase_EXPORT extern DynamicList<MPI_Request> outstandingRequests_;

		FoamBase_EXPORT extern int nTags_;

		FoamBase_EXPORT extern DynamicList<int> freedTags_;

		// Current communicators. First element will be MPI_COMM_FOAM
		FoamBase_EXPORT extern DynamicList<MPI_Comm> MPICommunicators_;

		FoamBase_EXPORT extern DynamicList<MPI_Group> MPIGroups_;

		FoamBase_EXPORT void checkCommunicator(const label, const label procNo);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PstreamGlobals_Header
