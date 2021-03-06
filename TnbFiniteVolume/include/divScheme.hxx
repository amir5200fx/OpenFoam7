#pragma once
#ifndef _divScheme_Header
#define _divScheme_Header

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
	tnbLib::fv::divScheme

Description
	Abstract base class for div schemes.

SourceFiles
	divScheme.C

\*---------------------------------------------------------------------------*/


#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <linear.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamDivScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamDivScheme_EXPORT_DEFINE
#define FoamDivScheme_EXPORT __declspec(dllexport)
#else
#define FoamDivScheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Type>
	class fvMatrix;

	class fvMesh;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								   Class divScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class divScheme
			:
			public tmp<divScheme<Type>>::refCount
		{

		protected:

			// Protected data

			const fvMesh& mesh_;
			tmp<surfaceInterpolationScheme<Type>> tinterpScheme_;


		public:

			//- Runtime type information
			virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			/*declareRunTimeSelectionTable
			(
				tmp,
				divScheme,
				Istream,
				(const fvMesh& mesh, Istream& schemeData),
				(mesh, schemeData)
			);*/

			typedef tmp<divScheme> (*IstreamConstructorPtr)(const fvMesh& mesh, Istream& schemeData);
			typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
			static FoamDivScheme_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
			static FoamDivScheme_EXPORT void constructIstreamConstructorTables();
			static FoamDivScheme_EXPORT void destroyIstreamConstructorTables();

			template <class divSchemeType>
			class addIstreamConstructorToTable
			{
			public:
				static tmp<divScheme> New(const fvMesh& mesh, Istream& schemeData)
				{
					return tmp<divScheme>(new divSchemeType(mesh, schemeData));
				}

				addIstreamConstructorToTable(const word& lookup = divSchemeType::typeName)
				{
					constructIstreamConstructorTables();
					if (!IstreamConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "divScheme" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
			};

			template <class divSchemeType>
			class addRemovableIstreamConstructorToTable
			{
				const word& lookup_;
			public:
				static tmp<divScheme> New(const fvMesh& mesh, Istream& schemeData)
				{
					return tmp<divScheme>(new divSchemeType(mesh, schemeData));
				}

				addRemovableIstreamConstructorToTable(const word& lookup = divSchemeType::typeName) : lookup_(lookup)
				{
					constructIstreamConstructorTables();
					IstreamConstructorTablePtr_->set(lookup, New);
				}

				~addRemovableIstreamConstructorToTable()
				{
					if (IstreamConstructorTablePtr_) { IstreamConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

				//- Construct from mesh
			divScheme(const fvMesh& mesh)
				:
				mesh_(mesh),
				tinterpScheme_(new linear<Type>(mesh))
			{}

			//- Construct from mesh and Istream
			divScheme(const fvMesh& mesh, Istream& is)
				:
				mesh_(mesh),
				tinterpScheme_(surfaceInterpolationScheme<Type>::New(mesh, is))
			{}

			//- Disallow default bitwise copy construction
			divScheme(const divScheme&) = delete;


			// Selectors

				//- Return a pointer to a new divScheme created on freestore
			static tmp<divScheme<Type>> New
			(
				const fvMesh& mesh,
				Istream& schemeData
			);


			//- Destructor
			virtual ~divScheme();


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return mesh_;
			}

			virtual tmp
				<
				GeometricField
				<typename innerProduct<vector, Type>::type, fvPatchField, volMesh>
				> fvcDiv
				(
					const GeometricField<Type, fvPatchField, volMesh>&
				) = 0;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const divScheme&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeFvDivTypeScheme(SS, Type)                                          \
    defineNamedTemplateTypeNameAndDebug(tnbLib::fv::SS<tnbLib::Type>, 0);          \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            divScheme<Type>::addIstreamConstructorToTable<SS<Type>>            \
                add##SS##Type##IstreamConstructorToTable_;                     \
        }                                                                      \
    }

#define makeFvDivScheme(SS)                                                    \
                                                                               \
makeFvDivTypeScheme(SS, vector)                                                \
makeFvDivTypeScheme(SS, sphericalTensor)                                       \
makeFvDivTypeScheme(SS, symmTensor)                                            \
makeFvDivTypeScheme(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <divSchemeI.hxx>

//#ifdef NoRepository
//#include <divScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_divScheme_Header
