#pragma once
#ifndef _externalDisplacementMeshMover_Header
#define _externalDisplacementMeshMover_Header

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
	tnbLib::externalDisplacementMeshMover

Description
	Virtual base class for mesh movers with externally provided displacement
	field giving the boundary conditions. Move the mesh from the current
	location to a new location (so modify the mesh; v.s. motionSolver that
	only returns the new location).

	All mesh movers are expected to read the dictionary settings at invocation
	of move(), i.e. not cache any settings.

SourceFiles
	externalDisplacementMeshMover.C

\*---------------------------------------------------------------------------*/

#include <pointFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
					   Class externalDisplacementMeshMover Declaration
	\*---------------------------------------------------------------------------*/

	class externalDisplacementMeshMover
	{
	protected:

		// Protected data

			//- Baffles in the mesh
		List<labelPair> baffles_;

		//- Reference to point motion field
		pointVectorField& pointDisplacement_;


	public:

		//- Runtime type information
		//TypeName("externalDisplacementMeshMover");
		static const char* typeName_() { return "externalDisplacementMeshMover"; }
		static FoamSnappyHexMesh_EXPORT const ::tnbLib::word typeName;
		static FoamSnappyHexMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time New selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			externalDisplacementMeshMover,
			dictionary,
			(
				const dictionary& dict,
				const List<labelPair>& baffles,
				pointVectorField& pointDisplacement
				),
				(dict, baffles, pointDisplacement)
		);*/

		typedef autoPtr<externalDisplacementMeshMover> (*dictionaryConstructorPtr)(
			const dictionary& dict, const List<labelPair>& baffles, pointVectorField& pointDisplacement);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamSnappyHexMesh_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamSnappyHexMesh_EXPORT void constructdictionaryConstructorTables();
		static FoamSnappyHexMesh_EXPORT void destroydictionaryConstructorTables();

		template <class externalDisplacementMeshMoverType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<externalDisplacementMeshMover> New(const dictionary& dict, const List<labelPair>& baffles,
			                                                  pointVectorField& pointDisplacement)
			{
				return autoPtr<externalDisplacementMeshMover>(
					new externalDisplacementMeshMoverType(dict, baffles, pointDisplacement));
			}

			adddictionaryConstructorToTable(const word& lookup = externalDisplacementMeshMoverType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"externalDisplacementMeshMover" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class externalDisplacementMeshMoverType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<externalDisplacementMeshMover> New(const dictionary& dict, const List<labelPair>& baffles,
			                                                  pointVectorField& pointDisplacement)
			{
				return autoPtr<externalDisplacementMeshMover>(
					new externalDisplacementMeshMoverType(dict, baffles, pointDisplacement));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = externalDisplacementMeshMoverType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};


		// Constructors

			//- Construct from dictionary and displacement field. Dictionary is
			//  allowed to go out of scope!
		FoamSnappyHexMesh_EXPORT externalDisplacementMeshMover
		(
			const dictionary& dict,
			const List<labelPair>& baffles,
			pointVectorField& pointDisplacement
		);

		//- Disallow default bitwise copy construction
		FoamSnappyHexMesh_EXPORT externalDisplacementMeshMover
		(
			const externalDisplacementMeshMover&
		);


		// Selectors

			//- Return a reference to the selected meshMover model
		static FoamSnappyHexMesh_EXPORT autoPtr<externalDisplacementMeshMover> New
		(
			const word& type,
			const dictionary& dict,
			const List<labelPair>& baffles,
			pointVectorField& pointDisplacement
		);


		//- Destructor
		FoamSnappyHexMesh_EXPORT virtual ~externalDisplacementMeshMover();


		// Member Functions

			// Access

				//- Return reference to the point motion displacement field
		pointVectorField& pointDisplacement()
		{
			return pointDisplacement_;
		}

		//- Return const reference to the point motion displacement field
		const pointVectorField& pointDisplacement() const
		{
			return pointDisplacement_;
		}

		const pointMesh& pMesh() const
		{
			return pointDisplacement_.mesh();
		}

		const polyMesh& mesh() const
		{
			return pMesh()();
		}


		// Mesh mover

			//- Move mesh using current pointDisplacement boundary values
			//  and current dictionary settings. Return true if successful
			//  (errors  on checkFaces less than allowable). Updates
			//  pointDisplacement.
		FoamSnappyHexMesh_EXPORT virtual bool move
		(
			const dictionary&,
			const label nAllowableErrors,
			labelList& checkFaces
		) = 0;

		//- Update local data for geometry changes
		FoamSnappyHexMesh_EXPORT virtual void movePoints(const pointField&);

		//-  Update local data for topology changes
		FoamSnappyHexMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSnappyHexMesh_EXPORT void operator=(const externalDisplacementMeshMover&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_externalDisplacementMeshMover_Header
