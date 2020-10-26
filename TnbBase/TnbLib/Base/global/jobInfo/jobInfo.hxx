#pragma once
#ifndef _jobInfo_Header
#define _jobInfo_Header

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
	tnbLib::jobInfo

Description
	Helper class for recording information about run/finished jobs.

	Writes the following files:
	  - $FOAM_JOB_DIR/runningJobs
	  - $FOAM_JOB_DIR/finishedJobs

SourceFiles
	jobInfo.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>
#include <fileName.hxx>
#include <cpuTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class jobInfo Declaration
	\*---------------------------------------------------------------------------*/

	class jobInfo
		:
		public dictionary
	{
		// Private Data

		mutable fileName runningJobPath_;
		mutable fileName finishedJobPath_;
		cpuTime cpuTime_;

		// Private Member Functions

		FoamBase_EXPORT bool write(Ostream&) const;
		FoamBase_EXPORT void end(const word& terminationType);


	public:

		static FoamBase_EXPORT bool constructed;
		static FoamBase_EXPORT bool writeJobControl;
		static FoamBase_EXPORT bool writeJobInfo;

		// Constructors

			//- Construct null
		FoamBase_EXPORT jobInfo();


		//- Destructor
		FoamBase_EXPORT ~jobInfo();


		// Member Functions

		FoamBase_EXPORT void write(const word& executable, const fileName& casePath) const;

		FoamBase_EXPORT void end();

		FoamBase_EXPORT void exit();

		FoamBase_EXPORT void abort();

		FoamBase_EXPORT void signalEnd() const;

		//- must be called at beginning of the program
		FoamBase_EXPORT void perform();  // Added by amir
	};


	FoamBase_EXPORT extern jobInfo jobInfo_;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_jobInfo_Header
