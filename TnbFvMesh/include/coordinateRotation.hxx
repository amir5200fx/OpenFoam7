#pragma once
#ifndef _coordinateRotation_Header
#define _coordinateRotation_Header

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

Class
	tnbLib::coordinateRotation

Description
	Abstract base class for coordinate rotation

	\verbatim
	coordinateRotation
	{
		type        axesRotation
		e1          (1 0 0);
		e2          (0 1 0);
	}
	\endverbatim

	Types of coordinateRotation:
	  -# axesRotation
	  -# STARCDRotation
	  -# cylindrical
	  -# EulerCoordinateRotation

SourceFiles
	coordinateRotation.C
	coordinateRotationNew.C

\*---------------------------------------------------------------------------*/

#include <vector.hxx>
#include <tensor.hxx>
#include <tensorField.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>
#include <objectRegistry.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class coordinateRotation Declaration
	\*---------------------------------------------------------------------------*/

	class coordinateRotation
	{
	protected:

		// Protected member functions

			//- Transform principal
		FoamFvMesh_EXPORT symmTensor transformPrincipal(const tensor&, const vector&) const;


	public:


		//- Runtime type information
		//TypeName("coordinateRotation");
		static const char* typeName_() { return "coordinateRotation"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table
		// for constructors with dictionary and objectRegistry
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			coordinateRotation,
			objectRegistry,
			(
				const dictionary& dict, const objectRegistry& obr
				),
				(dict, obr)
		);*/

		typedef autoPtr<coordinateRotation> (*objectRegistryConstructorPtr
		)(const dictionary& dict, const objectRegistry& obr);
		typedef HashTable<objectRegistryConstructorPtr, word, string::hash> objectRegistryConstructorTable;
		static FoamFvMesh_EXPORT objectRegistryConstructorTable* objectRegistryConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructobjectRegistryConstructorTables();
		static FoamFvMesh_EXPORT void destroyobjectRegistryConstructorTables();

		template <class coordinateRotationType>
		class addobjectRegistryConstructorToTable
		{
		public:
			static autoPtr<coordinateRotation> New(const dictionary& dict, const objectRegistry& obr)
			{
				return autoPtr<coordinateRotation>(new coordinateRotationType(dict, obr));
			}

			addobjectRegistryConstructorToTable(const word& lookup = coordinateRotationType::typeName)
			{
				constructobjectRegistryConstructorTables();
				if (!objectRegistryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "coordinateRotation" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addobjectRegistryConstructorToTable() { destroyobjectRegistryConstructorTables(); }
		};

		template <class coordinateRotationType>
		class addRemovableobjectRegistryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<coordinateRotation> New(const dictionary& dict, const objectRegistry& obr)
			{
				return autoPtr<coordinateRotation>(new coordinateRotationType(dict, obr));
			}

			addRemovableobjectRegistryConstructorToTable(const word& lookup = coordinateRotationType::typeName) : lookup_(lookup)
			{
				constructobjectRegistryConstructorTables();
				objectRegistryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableobjectRegistryConstructorToTable()
			{
				if (objectRegistryConstructorTablePtr_) { objectRegistryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Declare run-time constructor selection table
		// for constructors with dictionary
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			coordinateRotation,
			dictionary,
			(
				const dictionary& dict
				),
				(dict)
		);*/

		typedef autoPtr<coordinateRotation> (*dictionaryConstructorPtr)(const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamFvMesh_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructdictionaryConstructorTables();
		static FoamFvMesh_EXPORT void destroydictionaryConstructorTables();

		template <class coordinateRotationType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<coordinateRotation> New(const dictionary& dict)
			{
				return autoPtr<coordinateRotation>(new coordinateRotationType(dict));
			}

			adddictionaryConstructorToTable(const word& lookup = coordinateRotationType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "coordinateRotation" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class coordinateRotationType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<coordinateRotation> New(const dictionary& dict)
			{
				return autoPtr<coordinateRotation>(new coordinateRotationType(dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = coordinateRotationType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Selectors

			//- Select constructed from dictionary and objectRegistry
		static FoamFvMesh_EXPORT autoPtr<coordinateRotation> New
		(
			const dictionary& dict, const objectRegistry& obr
		);

		//- Select constructed from dictionary
		static FoamFvMesh_EXPORT autoPtr<coordinateRotation> New
		(
			const dictionary& dict
		);


		//- Destructor
		virtual ~coordinateRotation()
		{}


		// Member Functions

			//- Reset rotation to an identity rotation
		FoamFvMesh_EXPORT virtual void clear() = 0;

		//- Update the rotation for a list of cells
		FoamFvMesh_EXPORT virtual void updateCells
		(
			const polyMesh& mesh,
			const labelList& cells
		) = 0;

		//- Return local-to-global transformation tensor
		FoamFvMesh_EXPORT virtual const tensor& R() const = 0;

		//- Return global-to-local transformation tensor
		FoamFvMesh_EXPORT virtual const tensor& Rtr() const = 0;

		//- Return local Cartesian x-axis
		FoamFvMesh_EXPORT virtual const vector e1() const = 0;

		//- Return local Cartesian y-axis
		FoamFvMesh_EXPORT virtual const vector e2() const = 0;

		//- Return local Cartesian z-axis
		FoamFvMesh_EXPORT virtual const vector e3() const = 0;

		//- Return local-to-global transformation tensor
		FoamFvMesh_EXPORT virtual const tensorField& Tr() const = 0;

		//- Return true if the rotation tensor is uniform
		virtual bool uniform() const
		{
			return true;
		}

		//- Transform vectorField using transformation tensor field
		FoamFvMesh_EXPORT virtual tmp<vectorField> transform(const vectorField& st) const = 0;

		//- Transform vector using transformation tensor
		FoamFvMesh_EXPORT virtual vector transform(const vector& st) const = 0;

		//- Inverse transform vectorField using transformation tensor field
		FoamFvMesh_EXPORT virtual tmp<vectorField> invTransform(const vectorField& st) const = 0;

		//- Inverse transform vector using transformation tensor
		FoamFvMesh_EXPORT virtual vector invTransform(const vector& st) const = 0;

		//- Transform tensor field using transformation tensorField
		FoamFvMesh_EXPORT virtual tmp<tensorField> transformTensor
		(
			const tensorField& st
		) const = 0;

		//- Transform tensor sub-field using transformation tensorField
		FoamFvMesh_EXPORT virtual tmp<tensorField> transformTensor
		(
			const tensorField& st,
			const labelList& cellMap
		) const = 0;

		//- Transform tensor using transformation tensorField
		FoamFvMesh_EXPORT virtual tensor transformTensor(const tensor& st) const = 0;

		//- Transform vectorField using transformation tensorField and return
		// symmetrical tensorField
		FoamFvMesh_EXPORT virtual tmp<symmTensorField> transformVector
		(
			const vectorField& st
		) const = 0;

		//- Transform vector using transformation tensor and return
		// symmetrical tensor
		FoamFvMesh_EXPORT virtual symmTensor transformVector(const vector& st) const = 0;


		// Write

				//- Write
		FoamFvMesh_EXPORT virtual void write(Ostream&) const = 0;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coordinateRotation_Header
