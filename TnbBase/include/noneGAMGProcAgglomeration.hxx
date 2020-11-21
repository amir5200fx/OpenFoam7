#pragma once
#ifndef _noneGAMGProcAgglomeration_Header
#define _noneGAMGProcAgglomeration_Header

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
	tnbLib::noneGAMGProcAgglomeration

Description
	Processor agglomeration of GAMGAgglomerations.

SourceFiles
	noneGAMGProcAgglomeration.C

\*---------------------------------------------------------------------------*/

#include <GAMGProcAgglomeration.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class GAMGAgglomeration;

	/*---------------------------------------------------------------------------*\
				  Class noneGAMGProcAgglomeration Declaration
	\*---------------------------------------------------------------------------*/

	class noneGAMGProcAgglomeration
		:
		public GAMGProcAgglomeration
	{

	public:

		//- Runtime type information
		//TypeName("noneGAMGProcAgglomeration");
		static const char* typeName_() { return "noneGAMGProcAgglomeration"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given agglomerator and controls
		FoamBase_EXPORT noneGAMGProcAgglomeration
		(
			GAMGAgglomeration& agglom,
			const dictionary& controlDict
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT noneGAMGProcAgglomeration
		(
			const noneGAMGProcAgglomeration&
		);


		//- Destructor
		FoamBase_EXPORT virtual ~noneGAMGProcAgglomeration();


		// Member Functions

		   //- Modify agglomeration. Return true if modified
		virtual bool agglomerate()
		{
			return false;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const noneGAMGProcAgglomeration&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noneGAMGProcAgglomeration_Header
