#pragma once
#ifndef _SRFModel_Header
#define _SRFModel_Header

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

Namespace
	tnbLib::SRF

Description
	Namespace for single rotating frame (SRF) models

Class
	tnbLib::SRF::SRFModel

Description
	Top level model for single rotating frame
	- Steady state only - no time derivatives included

SourceFiles
	SRFModel.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <fvMesh.hxx>
#include <volFields.hxx>
#include <vectorField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace SRF
	{

		/*---------------------------------------------------------------------------*\
								   Class SRFModel Declaration
		\*---------------------------------------------------------------------------*/

		class SRFModel
			:
			public IOdictionary
		{

		protected:

			// Protected data

				//- Reference to the relative velocity field
			const volVectorField& Urel_;

			//- Reference to the mesh
			const fvMesh& mesh_;

			//- Origin of the axis
			dimensionedVector origin_;

			//- Axis of rotation, a direction vector which passes through the origin
			vector axis_;

			//- SRF model coeficients dictionary
			dictionary SRFModelCoeffs_;

			//- Angular velocity of the frame (rad/s)
			dimensionedVector omega_;


		public:

			//- Runtime type information
			//TypeName("SRFModel");
			static const char* typeName_() { return "SRFModel"; }
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
			static FoamFiniteVolume_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Declare runtime constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				SRFModel,
				dictionary,
				(
					const volVectorField& Urel
					),
					(Urel)
			);*/

			typedef autoPtr<SRFModel> (*dictionaryConstructorPtr)(const volVectorField& Urel);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamFiniteVolume_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamFiniteVolume_EXPORT void constructdictionaryConstructorTables();
			static FoamFiniteVolume_EXPORT void destroydictionaryConstructorTables();

			template <class SRFModelType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<SRFModel> New(const volVectorField& Urel) { return autoPtr<SRFModel>(new SRFModelType(Urel)); }

				adddictionaryConstructorToTable(const word& lookup = SRFModelType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "SRFModel" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class SRFModelType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<SRFModel> New(const volVectorField& Urel) { return autoPtr<SRFModel>(new SRFModelType(Urel)); }

				addRemovabledictionaryConstructorToTable(const word& lookup = SRFModelType::typeName) : lookup_(lookup)
				{
					constructdictionaryConstructorTables();
					dictionaryConstructorTablePtr_->set(lookup, New);
				}

				~addRemovabledictionaryConstructorToTable()
				{
					if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

				//- Construct from components
			FoamFiniteVolume_EXPORT SRFModel
			(
				const word& type,
				const volVectorField& Urel
			);

			//- Disallow default bitwise copy construction
			FoamFiniteVolume_EXPORT SRFModel(const SRFModel&) = delete;


			// Selectors

				 //- Return a reference to the selected SRF model
			static FoamFiniteVolume_EXPORT autoPtr<SRFModel> New
			(
				const volVectorField& Urel
			);


			//- Destructor
			FoamFiniteVolume_EXPORT virtual ~SRFModel();


			// Member Functions

				// Edit

					//- Read radiationProperties dictionary
			FoamFiniteVolume_EXPORT virtual bool read();


			// Access

				//- Return the origin of rotation
			FoamFiniteVolume_EXPORT 	const dimensionedVector& origin() const;

			//- Return the axis of rotation
			FoamFiniteVolume_EXPORT const vector& axis() const;

			//- Return the angular velocity field [rad/s]
			FoamFiniteVolume_EXPORT const dimensionedVector& omega() const;

			//- Return the coriolis force
			FoamFiniteVolume_EXPORT tmp<volVectorField::Internal> Fcoriolis() const;

			//- Return the centrifugal force
			FoamFiniteVolume_EXPORT tmp<volVectorField::Internal> Fcentrifugal() const;

			//- Source term component for momentum equation
			FoamFiniteVolume_EXPORT tmp<volVectorField::Internal> Su() const;

			//- Return velocity vector from positions
			FoamFiniteVolume_EXPORT vectorField velocity(const vectorField& positions) const;

			//- Return velocity of SRF for complete mesh
			FoamFiniteVolume_EXPORT tmp<volVectorField> U() const;

			//- Return absolute velocity for complete mesh
			FoamFiniteVolume_EXPORT tmp<volVectorField> Uabs() const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFiniteVolume_EXPORT void operator=(const SRFModel&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace SRF
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SRFModel_Header
