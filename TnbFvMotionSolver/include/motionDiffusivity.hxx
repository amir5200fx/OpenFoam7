#pragma once
#ifndef _motionDiffusivity_Header
#define _motionDiffusivity_Header

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
	tnbLib::motionDiffusivity

Description
	Abstract base class for cell-centre mesh motion diffusivity.

SourceFiles
	motionDiffusivity.C

\*---------------------------------------------------------------------------*/

#include <surfaceFieldsFwd.hxx>
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class motionDiffusivity Declaration
	\*---------------------------------------------------------------------------*/

	class motionDiffusivity
	{
		// Private Data

			//- Mesh reference
		const fvMesh& mesh_;

	public:

		//- Runtime type information
		//TypeName("motionDiffusivity");
		static const char* typeName_() { return "motionDiffusivity"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			motionDiffusivity,
			Istream,
			(
				const fvMesh& mesh,
				Istream& mdData
				),
				(mesh, mdData)
		);*/

		typedef autoPtr<motionDiffusivity> (*IstreamConstructorPtr)(const fvMesh& mesh, Istream& mdData);
		typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
		static FoamFvMotionSolver_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
		static FoamFvMotionSolver_EXPORT void constructIstreamConstructorTables();
		static FoamFvMotionSolver_EXPORT void destroyIstreamConstructorTables();

		template <class motionDiffusivityType>
		class addIstreamConstructorToTable
		{
		public:
			static autoPtr<motionDiffusivity> New(const fvMesh& mesh, Istream& mdData)
			{
				return autoPtr<motionDiffusivity>(new motionDiffusivityType(mesh, mdData));
			}

			addIstreamConstructorToTable(const word& lookup = motionDiffusivityType::typeName)
			{
				constructIstreamConstructorTables();
				if (!IstreamConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "motionDiffusivity"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
		};

		template <class motionDiffusivityType>
		class addRemovableIstreamConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<motionDiffusivity> New(const fvMesh& mesh, Istream& mdData)
			{
				return autoPtr<motionDiffusivity>(new motionDiffusivityType(mesh, mdData));
			}

			addRemovableIstreamConstructorToTable(const word& lookup = motionDiffusivityType::typeName) : lookup_(
				lookup)
			{
				constructIstreamConstructorTables();
				IstreamConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableIstreamConstructorToTable()
			{
				if (IstreamConstructorTablePtr_) { IstreamConstructorTablePtr_->erase(lookup_); }
			}
		};


		// Selectors

			//- Select null constructed
		static FoamFvMotionSolver_EXPORT autoPtr<motionDiffusivity> New
		(
			const fvMesh& mesh,
			Istream& mdData
		);


		// Constructors

			//- Construct for the given fvMesh
		FoamFvMotionSolver_EXPORT motionDiffusivity(const fvMesh& mesh);


		//- Destructor
		FoamFvMotionSolver_EXPORT virtual ~motionDiffusivity();


		// Member Functions

			//- Return reference to the mesh
		const fvMesh& mesh() const
		{
			return mesh_;
		}

		//- Correct the motion diffusivity
		virtual void correct()
		{}


		// Member Operators

			//- Return diffusivity field
		FoamFvMotionSolver_EXPORT virtual tmp<surfaceScalarField> operator()() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_motionDiffusivity_Header
