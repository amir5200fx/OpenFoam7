#pragma once
#ifndef _ddtScheme_Header
#define _ddtScheme_Header

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
	tnbLib::fv::ddtScheme

Description
	Abstract base class for ddt schemes.

SourceFiles
	ddtScheme.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <dimensionedType.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamDdtScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamDdtScheme_EXPORT_DEFINE
#define FoamDdtScheme_EXPORT __declspec(dllexport)
#else
#define FoamDdtScheme_EXPORT __declspec(dllimport)
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
								   Class ddtScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class ddtScheme
			:
			public tmp<ddtScheme<Type>>::refCount
		{

		protected:

			// Protected data

			const fvMesh& mesh_;


		public:

			//- Runtime type information
			virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			/*declareRunTimeSelectionTable
			(
				tmp,
				ddtScheme,
				Istream,
				(const fvMesh& mesh, Istream& schemeData),
				(mesh, schemeData)
			);*/

			typedef tmp<ddtScheme> (*IstreamConstructorPtr)(const fvMesh& mesh, Istream& schemeData);
			typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
			static FoamDdtScheme_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
			static FoamDdtScheme_EXPORT void constructIstreamConstructorTables();
			static FoamDdtScheme_EXPORT void destroyIstreamConstructorTables();

			template <class ddtSchemeType>
			class addIstreamConstructorToTable
			{
			public:
				static tmp<ddtScheme> New(const fvMesh& mesh, Istream& schemeData)
				{
					return tmp<ddtScheme>(new ddtSchemeType(mesh, schemeData));
				}

				addIstreamConstructorToTable(const word& lookup = ddtSchemeType::typeName)
				{
					constructIstreamConstructorTables();
					if (!IstreamConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "ddtScheme" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
			};

			template <class ddtSchemeType>
			class addRemovableIstreamConstructorToTable
			{
				const word& lookup_;
			public:
				static tmp<ddtScheme> New(const fvMesh& mesh, Istream& schemeData)
				{
					return tmp<ddtScheme>(new ddtSchemeType(mesh, schemeData));
				}

				addRemovableIstreamConstructorToTable(const word& lookup = ddtSchemeType::typeName) : lookup_(lookup)
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
			ddtScheme(const fvMesh& mesh)
				:
				mesh_(mesh)
			{}

			//- Construct from mesh and Istream
			ddtScheme(const fvMesh& mesh, Istream&)
				:
				mesh_(mesh)
			{}

			//- Disallow default bitwise copy construction
			ddtScheme(const ddtScheme&);


			// Selectors

				//- Return a pointer to a new ddtScheme created on freestore
			static tmp<ddtScheme<Type>> New
			(
				const fvMesh& mesh,
				Istream& schemeData
			);


			//- Destructor
			virtual ~ddtScheme();


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return mesh_;
			}

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const dimensioned<Type>&
			) = 0;

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const dimensionedScalar&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const volScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<GeometricField<Type, fvPatchField, volMesh>> fvcDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> fvcDdt
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>&
			);

			virtual tmp<fvMatrix<Type>> fvmDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<fvMatrix<Type>> fvmDdt
			(
				const dimensionedScalar&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<fvMatrix<Type>> fvmDdt
			(
				const volScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;

			virtual tmp<fvMatrix<Type>> fvmDdt
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) = 0;

			typedef GeometricField
				<
				typename flux<Type>::type,
				fvsPatchField,
				surfaceMesh
				> fluxFieldType;

			virtual tmp<surfaceScalarField> fvcDdtPhiCoeff
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi,
				const fluxFieldType& phiCorr
			);

			virtual tmp<surfaceScalarField> fvcDdtPhiCoeff
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi,
				const fluxFieldType& phiCorr,
				const volScalarField& rho
			);

			virtual tmp<surfaceScalarField> fvcDdtPhiCoeff
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			);

			virtual tmp<surfaceScalarField> fvcDdtPhiCoeff
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi,
				const volScalarField& rho
			);

			virtual tmp<fluxFieldType> fvcDdtUfCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			) = 0;

			virtual tmp<fluxFieldType> fvcDdtPhiCorr
			(
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			) = 0;

			virtual tmp<fluxFieldType> fvcDdtUfCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const GeometricField<Type, fvsPatchField, surfaceMesh>& Uf
			) = 0;

			virtual tmp<fluxFieldType> fvcDdtPhiCorr
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			) = 0;

			virtual tmp<surfaceScalarField> meshPhi
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) = 0;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const ddtScheme&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeFvDdtTypeScheme(SS, Type)                                          \
    defineNamedTemplateTypeNameAndDebug(tnbLib::fv::SS<tnbLib::Type>, 0);          \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            ddtScheme<Type>::addIstreamConstructorToTable<SS<Type>>            \
                add##SS##Type##IstreamConstructorToTable_;                     \
        }                                                                      \
    }

#define makeFvDdtScheme(SS)                                                    \
                                                                               \
makeFvDdtTypeScheme(SS, scalar)                                                \
makeFvDdtTypeScheme(SS, vector)                                                \
makeFvDdtTypeScheme(SS, sphericalTensor)                                       \
makeFvDdtTypeScheme(SS, symmTensor)                                            \
makeFvDdtTypeScheme(SS, tensor)                                                \
                                                                               \
namespace tnbLib                                                                 \
{                                                                              \
namespace fv                                                                   \
{                                                                              \
                                                                               \
template<>                                                                     \
tmp<surfaceScalarField> SS<scalar>::fvcDdtUfCorr                               \
(                                                                              \
    const volScalarField& U,                                                   \
    const surfaceScalarField& Uf                                               \
)                                                                              \
{                                                                              \
    NotImplemented;                                                            \
    return surfaceScalarField::null();                                         \
}                                                                              \
                                                                               \
template<>                                                                     \
tmp<surfaceScalarField> SS<scalar>::fvcDdtPhiCorr                              \
(                                                                              \
    const volScalarField& U,                                                   \
    const surfaceScalarField& phi                                              \
)                                                                              \
{                                                                              \
    NotImplemented;                                                            \
    return surfaceScalarField::null();                                         \
}                                                                              \
                                                                               \
template<>                                                                     \
tmp<surfaceScalarField> SS<scalar>::fvcDdtUfCorr                               \
(                                                                              \
    const volScalarField& rho,                                                 \
    const volScalarField& U,                                                   \
    const surfaceScalarField& Uf                                               \
)                                                                              \
{                                                                              \
    NotImplemented;                                                            \
    return surfaceScalarField::null();                                         \
}                                                                              \
                                                                               \
template<>                                                                     \
tmp<surfaceScalarField> SS<scalar>::fvcDdtPhiCorr                              \
(                                                                              \
    const volScalarField& rho,                                                 \
    const volScalarField& U,                                                   \
    const surfaceScalarField& phi                                              \
)                                                                              \
{                                                                              \
    NotImplemented;                                                            \
    return surfaceScalarField::null();                                         \
}                                                                              \
                                                                               \
}                                                                              \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ddtSchemeI.hxx>

//#ifdef NoRepository
//#include <ddtScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_ddtScheme_Header
