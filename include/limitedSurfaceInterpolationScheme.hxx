#pragma once
#ifndef _limitedSurfaceInterpolationScheme_Header
#define _limitedSurfaceInterpolationScheme_Header

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
	tnbLib::limitedSurfaceInterpolationScheme

Description
	Abstract base class for limited surface interpolation schemes.

SourceFiles
	limitedSurfaceInterpolationScheme.C

\*---------------------------------------------------------------------------*/

#include <surfaceInterpolationScheme.hxx>

#include <fvMesh.hxx>  // added by amir

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamLimitedSurfaceInterpolationScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamLimitedSurfaceInterpolationScheme_EXPORT_DEFINE
#define FoamLimitedSurfaceInterpolationScheme_EXPORT __declspec(dllexport)
#else
#define FoamLimitedSurfaceInterpolationScheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class limitedSurfaceInterpolationScheme Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class limitedSurfaceInterpolationScheme
		:
		public surfaceInterpolationScheme<Type>
	{

	protected:

		// Protected data

		const surfaceScalarField& faceFlux_;


	public:

		//- Runtime type information
		/*TypeName("limitedSurfaceInterpolationScheme");*/
		static const char* typeName_() { return "limitedSurfaceInterpolationScheme"; }
		static FoamLimitedSurfaceInterpolationScheme_EXPORT const ::tnbLib::word typeName;
		static FoamLimitedSurfaceInterpolationScheme_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			tmp,
			limitedSurfaceInterpolationScheme,
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
			limitedSurfaceInterpolationScheme,
			MeshFlux,
			(
				const fvMesh& mesh,
				const surfaceScalarField& faceFlux,
				Istream& schemeData
				),
				(mesh, faceFlux, schemeData)
		);*/

		typedef tmp<limitedSurfaceInterpolationScheme> (*MeshConstructorPtr)(const fvMesh& mesh, Istream& schemeData);
		typedef HashTable<MeshConstructorPtr, word, string::hash> MeshConstructorTable;
		static FoamLimitedSurfaceInterpolationScheme_EXPORT MeshConstructorTable* MeshConstructorTablePtr_;
		static FoamLimitedSurfaceInterpolationScheme_EXPORT void constructMeshConstructorTables();
		static FoamLimitedSurfaceInterpolationScheme_EXPORT void destroyMeshConstructorTables();

		template <class limitedSurfaceInterpolationSchemeType>
		class addMeshConstructorToTable
		{
		public:
			static tmp<limitedSurfaceInterpolationScheme> New(const fvMesh& mesh, Istream& schemeData)
			{
				return tmp<limitedSurfaceInterpolationScheme>(new limitedSurfaceInterpolationSchemeType(mesh, schemeData));
			}

			addMeshConstructorToTable(const word& lookup = limitedSurfaceInterpolationSchemeType::typeName)
			{
				constructMeshConstructorTables();
				if (!MeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "limitedSurfaceInterpolationScheme"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addMeshConstructorToTable() { destroyMeshConstructorTables(); }
		};

		template <class limitedSurfaceInterpolationSchemeType>
		class addRemovableMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static tmp<limitedSurfaceInterpolationScheme> New(const fvMesh& mesh, Istream& schemeData)
			{
				return tmp<limitedSurfaceInterpolationScheme>(new limitedSurfaceInterpolationSchemeType(mesh, schemeData));
			}

			addRemovableMeshConstructorToTable(const word& lookup = limitedSurfaceInterpolationSchemeType::typeName) : lookup_(
				lookup)
			{
				constructMeshConstructorTables();
				MeshConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableMeshConstructorToTable() { if (MeshConstructorTablePtr_) { MeshConstructorTablePtr_->erase(lookup_); } }
		};;

		typedef tmp<limitedSurfaceInterpolationScheme> (*MeshFluxConstructorPtr)(
			const fvMesh& mesh, const surfaceScalarField& faceFlux, Istream& schemeData);
		typedef HashTable<MeshFluxConstructorPtr, word, string::hash> MeshFluxConstructorTable;
		static FoamLimitedSurfaceInterpolationScheme_EXPORT MeshFluxConstructorTable* MeshFluxConstructorTablePtr_;
		static FoamLimitedSurfaceInterpolationScheme_EXPORT void constructMeshFluxConstructorTables();
		static FoamLimitedSurfaceInterpolationScheme_EXPORT void destroyMeshFluxConstructorTables();

		template <class limitedSurfaceInterpolationSchemeType>
		class addMeshFluxConstructorToTable
		{
		public:
			static tmp<limitedSurfaceInterpolationScheme>
			New(const fvMesh& mesh, const surfaceScalarField& faceFlux, Istream& schemeData)
			{
				return tmp<limitedSurfaceInterpolationScheme
				>(new limitedSurfaceInterpolationSchemeType(mesh, faceFlux, schemeData));
			}

			addMeshFluxConstructorToTable(const word& lookup = limitedSurfaceInterpolationSchemeType::typeName)
			{
				constructMeshFluxConstructorTables();
				if (!MeshFluxConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "limitedSurfaceInterpolationScheme"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addMeshFluxConstructorToTable() { destroyMeshFluxConstructorTables(); }
		};

		template <class limitedSurfaceInterpolationSchemeType>
		class addRemovableMeshFluxConstructorToTable
		{
			const word& lookup_;
		public:
			static tmp<limitedSurfaceInterpolationScheme>
			New(const fvMesh& mesh, const surfaceScalarField& faceFlux, Istream& schemeData)
			{
				return tmp<limitedSurfaceInterpolationScheme
				>(new limitedSurfaceInterpolationSchemeType(mesh, faceFlux, schemeData));
			}

			addRemovableMeshFluxConstructorToTable(
				const word& lookup = limitedSurfaceInterpolationSchemeType::typeName) : lookup_(lookup)
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

			//- Construct from mesh and faceFlux
		limitedSurfaceInterpolationScheme
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			faceFlux_(faceFlux)
		{}

		//- Construct from mesh and Istream.
		//  The name of the flux field is read from the Istream and looked-up
		//  from the mesh objectRegistry
		limitedSurfaceInterpolationScheme
		(
			const fvMesh& mesh,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			faceFlux_
			(
				mesh.lookupObject<surfaceScalarField>
				(
					word(is)
					)
			)
		{}

		//- Disallow default bitwise copy construction
		limitedSurfaceInterpolationScheme
		(
			const limitedSurfaceInterpolationScheme&
		);


		// Selectors

			//- Return new tmp interpolation scheme
		static tmp<limitedSurfaceInterpolationScheme<Type>> New
		(
			const fvMesh& mesh,
			Istream& schemeData
		);

		//- Return new tmp interpolation scheme
		static tmp<limitedSurfaceInterpolationScheme<Type>> New
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);


		//- Destructor
		virtual ~limitedSurfaceInterpolationScheme();


		// Member Functions

			//- Return the interpolation weighting factors
		virtual tmp<surfaceScalarField> limiter
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const = 0;

		//- Return the interpolation weighting factors for the given field,
		//  by limiting the given weights with the given limiter
		tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			const surfaceScalarField& CDweights,
			tmp<surfaceScalarField> tLimiter
		) const;

		//- Return the interpolation weighting factors for the given field
		virtual tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const;

		//- Return the interpolation weighting factors
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			flux
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const limitedSurfaceInterpolationScheme&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makelimitedSurfaceInterpolationTypeScheme(SS, Type)                    \
                                                                               \
defineNamedTemplateTypeNameAndDebug(SS<Type>, 0);                              \
                                                                               \
surfaceInterpolationScheme<Type>::addMeshConstructorToTable<SS<Type>>          \
    add##SS##Type##MeshConstructorToTable_;                                    \
                                                                               \
surfaceInterpolationScheme<Type>::addMeshFluxConstructorToTable<SS<Type>>      \
    add##SS##Type##MeshFluxConstructorToTable_;                                \
                                                                               \
limitedSurfaceInterpolationScheme<Type>::addMeshConstructorToTable<SS<Type>>   \
    add##SS##Type##MeshConstructorToLimitedTable_;                             \
                                                                               \
limitedSurfaceInterpolationScheme<Type>::                                      \
    addMeshFluxConstructorToTable<SS<Type>>                                    \
    add##SS##Type##MeshFluxConstructorToLimitedTable_;

#define makelimitedSurfaceInterpolationScheme(SS)                              \
                                                                               \
makelimitedSurfaceInterpolationTypeScheme(SS, scalar)                          \
makelimitedSurfaceInterpolationTypeScheme(SS, vector)                          \
makelimitedSurfaceInterpolationTypeScheme(SS, sphericalTensor)                 \
makelimitedSurfaceInterpolationTypeScheme(SS, symmTensor)                      \
makelimitedSurfaceInterpolationTypeScheme(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <limitedSurfaceInterpolationSchemeI.hxx>

//#ifdef NoRepository
//#include <limitedSurfaceInterpolationScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_limitedSurfaceInterpolationScheme_Header
