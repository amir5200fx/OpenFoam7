#pragma once
#ifndef _dynamicFvMesh_Header
#define _dynamicFvMesh_Header

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
	tnbLib::dynamicFvMesh

Description
	Abstract base class for geometry and/or topology changing fvMesh.

SourceFiles
	dynamicFvMesh.C
	dynamicFvMeshNew.C

\*---------------------------------------------------------------------------*/

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class dynamicFvMesh Declaration
	\*---------------------------------------------------------------------------*/

	class dynamicFvMesh
		:
		public fvMesh
	{
		// Private Data

			//- The dynamicMeshDict
		dictionary dynamicMeshDict_;


		// Private Member Functions

			//- Return the dynamicMeshDict IOobject
		static FoamDynamicMesh_EXPORT IOobject dynamicMeshDictIOobject(const IOobject& io);


	public:

		//- Runtime type information
		//TypeName("dynamicFvMesh");
		static const char* typeName_() { return "dynamicFvMesh"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			dynamicFvMesh,
			IOobject,
			(const IOobject& io),
			(io)
		);*/

		typedef autoPtr<dynamicFvMesh> (*IOobjectConstructorPtr)(const IOobject& io);
		typedef HashTable<IOobjectConstructorPtr, word, string::hash> IOobjectConstructorTable;
		static FoamDynamicMesh_EXPORT IOobjectConstructorTable* IOobjectConstructorTablePtr_;
		static FoamDynamicMesh_EXPORT void constructIOobjectConstructorTables();
		static FoamDynamicMesh_EXPORT void destroyIOobjectConstructorTables();

		template <class dynamicFvMeshType>
		class addIOobjectConstructorToTable
		{
		public:
			static autoPtr<dynamicFvMesh> New(const IOobject& io)
			{
				return autoPtr<dynamicFvMesh>(new dynamicFvMeshType(io));
			}

			addIOobjectConstructorToTable(const word& lookup = dynamicFvMeshType::typeName)
			{
				constructIOobjectConstructorTables();
				if (!IOobjectConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "dynamicFvMesh" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addIOobjectConstructorToTable() { destroyIOobjectConstructorTables(); }
		};

		template <class dynamicFvMeshType>
		class addRemovableIOobjectConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<dynamicFvMesh> New(const IOobject& io)
			{
				return autoPtr<dynamicFvMesh>(new dynamicFvMeshType(io));
			}

			addRemovableIOobjectConstructorToTable(const word& lookup = dynamicFvMeshType::typeName) : lookup_(lookup)
			{
				constructIOobjectConstructorTables();
				IOobjectConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableIOobjectConstructorToTable()
			{
				if (IOobjectConstructorTablePtr_) { IOobjectConstructorTablePtr_->erase(lookup_); }
			}
		};;


		//- Helper class to update the velocity boundary conditions
		//  following mesh motion
		class velocityMotionCorrection
		{
			// Private Data

			const dynamicFvMesh& mesh_;

			wordList velocityFields_;

		public:

			// Constructors

			FoamDynamicMesh_EXPORT velocityMotionCorrection
			(
				const dynamicFvMesh& mesh,
				const dictionary& dict
			);


			// Member Functions

			void update() const;
		};


		// Constructors

			//- Construct from objectRegistry, and read/write options
		explicit FoamDynamicMesh_EXPORT dynamicFvMesh(const IOobject& io);

		//- Construct from components without boundary.
		//  Boundary is added using addFvPatches() member function
		FoamDynamicMesh_EXPORT dynamicFvMesh
		(
			const IOobject& io,
			pointField&& points,
			faceList&& faces,
			labelList&& allOwner,
			labelList&& allNeighbour,
			const bool syncPar = true
		);

		//- Construct without boundary from cells rather than owner/neighbour.
		//  Boundary is added using addPatches() member function
		FoamDynamicMesh_EXPORT dynamicFvMesh
		(
			const IOobject& io,
			pointField&& points,
			faceList&& faces,
			cellList&& cells,
			const bool syncPar = true
		);

		//- Disallow default bitwise copy construction
		dynamicFvMesh(const dynamicFvMesh&) = delete;


		// Selectors

			//- Select, construct and return the dynamicFvMesh
			//  If the constant/dynamicMeshDict does not exist
			//  a staticFvMesh is returned
		static FoamDynamicMesh_EXPORT autoPtr<dynamicFvMesh> New(const IOobject& io);


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~dynamicFvMesh();


		// Member Functions

			//- Return the dynamicMeshDict
		const dictionary& dynamicMeshDict() const
		{
			return dynamicMeshDict_;
		}

		//- Is mesh dynamic
		virtual bool dynamic() const
		{
			return true;
		}

		//- Update the mesh for both mesh motion and topology change
		virtual bool update() = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const dynamicFvMesh&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicFvMesh_Header
