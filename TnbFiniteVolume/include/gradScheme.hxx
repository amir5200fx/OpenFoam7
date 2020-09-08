#pragma once
#ifndef _gradScheme_Header
#define _gradScheme_Header

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
	tnbLib::fv::gradScheme

Description
	Abstract base class for gradient schemes.

SourceFiles
	gradScheme.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								   Class gradScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class gradScheme
			:
			public tmp<gradScheme<Type>>::refCount
		{
			// Private Data

			const fvMesh& mesh_;


			// Private Member Functions

				//- Disallow default bitwise copy construction
			gradScheme(const gradScheme&);

			//- Disallow default bitwise assignment
			void operator=(const gradScheme&) = delete;


		public:

			//- Runtime type information
			virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			declareRunTimeSelectionTable
			(
				tmp,
				gradScheme,
				Istream,
				(const fvMesh& mesh, Istream& schemeData),
				(mesh, schemeData)
			);


			// Constructors

				//- Construct from mesh
			gradScheme(const fvMesh& mesh)
				:
				mesh_(mesh)
			{}


			// Selectors

				//- Return a pointer to a new gradScheme created on freestore
			static tmp<gradScheme<Type>> New
			(
				const fvMesh& mesh,
				Istream& schemeData
			);


			//- Destructor
			virtual ~gradScheme();


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return mesh_;
			}

			//- Calculate and return the grad of the given field.
			//  Used by grad either to recalculate the cached gradient when it is
			//  out of date with respect to the field or when it is not cached.
			virtual tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> calcGrad
				(
					const GeometricField<Type, fvPatchField, volMesh>&,
					const word& name
				) const = 0;

			//- Calculate and return the grad of the given field
			//  which may have been cached
			tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> grad
				(
					const GeometricField<Type, fvPatchField, volMesh>&,
					const word& name
				) const;

			//- Calculate and return the grad of the given field
			//  with the default name
			//  which may have been cached
			tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> grad
				(
					const GeometricField<Type, fvPatchField, volMesh>&
				) const;

			//- Calculate and return the grad of the given field
			//  with the default name
			//  which may have been cached
			tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> grad
				(
					const tmp<GeometricField<Type, fvPatchField, volMesh>>&
				) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeFvGradTypeScheme(SS, Type)                                         \
    defineNamedTemplateTypeNameAndDebug(tnbLib::fv::SS<tnbLib::Type>, 0);          \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            gradScheme<Type>::addIstreamConstructorToTable<SS<Type>>           \
                add##SS##Type##IstreamConstructorToTable_;                     \
        }                                                                      \
    }


#define makeFvGradScheme(SS)                                                   \
                                                                               \
makeFvGradTypeScheme(SS, scalar)                                               \
makeFvGradTypeScheme(SS, vector)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <gradSchemeI.hxx>

//#ifdef NoRepository
//#include <gradScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_gradScheme_Header
