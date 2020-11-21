#pragma once
#ifndef _lduInterface_Header
#define _lduInterface_Header

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
	tnbLib::lduInterface

Description
	An abstract base class for implicitly-coupled interfaces
	e.g. processor and cyclic patches.

SourceFiles
	lduInterface.C

\*---------------------------------------------------------------------------*/

#include <labelField.hxx>
#include <typeInfo.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	/*---------------------------------------------------------------------------*\
						 Class lduInterface Declaration
	\*---------------------------------------------------------------------------*/

	class lduInterface
	{

	public:

		//- Runtime type information
		//TypeName("lduInterface");
		static const char* typeName_() { return "lduInterface"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		lduInterface()
		{}

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT lduInterface(const lduInterface&) = delete;


		//- Destructor
		FoamBase_EXPORT virtual ~lduInterface();


		// Member Functions

			// Access

				//- Return faceCell addressing
		FoamBase_EXPORT virtual const labelUList& faceCells() const = 0;


		// Interface transfer functions

			//- Return the values of the given internal data adjacent to
			//  the interface as a field
		FoamBase_EXPORT virtual tmp<labelField> interfaceInternalField
		(
			const labelUList& internalData
		) const = 0;

		//- Initialise transfer of internal field adjacent to the interface
		virtual void initInternalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& iF
		) const
		{}

		//- Transfer and return internal field adjacent to the interface
		FoamBase_EXPORT virtual tmp<labelField> internalFieldTransfer
		(
			const Pstream::commsTypes commsType,
			const labelUList& iF
		) const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const lduInterface&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_lduInterface_Header
