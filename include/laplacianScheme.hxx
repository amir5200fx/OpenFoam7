#pragma once
#ifndef _laplacianScheme_Header
#define _laplacianScheme_Header

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
	tnbLib::fv::laplacianScheme

Description
	Abstract base class for laplacian schemes.

SourceFiles
	laplacianScheme.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <linear.hxx>
#include <correctedSnGrad.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamLaplacianScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamLaplacianScheme_EXPORT_DEFINE
#define FoamLaplacianScheme_EXPORT __declspec(dllexport)
#else
#define FoamLaplacianScheme_EXPORT __declspec(dllimport)
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
								   Class laplacianScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type, class GType>
		class laplacianScheme
			:
			public tmp<laplacianScheme<Type, GType>>::refCount
		{

		protected:

			// Protected data

			const fvMesh& mesh_;
			tmp<surfaceInterpolationScheme<GType>> tinterpGammaScheme_;
			tmp<snGradScheme<Type>> tsnGradScheme_;


		private:

			// Private Member Functions

				//- Disallow default bitwise copy construction
			laplacianScheme(const laplacianScheme&);

			//- Disallow default bitwise assignment
			void operator=(const laplacianScheme&) = delete;


		public:

			//- Runtime type information
			virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			/*declareRunTimeSelectionTable
			(
				tmp,
				laplacianScheme,
				Istream,
				(const fvMesh& mesh, Istream& schemeData),
				(mesh, schemeData)
			);*/

			typedef tmp<laplacianScheme> (*IstreamConstructorPtr)(const fvMesh& mesh, Istream& schemeData);
			typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
			static FoamLaplacianScheme_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
			static FoamLaplacianScheme_EXPORT void constructIstreamConstructorTables();
			static FoamLaplacianScheme_EXPORT void destroyIstreamConstructorTables();

			template <class laplacianSchemeType>
			class addIstreamConstructorToTable
			{
			public:
				static tmp<laplacianScheme> New(const fvMesh& mesh, Istream& schemeData)
				{
					return tmp<laplacianScheme>(new laplacianSchemeType(mesh, schemeData));
				}

				addIstreamConstructorToTable(const word& lookup = laplacianSchemeType::typeName)
				{
					constructIstreamConstructorTables();
					if (!IstreamConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "laplacianScheme" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
			};

			template <class laplacianSchemeType>
			class addRemovableIstreamConstructorToTable
			{
				const word& lookup_;
			public:
				static tmp<laplacianScheme> New(const fvMesh& mesh, Istream& schemeData)
				{
					return tmp<laplacianScheme>(new laplacianSchemeType(mesh, schemeData));
				}

				addRemovableIstreamConstructorToTable(const word& lookup = laplacianSchemeType::typeName) : lookup_(lookup)
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
			laplacianScheme(const fvMesh& mesh)
				:
				mesh_(mesh),
				tinterpGammaScheme_(new linear<GType>(mesh)),
				tsnGradScheme_(new correctedSnGrad<Type>(mesh))
			{}

			//- Construct from mesh and Istream
			laplacianScheme(const fvMesh& mesh, Istream& is)
				:
				mesh_(mesh),
				tinterpGammaScheme_(nullptr),
				tsnGradScheme_(nullptr)
			{
				tinterpGammaScheme_ = tmp<surfaceInterpolationScheme<GType>>
					(
						surfaceInterpolationScheme<GType>::New(mesh, is)
						);

				tsnGradScheme_ = tmp<snGradScheme<Type>>
					(
						snGradScheme<Type>::New(mesh, is)
						);
			}

			//- Construct from mesh, interpolation and snGradScheme schemes
			laplacianScheme
			(
				const fvMesh& mesh,
				const tmp<surfaceInterpolationScheme<GType>>& igs,
				const tmp<snGradScheme<Type>>& sngs
			)
				:
				mesh_(mesh),
				tinterpGammaScheme_(igs),
				tsnGradScheme_(sngs)
			{}


			// Selectors

				//- Return a pointer to a new laplacianScheme created on freestore
			static tmp<laplacianScheme<Type, GType>> New
			(
				const fvMesh& mesh,
				Istream& schemeData
			);


			//- Destructor
			virtual ~laplacianScheme();


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return mesh_;
			}

			virtual tmp<fvMatrix<Type>> fvmLaplacian
			(
				const GeometricField<GType, fvsPatchField, surfaceMesh>&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<fvMatrix<Type>> fvmLaplacian
			(
				const GeometricField<GType, fvPatchField, volMesh>&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcLaplacian
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcLaplacian
			(
				const GeometricField<GType, fvsPatchField, surfaceMesh>&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcLaplacian
			(
				const GeometricField<GType, fvPatchField, volMesh>&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeFvLaplacianTypeScheme(SS, GType, Type)                             \
    typedef tnbLib::fv::SS<tnbLib::Type, tnbLib::GType> SS##Type##GType;             \
    defineNamedTemplateTypeNameAndDebug(SS##Type##GType, 0);                   \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            typedef SS<Type, GType> SS##Type##GType;                           \
                                                                               \
            laplacianScheme<Type, GType>::                                     \
                addIstreamConstructorToTable<SS<Type, GType>>                  \
                add##SS##Type##GType##IstreamConstructorToTable_;              \
        }                                                                      \
    }


#define makeFvLaplacianScheme(SS)                                              \
                                                                               \
makeFvLaplacianTypeScheme(SS, scalar, scalar)                                  \
makeFvLaplacianTypeScheme(SS, symmTensor, scalar)                              \
makeFvLaplacianTypeScheme(SS, tensor, scalar)                                  \
makeFvLaplacianTypeScheme(SS, scalar, vector)                                  \
makeFvLaplacianTypeScheme(SS, symmTensor, vector)                              \
makeFvLaplacianTypeScheme(SS, tensor, vector)                                  \
makeFvLaplacianTypeScheme(SS, scalar, sphericalTensor)                         \
makeFvLaplacianTypeScheme(SS, symmTensor, sphericalTensor)                     \
makeFvLaplacianTypeScheme(SS, tensor, sphericalTensor)                         \
makeFvLaplacianTypeScheme(SS, scalar, symmTensor)                              \
makeFvLaplacianTypeScheme(SS, symmTensor, symmTensor)                          \
makeFvLaplacianTypeScheme(SS, tensor, symmTensor)                              \
makeFvLaplacianTypeScheme(SS, scalar, tensor)                                  \
makeFvLaplacianTypeScheme(SS, symmTensor, tensor)                              \
makeFvLaplacianTypeScheme(SS, tensor, tensor)

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <laplacianSchemeI.hxx>

//#ifdef NoRepository
//#include <laplacianScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_laplacianScheme_Header
