#pragma once
#ifndef _masterCoarsestGAMGProcAgglomeration_Header
#define _masterCoarsestGAMGProcAgglomeration_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::masterCoarsestGAMGProcAgglomeration

Description
	Processor agglomeration of GAMGAgglomerations.

SourceFiles
	masterCoarsestGAMGProcAgglomeration.C

\*---------------------------------------------------------------------------*/

#include <GAMGProcAgglomeration.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class GAMGAgglomeration;

	/*---------------------------------------------------------------------------*\
				  Class masterCoarsestGAMGProcAgglomeration Declaration
	\*---------------------------------------------------------------------------*/

	class masterCoarsestGAMGProcAgglomeration
		:
		public GAMGProcAgglomeration
	{
		// Private Data

		DynamicList<label> comms_;


	public:

		//- Runtime type information
		//TypeName("masterCoarsest");
		static const char* typeName_() { return "masterCoarsest"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given agglomerator and controls
		FoamBase_EXPORT masterCoarsestGAMGProcAgglomeration
		(
			GAMGAgglomeration& agglom,
			const dictionary& controlDict
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT masterCoarsestGAMGProcAgglomeration
		(
			const masterCoarsestGAMGProcAgglomeration&
		);


		//- Destructor
		FoamBase_EXPORT virtual ~masterCoarsestGAMGProcAgglomeration();


		// Member Functions

		   //- Modify agglomeration. Return true if modified
		FoamBase_EXPORT virtual bool agglomerate();

		//- Disallow default bitwise assignment


	// Member Operators

		FoamBase_EXPORT void operator=(const masterCoarsestGAMGProcAgglomeration&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_masterCoarsestGAMGProcAgglomeration_Header
