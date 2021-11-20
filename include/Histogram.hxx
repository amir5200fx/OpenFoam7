#pragma once
#ifndef _histogram_Header
#define _histogram_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::histogram

Description
	Write the volume-weighted histogram of a volScalarField.

	Example:
	\verbatim
	histogram1
	{
		type            histogram;

		libs            ("libfieldFunctionObjects.so");

		field           p;
		nBins           100;
		min             -5;
		max             5;
		setFormat       gnuplot;
	}
	\endverbatim

Usage
	\table
		Property     | Description             | Required    | Default value
		type         | type name: histogram    | yes         |
		field        | Field to analyse        | yes         |
		nBins        | Number of bins for the histogram | yes|
		max          | Maximum value sampled   | yes         |
		min          | minimum value sampled   | no          | 0
		setFormat    | Output format           | yes         |
	\endtable

See also
	tnbLib::functionObject
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::writeFile

SourceFiles
	histogram.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <writeFile.hxx>
#include <writer.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								 Class histogram Declaration
		\*---------------------------------------------------------------------------*/

		class histogram
			:
			public fvMeshFunctionObject
		{
			// Private Data

			writeFile file_;

			//- Name of field
			word fieldName_;

			//- Maximum value
			scalar max_;

			//- Minimum value
			scalar min_;

			//- Number of bins
			label nBins_;

			//- Output formatter to write
			autoPtr<writer<scalar>> formatterPtr_;


			// Private Member Functions

			FoamFunctionObjects_EXPORT void writeGraph
			(
				const coordSet& coords,
				const word& valueName,
				const scalarField& values
			) const;


		public:

			//- Runtime type information
			//TypeName("histogram");
			static const char* typeName_() { return "histogram"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT histogram
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT histogram(const histogram&) = delete;


			// Destructor
			FoamFunctionObjects_EXPORT virtual ~histogram();


			// Member Functions

				//- Read the histogram data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Execute, currently does nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Calculate the histogram and write.
			//  postProcess overrides the usual writeControl behaviour and
			//  forces writing always (used in post-processing mode)
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const histogram&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_histogram_Header
