#pragma once
#ifndef _rigidBody_Header
#define _rigidBody_Header

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
	tnbLib::RBD::rigidBody

Description

SourceFiles
	rigidBodyI.H

\*---------------------------------------------------------------------------*/

#include <rigidBodyInertia.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{

		// Forward declaration of classes
		class subBody;

		// Forward declaration of friend functions and operators
		class rigidBody;

		inline Ostream& operator<<(Ostream&, const rigidBody&);


		/*---------------------------------------------------------------------------*\
								 Class rigidBody Declaration
		\*---------------------------------------------------------------------------*/

		class rigidBody
			:
			public rigidBodyInertia
		{
			// Private Data

				//- Name of body
			word name_;


		public:

			//- Runtime type information
			//TypeName("rigidBody");
			static const char* typeName_() { return "rigidBody"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Declare run-time constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				rigidBody,
				dictionary,
				(const word& name, const dictionary& dict),
				(name, dict)
			);*/

			typedef autoPtr<rigidBody> (*dictionaryConstructorPtr)(const word& name, const dictionary& dict);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamRigidBodyMotion_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamRigidBodyMotion_EXPORT void constructdictionaryConstructorTables();
			static FoamRigidBodyMotion_EXPORT void destroydictionaryConstructorTables();

			template <class rigidBodyType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<rigidBody> New(const word& name, const dictionary& dict)
				{
					return autoPtr<rigidBody>(new rigidBodyType(name, dict));
				}

				adddictionaryConstructorToTable(const word& lookup = rigidBodyType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "rigidBody" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class rigidBodyType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<rigidBody> New(const word& name, const dictionary& dict)
				{
					return autoPtr<rigidBody>(new rigidBodyType(name, dict));
				}

				addRemovabledictionaryConstructorToTable(const word& lookup = rigidBodyType::typeName) : lookup_(lookup)
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

				//- Construct from mass, centre of mass and moment of inertia tensor
				//  about the centre of mass
			inline rigidBody
			(
				const word& name,
				const scalar& m,
				const vector& c,
				const symmTensor& Ic
			);

			//- Construct from with the given rigidBodyInertia
			inline rigidBody
			(
				const word& name,
				const rigidBodyInertia& rbi
			);

			//- Construct from dictionary
			inline rigidBody
			(
				const word& name,
				const dictionary& dict
			);

			//- Return clone of this rigidBody
			FoamRigidBodyMotion_EXPORT virtual autoPtr<rigidBody> clone() const;


			// Selectors

				//- Select constructed from components
			static FoamRigidBodyMotion_EXPORT autoPtr<rigidBody> New
			(
				const word& name,
				const scalar& m,
				const vector& c,
				const symmTensor& Ic
			);

			//- Select constructed from name and dictionary
			static FoamRigidBodyMotion_EXPORT autoPtr<rigidBody> New
			(
				const word& name,
				const dictionary& dict
			);


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~rigidBody();


			// Member Functions

				//- Return name
			inline const word& name() const;

			//- Return false as this body is not massless
			FoamRigidBodyMotion_EXPORT virtual bool massless() const;

			//- Merge a body into this parent body
			FoamRigidBodyMotion_EXPORT void merge(const subBody&);

			//- Write
			FoamRigidBodyMotion_EXPORT virtual void write(Ostream&) const;


			// Ostream Operator

			friend Ostream& operator<<(Ostream&, const rigidBody&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <rigidBodyI.hxx>

#endif // !_rigidBody_Header
