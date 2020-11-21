#pragma once
#ifndef _convectionScheme_Header
#define _convectionScheme_Header

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
	tnbLib::fv::convectionScheme

Description
	Abstract base class for convection schemes.

SourceFiles
	convectionScheme.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <multivariateSurfaceInterpolationScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamConvectionScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamConvectionScheme_EXPORT_DEFINE
#define FoamConvectionScheme_EXPORT __declspec(dllexport)
#else
#define FoamConvectionScheme_EXPORT __declspec(dllimport)
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
								   Class convectionScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class convectionScheme
			:
			public tmp<convectionScheme<Type>>::refCount
		{
			// Private Data

			const fvMesh& mesh_;


		public:

			//- Runtime type information
			virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			/*declareRunTimeSelectionTable
			(
				tmp,
				convectionScheme,
				Istream,
				(
					const fvMesh& mesh,
					const surfaceScalarField& faceFlux,
					Istream& schemeData
					),
					(mesh, faceFlux, schemeData)
			);

			declareRunTimeSelectionTable
			(
				tmp,
				convectionScheme,
				Multivariate,
				(
					const fvMesh& mesh,
					const typename multivariateSurfaceInterpolationScheme<Type>::
					fieldTable& fields,
					const surfaceScalarField& faceFlux,
					Istream& schemeData
					),
					(mesh, fields, faceFlux, schemeData)
			);*/

			typedef tmp<convectionScheme> (*IstreamConstructorPtr)(const fvMesh& mesh, const surfaceScalarField& faceFlux,
			                                                       Istream& schemeData);
			typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
			static FoamConvectionScheme_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
			static FoamConvectionScheme_EXPORT void constructIstreamConstructorTables();
			static FoamConvectionScheme_EXPORT void destroyIstreamConstructorTables();

			template <class convectionSchemeType>
			class addIstreamConstructorToTable
			{
			public:
				static tmp<convectionScheme> New(const fvMesh& mesh, const surfaceScalarField& faceFlux, Istream& schemeData)
				{
					return tmp<convectionScheme>(new convectionSchemeType(mesh, faceFlux, schemeData));
				}

				addIstreamConstructorToTable(const word& lookup = convectionSchemeType::typeName)
				{
					constructIstreamConstructorTables();
					if (!IstreamConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "convectionScheme" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
			};

			template <class convectionSchemeType>
			class addRemovableIstreamConstructorToTable
			{
				const word& lookup_;
			public:
				static tmp<convectionScheme> New(const fvMesh& mesh, const surfaceScalarField& faceFlux, Istream& schemeData)
				{
					return tmp<convectionScheme>(new convectionSchemeType(mesh, faceFlux, schemeData));
				}

				addRemovableIstreamConstructorToTable(const word& lookup = convectionSchemeType::typeName) : lookup_(lookup)
				{
					constructIstreamConstructorTables();
					IstreamConstructorTablePtr_->set(lookup, New);
				}

				~addRemovableIstreamConstructorToTable()
				{
					if (IstreamConstructorTablePtr_) { IstreamConstructorTablePtr_->erase(lookup_); }
				}
			};;

			typedef tmp<convectionScheme> (*MultivariateConstructorPtr)(const fvMesh& mesh,
			                                                            const typename multivariateSurfaceInterpolationScheme<
				                                                            Type>::fieldTable& fields,
			                                                            const surfaceScalarField& faceFlux, Istream& schemeData);
			typedef HashTable<MultivariateConstructorPtr, word, string::hash> MultivariateConstructorTable;
			static FoamConvectionScheme_EXPORT MultivariateConstructorTable* MultivariateConstructorTablePtr_;
			static FoamConvectionScheme_EXPORT void constructMultivariateConstructorTables();
			static FoamConvectionScheme_EXPORT void destroyMultivariateConstructorTables();

			template <class convectionSchemeType>
			class addMultivariateConstructorToTable
			{
			public:
				static tmp<convectionScheme> New(const fvMesh& mesh,
				                                 const typename multivariateSurfaceInterpolationScheme<Type>::fieldTable& fields,
				                                 const surfaceScalarField& faceFlux, Istream& schemeData)
				{
					return tmp<convectionScheme>(new convectionSchemeType(mesh, fields, faceFlux, schemeData));
				}

				addMultivariateConstructorToTable(const word& lookup = convectionSchemeType::typeName)
				{
					constructMultivariateConstructorTables();
					if (!MultivariateConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "convectionScheme" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addMultivariateConstructorToTable() { destroyMultivariateConstructorTables(); }
			};

			template <class convectionSchemeType>
			class addRemovableMultivariateConstructorToTable
			{
				const word& lookup_;
			public:
				static tmp<convectionScheme> New(const fvMesh& mesh,
				                                 const typename multivariateSurfaceInterpolationScheme<Type>::fieldTable& fields,
				                                 const surfaceScalarField& faceFlux, Istream& schemeData)
				{
					return tmp<convectionScheme>(new convectionSchemeType(mesh, fields, faceFlux, schemeData));
				}

				addRemovableMultivariateConstructorToTable(const word& lookup = convectionSchemeType::typeName) : lookup_(lookup)
				{
					constructMultivariateConstructorTables();
					MultivariateConstructorTablePtr_->set(lookup, New);
				}

				~addRemovableMultivariateConstructorToTable()
				{
					if (MultivariateConstructorTablePtr_) { MultivariateConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

				//- Copy construct
			convectionScheme(const convectionScheme&);

			//- Construct from mesh, flux and Istream
			convectionScheme
			(
				const fvMesh& mesh,
				const surfaceScalarField&
			)
				:
				mesh_(mesh)
			{}


			// Selectors

				//- Return a pointer to a new convectionScheme created on freestore
			static tmp<convectionScheme<Type>> New
			(
				const fvMesh& mesh,
				const surfaceScalarField& faceFlux,
				Istream& schemeData
			);


			//- Return a pointer to a new multivariate convectionScheme
			//  created on freestore
			static tmp<convectionScheme<Type>> New
			(
				const fvMesh& mesh,
				const typename multivariateSurfaceInterpolationScheme<Type>::
				fieldTable& fields,
				const surfaceScalarField& faceFlux,
				Istream& schemeData
			);


			//- Destructor
			virtual ~convectionScheme();


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return mesh_;
			}

			virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				interpolate
				(
					const surfaceScalarField&,
					const GeometricField<Type, fvPatchField, volMesh>&
				) const = 0;

			virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> flux
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const = 0;

			virtual tmp<fvMatrix<Type>> fvmDiv
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const = 0;

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDiv
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const = 0;


			// Member Operators

			void operator=(const convectionScheme<Type>&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeFvConvectionTypeScheme(SS, Type)                                   \
    defineNamedTemplateTypeNameAndDebug(tnbLib::fv::SS<tnbLib::Type>, 0);          \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            convectionScheme<Type>::addIstreamConstructorToTable<SS<Type>>     \
                add##SS##Type##IstreamConstructorToTable_;                     \
        }                                                                      \
    }

#define makeFvConvectionScheme(SS)                                             \
                                                                               \
makeFvConvectionTypeScheme(SS, scalar)                                         \
makeFvConvectionTypeScheme(SS, vector)                                         \
makeFvConvectionTypeScheme(SS, sphericalTensor)                                \
makeFvConvectionTypeScheme(SS, symmTensor)                                     \
makeFvConvectionTypeScheme(SS, tensor)


#define makeMultivariateFvConvectionTypeScheme(SS, Type)                       \
    defineNamedTemplateTypeNameAndDebug(tnbLib::fv::SS<tnbLib::Type>, 0);          \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            convectionScheme<Type>::                                           \
                addMultivariateConstructorToTable<SS<Type>>                    \
                add##SS##Type##MultivariateConstructorToTable_;                \
        }                                                                      \
    }


#define makeMultivariateFvConvectionScheme(SS)                                 \
                                                                               \
makeMultivariateFvConvectionTypeScheme(SS, scalar)                             \
makeMultivariateFvConvectionTypeScheme(SS, vector)                             \
makeMultivariateFvConvectionTypeScheme(SS, sphericalTensor)                    \
makeMultivariateFvConvectionTypeScheme(SS, symmTensor)                         \
makeMultivariateFvConvectionTypeScheme(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <convectionSchemeI.hxx>

//#ifdef NoRepository
//#include <convectionScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_convectionScheme_Header
