#pragma once
#ifndef _meshToMeshMethod_Header
#define _meshToMeshMethod_Header

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
	tnbLib::meshToMeshMethod

Description
	Base class for mesh-to-mesh calculation methods

SourceFiles
	meshToMeshMethod.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class meshToMeshMethod Declaration
	\*---------------------------------------------------------------------------*/

	class meshToMeshMethod
	{

	protected:

		// Protected data

			//- Reference to the source mesh
		const polyMesh& src_;

		//- Reference to the target mesh
		const polyMesh& tgt_;

		//- Cell total volume in overlap region [m^3]
		scalar V_;

		//- Tolerance used in volume overlap calculations
		static FoamSampling_EXPORT scalar tolerance_;


		// Protected Member Functions

			//- Return src cell IDs for the overlap region
		FoamSampling_EXPORT labelList maskCells() const;

		//- Return the true if cells intersect
		FoamSampling_EXPORT virtual bool intersect
		(
			const label srcCelli,
			const label tgtCelli
		) const;

		//- Return the intersection volume between two cells
		FoamSampling_EXPORT virtual scalar interVol
		(
			const label srcCelli,
			const label tgtCelli
		) const;

		//- Append target cell neihgbour cells to cellIDs list
		FoamSampling_EXPORT virtual void appendNbrCells
		(
			const label tgtCelli,
			const polyMesh& mesh,
			const DynamicList<label>& visitedTgtCells,
			DynamicList<label>& nbrTgtCellIDs
		) const;

		FoamSampling_EXPORT virtual bool initialise
		(
			labelListList& srcToTgtAddr,
			scalarListList& srcToTgtWght,
			labelListList& tgtToTgtAddr,
			scalarListList& tgtToTgtWght
		) const;


	public:

		//- Run-time type information
		//TypeName("meshToMeshMethod");
		static const char* typeName_() { return "meshToMeshMethod"; }
		static FoamSampling_EXPORT const ::tnbLib::word typeName;
		static FoamSampling_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			meshToMeshMethod,
			components,
			(
				const polyMesh& src,
				const polyMesh& tgt
				),
				(src, tgt)
		);*/
		
		typedef autoPtr<meshToMeshMethod> (*componentsConstructorPtr)(const polyMesh& src, const polyMesh& tgt);
		typedef HashTable<componentsConstructorPtr, word, string::hash> componentsConstructorTable;
		static FoamSampling_EXPORT componentsConstructorTable* componentsConstructorTablePtr_;
		static FoamSampling_EXPORT void constructcomponentsConstructorTables();
		static FoamSampling_EXPORT void destroycomponentsConstructorTables();

		template <class meshToMeshMethodType>
		class addcomponentsConstructorToTable
		{
		public:
			static autoPtr<meshToMeshMethod> New(const polyMesh& src, const polyMesh& tgt)
			{
				return autoPtr<meshToMeshMethod>(new meshToMeshMethodType(src, tgt));
			}

			addcomponentsConstructorToTable(const word& lookup = meshToMeshMethodType::typeName)
			{
				constructcomponentsConstructorTables();
				if (!componentsConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "meshToMeshMethod" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addcomponentsConstructorToTable() { destroycomponentsConstructorTables(); }
		};

		template <class meshToMeshMethodType>
		class addRemovablecomponentsConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<meshToMeshMethod> New(const polyMesh& src, const polyMesh& tgt)
			{
				return autoPtr<meshToMeshMethod>(new meshToMeshMethodType(src, tgt));
			}

			addRemovablecomponentsConstructorToTable(const word& lookup = meshToMeshMethodType::typeName) : lookup_(
				lookup)
			{
				constructcomponentsConstructorTables();
				componentsConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablecomponentsConstructorToTable()
			{
				if (componentsConstructorTablePtr_) { componentsConstructorTablePtr_->erase(lookup_); }
			}
		};

		// Constructors

			//- Construct from source and target meshes
		FoamSampling_EXPORT meshToMeshMethod(const polyMesh& src, const polyMesh& tgt);

		//- Disallow default bitwise copy construction
		FoamSampling_EXPORT meshToMeshMethod(const meshToMeshMethod&) = delete;


		//- Selector
		static FoamSampling_EXPORT autoPtr<meshToMeshMethod> New
		(
			const word& methodName,
			const polyMesh& src,
			const polyMesh& tgt
		);


		//- Destructor
		FoamSampling_EXPORT virtual ~meshToMeshMethod();


		// Member Functions

			// Evaluate

				//- Calculate addressing and weights
		FoamSampling_EXPORT virtual void calculate
		(
			labelListList& srcToTgtAddr,
			scalarListList& srcToTgtWght,
			labelListList& tgtToTgtAddr,
			scalarListList& tgtToTgtWght
		) = 0;


		// Access

			//- Return const access to the source mesh
		inline const polyMesh& src() const;

		//- Return const access to the target mesh
		inline const polyMesh& tgt() const;

		//- Return const access to the overlap volume
		inline scalar V() const;


		// Check

			//- Write the connectivity (debugging)
		FoamSampling_EXPORT void writeConnectivity
		(
			const polyMesh& mesh1,
			const polyMesh& mesh2,
			const labelListList& mesh1ToMesh2Addr
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSampling_EXPORT void operator=(const meshToMeshMethod&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <meshToMeshMethodI.hxx>

#endif // !_meshToMeshMethod_Header
