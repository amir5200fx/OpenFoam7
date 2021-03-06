#pragma once
#ifndef _multivariateSurfaceInterpolationScheme_Header
#define _multivariateSurfaceInterpolationScheme_Header

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
	tnbLib::multivariateSurfaceInterpolationScheme

Description
	Abstract base class for multi-variate surface interpolation schemes.

SourceFiles
	multivariateSurfaceInterpolationScheme.C

\*---------------------------------------------------------------------------*/

#include <surfaceInterpolationScheme.hxx>
#include <HashTable.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamMultivariateSurfaceInterpolationScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamMultivariateSurfaceInterpolationScheme_EXPORT_DEFINE
#define FoamMultivariateSurfaceInterpolationScheme_EXPORT __declspec(dllexport)
#else
#define FoamMultivariateSurfaceInterpolationScheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class multivariateSurfaceInterpolationScheme Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class multivariateSurfaceInterpolationScheme
		:
		public tmp<multivariateSurfaceInterpolationScheme<Type>>::refCount
	{

	public:

		//- fieldTable
		class fieldTable
			:
			public HashTable<const GeometricField<Type, fvPatchField, volMesh>*>
		{
		public:

			fieldTable()
			{}

			void add(const GeometricField<Type, fvPatchField, volMesh>& f)
			{
				this->insert(f.name(), &f);
			}
		};


	private:

		// Private Data

			//- Hold reference to mesh
		const fvMesh& mesh_;

		//- HashTable of pointers to the field set
		const fieldTable& fields_;


	public:

		//- Runtime type information
		virtual const word& type() const = 0;


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			tmp,
			multivariateSurfaceInterpolationScheme,
			Istream,
			(
				const fvMesh& mesh,
				const fieldTable& fields,
				const surfaceScalarField& faceFlux,
				Istream& is
				),
				(mesh, fields, faceFlux, is)
		);*/

		typedef tmp<multivariateSurfaceInterpolationScheme> (*IstreamConstructorPtr)(
			const fvMesh& mesh, const fieldTable& fields, const surfaceScalarField& faceFlux, Istream& is);
		typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
		static FoamMultivariateSurfaceInterpolationScheme_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
		static FoamMultivariateSurfaceInterpolationScheme_EXPORT void constructIstreamConstructorTables();
		static FoamMultivariateSurfaceInterpolationScheme_EXPORT void destroyIstreamConstructorTables();

		template <class multivariateSurfaceInterpolationSchemeType>
		class addIstreamConstructorToTable
		{
		public:
			static tmp<multivariateSurfaceInterpolationScheme> New(const fvMesh& mesh, const fieldTable& fields,
			                                                       const surfaceScalarField& faceFlux, Istream& is)
			{
				return tmp<multivariateSurfaceInterpolationScheme>(
					new multivariateSurfaceInterpolationSchemeType(mesh, fields, faceFlux, is));
			}

			addIstreamConstructorToTable(const word& lookup = multivariateSurfaceInterpolationSchemeType::typeName)
			{
				constructIstreamConstructorTables();
				if (!IstreamConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"multivariateSurfaceInterpolationScheme" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
		};

		template <class multivariateSurfaceInterpolationSchemeType>
		class addRemovableIstreamConstructorToTable
		{
			const word& lookup_;
		public:
			static tmp<multivariateSurfaceInterpolationScheme> New(const fvMesh& mesh, const fieldTable& fields,
			                                                       const surfaceScalarField& faceFlux, Istream& is)
			{
				return tmp<multivariateSurfaceInterpolationScheme>(
					new multivariateSurfaceInterpolationSchemeType(mesh, fields, faceFlux, is));
			}

			addRemovableIstreamConstructorToTable(
				const word& lookup = multivariateSurfaceInterpolationSchemeType::typeName) : lookup_(lookup)
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

			//- Construct for interpolating given field
		multivariateSurfaceInterpolationScheme
		(
			const fvMesh& mesh,
			const fieldTable& fields,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);

		//- Disallow default bitwise copy construction
		multivariateSurfaceInterpolationScheme
		(
			const multivariateSurfaceInterpolationScheme&
		);


		// Selectors

			//- Return a pointer to a new gradScheme created on freestore
		static tmp<multivariateSurfaceInterpolationScheme<Type>> New
		(
			const fvMesh& mesh,
			const fieldTable& fields,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);


		//- Destructor
		virtual ~multivariateSurfaceInterpolationScheme();


		// Member Functions

			//- Return mesh reference
		const fvMesh& mesh() const
		{
			return mesh_;
		}

		//- Return fields to be interpolated
		const fieldTable& fields() const
		{
			return fields_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const multivariateSurfaceInterpolationScheme&) = delete;

		//- surfaceInterpolationScheme sub-class returned by operator(field)
		//  which is used as the interpolation scheme for the field
		class fieldScheme
			:
			public surfaceInterpolationScheme<Type>
		{

		public:

			// Constructors

			fieldScheme
			(
				const GeometricField<Type, fvPatchField, volMesh>& field
			)
				:
				surfaceInterpolationScheme<Type>(field.mesh())
			{}


			// Member Functions

				//- Return the interpolation weighting factors
			virtual tmp<surfaceScalarField> weights
			(
				const GeometricField<Type, fvPatchField, volMesh>& field
			) const = 0;
		};

		virtual tmp<surfaceInterpolationScheme<Type>> operator()
			(
				const GeometricField<Type, fvPatchField, volMesh>& field
				) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeMultivariateSurfaceInterpolationTypeScheme(SS, Type)               \
                                                                               \
defineNamedTemplateTypeNameAndDebug(SS<Type>, 0);                              \
                                                                               \
multivariateSurfaceInterpolationScheme<Type>::                                 \
addIstreamConstructorToTable<SS<Type>>                                         \
    add##SS##Type##ConstructorToTable_;


#define makeMultivariateSurfaceInterpolationScheme(SS)                         \
                                                                               \
makeMultivariateSurfaceInterpolationTypeScheme(SS, scalar)                     \
makeMultivariateSurfaceInterpolationTypeScheme(SS, vector)                     \
makeMultivariateSurfaceInterpolationTypeScheme(SS, sphericalTensor)            \
makeMultivariateSurfaceInterpolationTypeScheme(SS, symmTensor)                 \
makeMultivariateSurfaceInterpolationTypeScheme(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <multivariateSurfaceInterpolationSchemeI.hxx>

//#ifdef NoRepository
//#include <multivariateSurfaceInterpolationScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_multivariateSurfaceInterpolationScheme_Header
