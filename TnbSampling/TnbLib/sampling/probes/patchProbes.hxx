#pragma once
#ifndef _patchProbes_Header
#define _patchProbes_Header

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
	tnbLib::patchProbes

Description
	Set of locations to sample.at patches

	Call write() to sample and write files.

SourceFiles
	patchProbes.C

\*---------------------------------------------------------------------------*/


#include <probes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class objectRegistry;
	class dictionary;
	class fvMesh;
	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
							  Class patchProbes Declaration
	\*---------------------------------------------------------------------------*/

	class patchProbes
		:
		public probes
	{
		// Private Data

			//- Patch name
		word patchName_;


		// Private Member Functions

			//- Sample and write a particular volume field
		template<class Type>
		void sampleAndWrite
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		//- Sample and write a particular surface field
		template<class Type>
		void sampleAndWrite
		(
			const GeometricField<Type, fvsPatchField, surfaceMesh>&
		);


		//- Sample and write all the fields of the given type
		template<class Type>
		void sampleAndWrite(const fieldGroup<Type>&);


		//- Sample and write all the surface fields of the given type
		template<class Type>
		void sampleAndWriteSurfaceFields(const fieldGroup<Type>&);


		//- Sample a volume field at all locations
		template<class Type>
		tmp<Field<Type>> sample
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const;


		//- Sample a surface field at all locations
		template<class Type>
		tmp<Field<Type>> sample
		(
			const GeometricField<Type, fvsPatchField, surfaceMesh>&
		) const;


		//- Sample a single field on all sample locations
		template<class Type>
		tmp<Field<Type>> sample(const word& fieldName) const;


	public:

		//- Runtime type information
		//TypeName("patchProbes");
		static const char* typeName_() { return "patchProbes"; }
		static FoamSampling_EXPORT const ::tnbLib::word typeName;
		static FoamSampling_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from Time and dictionary
		FoamSampling_EXPORT patchProbes
		(
			const word& name,
			const Time& time,
			const dictionary& dict
		);

		//- Construct for given objectRegistry and dictionary.
		//  Allow the possibility to load fields from files
		FoamSampling_EXPORT patchProbes
		(
			const word& name,
			const objectRegistry&,
			const dictionary&,
			const bool loadFromFiles = false
		);

		//- Disallow default bitwise copy construction
		FoamSampling_EXPORT patchProbes(const patchProbes&) = delete;


		//- Destructor
		FoamSampling_EXPORT virtual ~patchProbes();


		// Member Functions

			//- Sample and write
		FoamSampling_EXPORT virtual bool write();

		//- Read
		FoamSampling_EXPORT virtual bool read(const dictionary&);

		//- Find elements containing patchProbes
		FoamSampling_EXPORT virtual void findElements(const fvMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSampling_EXPORT void operator=(const patchProbes&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <patchProbesI.hxx>

//#ifdef NoRepository
//#include <patchProbesTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_patchProbes_Header
