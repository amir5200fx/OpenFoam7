#pragma once
#ifndef _surfaceInterpolationScheme_Header
#define _surfaceInterpolationScheme_Header

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
	tnbLib::surfaceInterpolationScheme

Description
	Abstract base class for surface interpolation schemes.

SourceFiles
	surfaceInterpolationScheme.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

#include <surfaceFields.hxx>  // added by amir

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamSurfaceInterpolationScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamSurfaceInterpolationScheme_EXPORT_DEFINE
#define FoamSurfaceInterpolationScheme_EXPORT __declspec(dllexport)
#else
#define FoamSurfaceInterpolationScheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
					 Class surfaceInterpolationScheme Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class surfaceInterpolationScheme
		:
		public tmp<surfaceInterpolationScheme<Type>>::refCount
	{
		// Private Data

			//- Hold reference to mesh
		const fvMesh& mesh_;


	public:

		//- Runtime type information
		/*TypeName("surfaceInterpolationScheme");*/
		static const char* typeName_() { return "surfaceInterpolationScheme"; }
		static FoamSurfaceInterpolationScheme_EXPORT const ::tnbLib::word typeName;
		static FoamSurfaceInterpolationScheme_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			tmp,
			surfaceInterpolationScheme,
			Mesh,
			(
				const fvMesh& mesh,
				Istream& schemeData
				),
				(mesh, schemeData)
		);

		declareRunTimeSelectionTable
		(
			tmp,
			surfaceInterpolationScheme,
			MeshFlux,
			(
				const fvMesh& mesh,
				const surfaceScalarField& faceFlux,
				Istream& schemeData
				),
				(mesh, faceFlux, schemeData)
		);*/

		typedef tmp<surfaceInterpolationScheme> (*MeshConstructorPtr)(const fvMesh& mesh, Istream& schemeData);
		typedef HashTable<MeshConstructorPtr, word, string::hash> MeshConstructorTable;
		static FoamSurfaceInterpolationScheme_EXPORT MeshConstructorTable* MeshConstructorTablePtr_;
		static FoamSurfaceInterpolationScheme_EXPORT void constructMeshConstructorTables();
		static FoamSurfaceInterpolationScheme_EXPORT void destroyMeshConstructorTables();

		template <class surfaceInterpolationSchemeType>
		class addMeshConstructorToTable
		{
		public:
			static tmp<surfaceInterpolationScheme> New(const fvMesh& mesh, Istream& schemeData)
			{
				return tmp<surfaceInterpolationScheme>(new surfaceInterpolationSchemeType(mesh, schemeData));
			}

			addMeshConstructorToTable(const word& lookup = surfaceInterpolationSchemeType::typeName)
			{
				constructMeshConstructorTables();
				if (!MeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "surfaceInterpolationScheme" << std
						::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addMeshConstructorToTable() { destroyMeshConstructorTables(); }
		};

		template <class surfaceInterpolationSchemeType>
		class addRemovableMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static tmp<surfaceInterpolationScheme> New(const fvMesh& mesh, Istream& schemeData)
			{
				return tmp<surfaceInterpolationScheme>(new surfaceInterpolationSchemeType(mesh, schemeData));
			}

			addRemovableMeshConstructorToTable(const word& lookup = surfaceInterpolationSchemeType::typeName) : lookup_(lookup)
			{
				constructMeshConstructorTables();
				MeshConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableMeshConstructorToTable() { if (MeshConstructorTablePtr_) { MeshConstructorTablePtr_->erase(lookup_); } }
		};;

		typedef tmp<surfaceInterpolationScheme> (*MeshFluxConstructorPtr)(const fvMesh& mesh,
		                                                                  const surfaceScalarField& faceFlux,
		                                                                  Istream& schemeData);
		typedef HashTable<MeshFluxConstructorPtr, word, string::hash> MeshFluxConstructorTable;
		static FoamSurfaceInterpolationScheme_EXPORT MeshFluxConstructorTable* MeshFluxConstructorTablePtr_;
		static FoamSurfaceInterpolationScheme_EXPORT void constructMeshFluxConstructorTables();
		static FoamSurfaceInterpolationScheme_EXPORT void destroyMeshFluxConstructorTables();

		template <class surfaceInterpolationSchemeType>
		class addMeshFluxConstructorToTable
		{
		public:
			static tmp<surfaceInterpolationScheme> New(const fvMesh& mesh, const surfaceScalarField& faceFlux,
			                                           Istream& schemeData)
			{
				return tmp<surfaceInterpolationScheme>(new surfaceInterpolationSchemeType(mesh, faceFlux, schemeData));
			}

			addMeshFluxConstructorToTable(const word& lookup = surfaceInterpolationSchemeType::typeName)
			{
				constructMeshFluxConstructorTables();
				if (!MeshFluxConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "surfaceInterpolationScheme" << std
						::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addMeshFluxConstructorToTable() { destroyMeshFluxConstructorTables(); }
		};

		template <class surfaceInterpolationSchemeType>
		class addRemovableMeshFluxConstructorToTable
		{
			const word& lookup_;
		public:
			static tmp<surfaceInterpolationScheme> New(const fvMesh& mesh, const surfaceScalarField& faceFlux,
			                                           Istream& schemeData)
			{
				return tmp<surfaceInterpolationScheme>(new surfaceInterpolationSchemeType(mesh, faceFlux, schemeData));
			}

			addRemovableMeshFluxConstructorToTable(const word& lookup = surfaceInterpolationSchemeType::typeName) : lookup_(
				lookup)
			{
				constructMeshFluxConstructorTables();
				MeshFluxConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableMeshFluxConstructorToTable()
			{
				if (MeshFluxConstructorTablePtr_) { MeshFluxConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from mesh
		surfaceInterpolationScheme(const fvMesh& mesh)
			:
			mesh_(mesh)
		{}

		//- Disallow default bitwise copy construction
		surfaceInterpolationScheme(const surfaceInterpolationScheme&);



		// Selectors

			//- Return new tmp interpolation scheme
		static tmp<surfaceInterpolationScheme<Type>> New
		(
			const fvMesh& mesh,
			Istream& schemeData
		);

		//- Return new tmp interpolation scheme
		static tmp<surfaceInterpolationScheme<Type>> New
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);


		//- Destructor
		virtual ~surfaceInterpolationScheme();


		// Member Functions

			//- Return mesh reference
		const fvMesh& mesh() const
		{
			return mesh_;
		}


		//- Return the face-interpolate of the given cell field
		//  with the given owner and neighbour weigting factors
		static tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			interpolate
			(
				const GeometricField<Type, fvPatchField, volMesh>&,
				const tmp<surfaceScalarField>&,
				const tmp<surfaceScalarField>&
			);

		//- Return the face-interpolate of the given cell field
		//  with the given weighting factors dotted with given field Sf
		template<class SFType>
		static tmp
			<
			GeometricField
			<
			typename innerProduct<typename SFType::value_type, Type>::type,
			fvsPatchField,
			surfaceMesh
			>
			>
			dotInterpolate
			(
				const SFType& Sf,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const tmp<surfaceScalarField>& tlambdas
			);

		//- Return the face-interpolate of the given cell field
		//  with the given weighting factors
		static tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			interpolate
			(
				const GeometricField<Type, fvPatchField, volMesh>&,
				const tmp<surfaceScalarField>&
			);

		//- Return the interpolation weighting factors for the given field
		virtual tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const = 0;

		//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return false;
		}

		//- Return the explicit correction to the face-interpolate
		//  for the given field
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			correction(const GeometricField<Type, fvPatchField, volMesh>&) const
		{
			return tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				(
					nullptr
					);
		}

		//- Return the face-interpolate of the given cell field
		//  with explicit correction dotted with given field Sf
		virtual
			tmp
			<
			GeometricField
			<
			typename innerProduct<vector, Type>::type,
			fvsPatchField,
			surfaceMesh
			>
			>
			dotInterpolate
			(
				const surfaceVectorField& Sf,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const;

		//- Return the face-interpolate of the given tmp cell field
		//  with explicit correction dotted with given field Sf
		tmp
			<
			GeometricField
			<
			typename innerProduct<vector, Type>::type,
			fvsPatchField,
			surfaceMesh
			>
			>
			dotInterpolate
			(
				const surfaceVectorField& Sf,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>&
			) const;

		//- Return the face-interpolate of the given cell field
		//  with explicit correction
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			interpolate(const GeometricField<Type, fvPatchField, volMesh>&) const;

		//- Return the face-interpolate of the given tmp cell field
		//  with explicit correction
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			interpolate
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh>>&
			) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const surfaceInterpolationScheme&) = delete;
	};


	template<>
	tmp
		<
		GeometricField
		<
		typename innerProduct<vector, scalar>::type,
		fvsPatchField,
		surfaceMesh
		>
		>
		surfaceInterpolationScheme<scalar>::dotInterpolate
		(
			const surfaceVectorField& Sf,
			const GeometricField<scalar, fvPatchField, volMesh>&
		) const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeSurfaceInterpolationTypeScheme(SS, Type)                           \
                                                                               \
defineNamedTemplateTypeNameAndDebug(SS<Type>, 0);                              \
                                                                               \
surfaceInterpolationScheme<Type>::addMeshConstructorToTable<SS<Type>>          \
    add##SS##Type##MeshConstructorToTable_;                                    \
                                                                               \
surfaceInterpolationScheme<Type>::addMeshFluxConstructorToTable<SS<Type>>      \
    add##SS##Type##MeshFluxConstructorToTable_;

#define makeSurfaceInterpolationScheme(SS)                                     \
                                                                               \
makeSurfaceInterpolationTypeScheme(SS, scalar)                                 \
makeSurfaceInterpolationTypeScheme(SS, vector)                                 \
makeSurfaceInterpolationTypeScheme(SS, sphericalTensor)                        \
makeSurfaceInterpolationTypeScheme(SS, symmTensor)                             \
makeSurfaceInterpolationTypeScheme(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <surfaceInterpolationSchemeI.hxx>

//#ifdef NoRepository
//#include <surfaceInterpolationScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceInterpolationScheme_Header
