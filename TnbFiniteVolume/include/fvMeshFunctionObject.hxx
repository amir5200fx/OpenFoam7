#pragma once
#ifndef _fvMeshFunctionObject_Header
#define _fvMeshFunctionObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::fvMeshFunctionObject

Description
	Specialization of tnbLib::functionObject for an tnbLib::fvMesh, providing a
	reference to the tnbLib::fvMesh.

	If the selected region is not an tnbLib::fvMesh a tnbLib::FatalError will be
	generated.

See also
	tnbLib::regionFunctionObject
	tnbLib::functionObject

SourceFiles
	fvMeshFunctionObject.C

\*---------------------------------------------------------------------------*/

#include <regionFunctionObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvMesh;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							 Class fvMeshFunctionObject Declaration
		\*---------------------------------------------------------------------------*/

		class fvMeshFunctionObject
			:
			public regionFunctionObject
		{

		protected:

			// Protected member data

				//- Reference to the fvMesh
			const fvMesh& mesh_;


		public:

			//- Runtime type information
			/*TypeName("fvMeshFunctionObject");*/
			static const char* typeName_() { return "fvMeshFunctionObject"; }
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
			static FoamFiniteVolume_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFiniteVolume_EXPORT fvMeshFunctionObject
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Construct from the region objectRegistry and dictionary
			FoamFiniteVolume_EXPORT fvMeshFunctionObject
			(
				const word& name,
				const objectRegistry& obr,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFiniteVolume_EXPORT fvMeshFunctionObject(const fvMeshFunctionObject&) = delete;


			//- Destructor
			FoamFiniteVolume_EXPORT virtual ~fvMeshFunctionObject();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFiniteVolume_EXPORT void operator=(const fvMeshFunctionObject&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvMeshFunctionObject_Header
