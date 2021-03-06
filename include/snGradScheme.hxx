#pragma once
#ifndef _snGradScheme_Header
#define _snGradScheme_Header

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
	tnbLib::fv::snGradScheme

Description
	Abstract base class for snGrad schemes.

SourceFiles
	snGradScheme.C

\*---------------------------------------------------------------------------*/


#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamSnGradScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamSnGradScheme_EXPORT_DEFINE
#define FoamSnGradScheme_EXPORT __declspec(dllexport)
#else
#define FoamSnGradScheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						 Class snGradScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class snGradScheme
			:
			public tmp<snGradScheme<Type>>::refCount
		{
			// Private Data

				//- Hold reference to mesh
			const fvMesh& mesh_;


		public:

			//- Runtime type information
			virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			/*declareRunTimeSelectionTable
			(
				tmp,
				snGradScheme,
				Mesh,
				(const fvMesh& mesh, Istream& schemeData),
				(mesh, schemeData)
			);*/

			typedef tmp<snGradScheme> (*MeshConstructorPtr)(const fvMesh& mesh, Istream& schemeData);
			typedef HashTable<MeshConstructorPtr, word, string::hash> MeshConstructorTable;
			static FoamSnGradScheme_EXPORT MeshConstructorTable* MeshConstructorTablePtr_;
			static FoamSnGradScheme_EXPORT void constructMeshConstructorTables();
			static FoamSnGradScheme_EXPORT void destroyMeshConstructorTables();

			template <class snGradSchemeType>
			class addMeshConstructorToTable
			{
			public:
				static tmp<snGradScheme> New(const fvMesh& mesh, Istream& schemeData)
				{
					return tmp<snGradScheme>(new snGradSchemeType(mesh, schemeData));
				}

				addMeshConstructorToTable(const word& lookup = snGradSchemeType::typeName)
				{
					constructMeshConstructorTables();
					if (!MeshConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "snGradScheme" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addMeshConstructorToTable() { destroyMeshConstructorTables(); }
			};

			template <class snGradSchemeType>
			class addRemovableMeshConstructorToTable
			{
				const word& lookup_;
			public:
				static tmp<snGradScheme> New(const fvMesh& mesh, Istream& schemeData)
				{
					return tmp<snGradScheme>(new snGradSchemeType(mesh, schemeData));
				}

				addRemovableMeshConstructorToTable(const word& lookup = snGradSchemeType::typeName) : lookup_(lookup)
				{
					constructMeshConstructorTables();
					MeshConstructorTablePtr_->set(lookup, New);
				}

				~addRemovableMeshConstructorToTable()
				{
					if (MeshConstructorTablePtr_) { MeshConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

				//- Construct from mesh
			snGradScheme(const fvMesh& mesh)
				:
				mesh_(mesh)
			{}

			//- Disallow default bitwise copy construction
			snGradScheme(const snGradScheme&);


			// Selectors

				//- Return new tmp interpolation scheme
			static tmp<snGradScheme<Type>> New
			(
				const fvMesh& mesh,
				Istream& schemeData
			);


			//- Destructor
			virtual ~snGradScheme();


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return mesh_;
			}


			//- Return the snGrad of the given cell field with the given deltaCoeffs
			static tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				snGrad
				(
					const GeometricField<Type, fvPatchField, volMesh>&,
					const tmp<surfaceScalarField>&,
					const word& snGradName = "snGrad"
				);

			//- Return the sndGrad of the given cell field
			static tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				sndGrad
				(
					const GeometricField<Type, fvPatchField, volMesh>&,
					const word& snGradName = "sndGrad"
				);

			//- Return the interpolation weighting factors for the given field
			virtual tmp<surfaceScalarField> deltaCoeffs
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) const = 0;

			//- Return true if this scheme uses an explicit correction
			virtual bool corrected() const
			{
				return false;
			}

			//- Return the explicit correction to the snGrad
			//  for the given field
			virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				correction(const GeometricField<Type, fvPatchField, volMesh>&) const
			{
				return tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
					(
						nullptr
						);
			}

			//- Return the snGrad of the given cell field
			//  with explicit correction
			virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				snGrad(const GeometricField<Type, fvPatchField, volMesh>&) const;

			//- Return the snGrad of the given tmp cell field
			//  with explicit correction
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				snGrad
				(
					const tmp<GeometricField<Type, fvPatchField, volMesh>>&
				) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const snGradScheme&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeSnGradTypeScheme(SS, Type)                                         \
    defineNamedTemplateTypeNameAndDebug(tnbLib::fv::SS<tnbLib::Type>, 0);          \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            snGradScheme<Type>::addMeshConstructorToTable<SS<Type>>            \
                add##SS##Type##MeshConstructorToTable_;                        \
        }                                                                      \
    }

#define makeSnGradScheme(SS)                                                   \
                                                                               \
makeSnGradTypeScheme(SS, scalar)                                               \
makeSnGradTypeScheme(SS, vector)                                               \
makeSnGradTypeScheme(SS, sphericalTensor)                                      \
makeSnGradTypeScheme(SS, symmTensor)                                           \
makeSnGradTypeScheme(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <snGradSchemeI.hxx>

//#ifdef NoRepository
//#include <snGradScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_snGradScheme_Header
