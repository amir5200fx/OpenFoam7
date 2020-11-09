#pragma once
#ifndef _rawSurfaceWriter_Header
#define _rawSurfaceWriter_Header

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
	tnbLib::rawSurfaceWriter

Description
	A surfaceWriter for raw output.

SourceFiles
	rawSurfaceWriter.C

\*---------------------------------------------------------------------------*/

#include <surfaceWriter.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class rawSurfaceWriter Declaration
	\*---------------------------------------------------------------------------*/

	class rawSurfaceWriter
		:
		public surfaceWriter
	{
		// Private Data

			//- Output compression, defaults to uncompressed
		IOstream::compressionType writeCompression_;


		// Private Member Functions

		static FoamConversion_EXPORT void writeLocation
		(
			Ostream&,
			const pointField&,
			const label pointi
		);

		static FoamConversion_EXPORT void writeLocation
		(
			Ostream&,
			const pointField&,
			const faceList&,
			const label facei
		);

		template<class Type>
		static FoamConversion_EXPORT void writeHeader
		(
			Ostream&,
			const word& fieldName,
			const Field<Type>&
		);

		template<class Type>
		static FoamConversion_EXPORT void writeData(Ostream&, const Type&);


		//- Templated write operation
		template<class Type>
		FoamConversion_EXPORT void writeTemplate
		(
			const fileName& outputDir,
			const fileName& surfaceName,
			const pointField& points,
			const faceList& faces,
			const word& fieldName,
			const Field<Type>& values,
			const bool isNodeValues,
			const bool verbose
		) const;


	public:

		//- Runtime type information
		//TypeName("raw");
		static const char* typeName_() { return "raw"; }
		static FoamConversion_EXPORT const ::tnbLib::word typeName;
		static FoamConversion_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		FoamConversion_EXPORT rawSurfaceWriter();

		//- Construct with some output options
		FoamConversion_EXPORT rawSurfaceWriter(const dictionary& options);


		//- Destructor
		FoamConversion_EXPORT virtual ~rawSurfaceWriter();


		// Member Functions

			//- Write single surface geometry to file.
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,
			const fileName& surfaceName,
			const pointField& points,
			const faceList& faces,
			const bool verbose = false
		) const;


		//- Write scalarField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<scalar>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const;

		//- Write vectorField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<vector>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const;

		//- Write sphericalTensorField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<sphericalTensor>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const;

		//- Write symmTensorField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<symmTensor>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const;

		//- Write tensorField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<tensor>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rawSurfaceWriter_Header
