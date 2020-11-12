#pragma once
#ifndef _sampledSets_Header
#define _sampledSets_Header

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
	tnbLib::sampledSets

Description
	Set of sets to sample.
	Call sampledSets.write() to sample&write files.

SourceFiles
	sampledSets.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <sampledSet.hxx>
#include <volFieldsFwd.hxx>
#include <meshSearch.hxx>
#include <interpolation.hxx>
#include <coordSet.hxx>
#include <writer.hxx>
#include <wordReList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class Time;
	class objectRegistry;
	class dictionary;
	class fvMesh;

	/*---------------------------------------------------------------------------*\
							 Class sampledSets Declaration
	\*---------------------------------------------------------------------------*/

	class sampledSets
		:
		public functionObject,
		public PtrList<sampledSet>
	{
		// Private classes

			//- Class used for grouping field types
		template<class Type>
		class fieldGroup
			:
			public DynamicList<word>
		{
		public:

			//- The set formatter
			autoPtr<writer<Type>> formatter;

			//- Construct null
			fieldGroup()
				:
				DynamicList<word>(0),
				formatter(nullptr)
			{}

			//- Construct for a particular format
			fieldGroup(const word& writeFormat)
				:
				DynamicList<word>(0),
				formatter(writer<Type>::New(writeFormat))
			{}

			//- Reset format and field list
			void clear()
			{
				DynamicList<word>::clear();
				formatter.clear();
			}

			//- Assign a new formatter
			void operator=(const word& writeFormat)
			{
				formatter = writer<Type>::New(writeFormat);
			}

		};


		//- Class used for sampling volFields
		template<class Type>
		class volFieldSampler
			:
			public List<Field<Type>>
		{
			//- Name of this collection of values
			const word name_;

		public:

			//- Construct interpolating field to the sampleSets
			volFieldSampler
			(
				const word& interpolationScheme,
				const GeometricField<Type, fvPatchField, volMesh>& field,
				const PtrList<sampledSet>&
			);

			//- Construct mapping field to the sampleSets
			volFieldSampler
			(
				const GeometricField<Type, fvPatchField, volMesh>& field,
				const PtrList<sampledSet>&
			);

			//- Construct from components
			volFieldSampler
			(
				const List<Field<Type>>& values,
				const word& name
			);

			//- Return the field name
			const word& name() const
			{
				return name_;
			}
		};


		// Static Data Members

			//- Output verbosity
		static FoamSampling_EXPORT bool verbose_;


		// Private Data

			//- Const reference to fvMesh
		const fvMesh& mesh_;

		//- Keep the dictionary to recreate sets for moving mesh cases
		dictionary dict_;

		//- Load fields from files (not from objectRegistry)
		bool loadFromFiles_;

		//- Output path
		fileName outputPath_;

		//- Mesh search engine
		meshSearch searchEngine_;


		// Read from dictonary

			//- Names of fields to sample
		wordReList fieldSelection_;

		//- Interpolation scheme to use
		word interpolationScheme_;

		//- Output format to use
		word writeFormat_;


		// Categorized scalar/vector/tensor fields

		fieldGroup<scalar> scalarFields_;
		fieldGroup<vector> vectorFields_;
		fieldGroup<sphericalTensor> sphericalTensorFields_;
		fieldGroup<symmTensor> symmTensorFields_;
		fieldGroup<tensor> tensorFields_;


		// Merging structures

		PtrList<coordSet> masterSampledSets_;
		labelListList indexSets_;


		// Private Member Functions

			//- Clear old field groups
		FoamSampling_EXPORT void clearFieldGroups();

		//- Append fieldName to the appropriate group
		FoamSampling_EXPORT label appendFieldGroup(const word& fieldName, const word& fieldType);

		//- Classify field types, returns the number of fields
		FoamSampling_EXPORT label classifyFields();

		//- Combine points from all processors. Sort by curveDist and produce
		//  index list. Valid result only on master processor.
		FoamSampling_EXPORT void combineSampledSets
		(
			PtrList<coordSet>& masterSampledSets,
			labelListList& indexSets
		);

		//- Combine values from all processors.
		//  Valid result only on master processor.
		template<class T>
		void combineSampledValues
		(
			const PtrList<volFieldSampler<T>>& sampledFields,
			const labelListList& indexSets,
			PtrList<volFieldSampler<T>>& masterFields
		);

		template<class Type>
		void writeSampleFile
		(
			const coordSet& masterSampleSet,
			const PtrList<volFieldSampler<Type>>& masterFields,
			const label setI,
			const fileName& timeDir,
			const writer<Type>& formatter
		);

		template<class Type>
		void sampleAndWrite(fieldGroup<Type>& fields);


	public:

		//- Runtime type information
		//TypeName("sets");
		static const char* typeName_() { return "sets"; }
		static FoamSampling_EXPORT const ::tnbLib::word typeName;
		static FoamSampling_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from Time and dictionary
		FoamSampling_EXPORT sampledSets
		(
			const word& name,
			const Time& time,
			const dictionary& dict
		);

		//- Construct for given objectRegistry and dictionary
		//  allow the possibility to load fields from files
		FoamSampling_EXPORT sampledSets
		(
			const word& name,
			const objectRegistry&,
			const dictionary&,
			const bool loadFromFiles = false
		);

		//- Disallow default bitwise copy construction
		FoamSampling_EXPORT sampledSets(const sampledSets&) = delete;


		//- Destructor
		FoamSampling_EXPORT virtual ~sampledSets();


		// Member Functions

			//- Set verbosity level
		FoamSampling_EXPORT void verbose(const bool verbosity = true);

		//- Read the sampledSets
		FoamSampling_EXPORT virtual bool read(const dictionary&);

		//- Execute, currently does nothing
		FoamSampling_EXPORT virtual bool execute();

		//- Sample and write
		FoamSampling_EXPORT virtual bool write();

		//- Correct for mesh changes
		FoamSampling_EXPORT void correct();

		//- Update for changes of mesh
		FoamSampling_EXPORT virtual void updateMesh(const mapPolyMesh&);

		//- Update for mesh point-motion
		FoamSampling_EXPORT virtual void movePoints(const polyMesh&);

		//- Update for changes of mesh due to readUpdate
		FoamSampling_EXPORT virtual void readUpdate(const polyMesh::readUpdateState state);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSampling_EXPORT void operator=(const sampledSets&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <sampledSetsI.hxx>

//#ifdef NoRepository
//#include <sampledSetsTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sampledSets_Header
