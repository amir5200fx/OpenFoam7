#pragma once
#ifndef _specieReactionRates_Header
#define _specieReactionRates_Header

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
	tnbLib::functionObjects::specieReactionRates

Description
	Writes the domain averaged reaction rates for each specie for each reaction
	into the file \<timeDir\>/specieReactionRates.dat

See also
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::volRegion
	tnbLib::functionObjects::logFiles

SourceFiles
	specieReactionRates.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <volRegion.hxx>
#include <logFiles.hxx>

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamspecieReactionRates_EXPORT __declspec(dllexport)
#else
#ifdef FoamspecieReactionRates_EXPORT_DEFINE
#define FoamspecieReactionRates_EXPORT __declspec(dllexport)
#else
#define FoamspecieReactionRates_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								  Class specieReactionRates Declaration
		\*---------------------------------------------------------------------------*/

		template<class ChemistryModelType>
		class specieReactionRates
			:
			public fvMeshFunctionObject,
			public volRegion,
			public logFiles
		{
			// Private Member Data

			const ChemistryModelType& chemistryModel_;


			// Private Member Functions

				//- File header information
			virtual void writeFileHeader(const label i);


		public:

			//- Runtime type information
			//TypeName("specieReactionRates");
			static const char* typeName_() { return "specieReactionRates"; }
			static FoamspecieReactionRates_EXPORT const ::tnbLib::word typeName;
			static FoamspecieReactionRates_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			specieReactionRates
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			specieReactionRates(const specieReactionRates&) = delete;


			//- Destructor
			virtual ~specieReactionRates();


			// Member Functions

				//- Read the specieReactionRates data
			virtual bool read(const dictionary&);

			//- Do nothing
			virtual bool execute();

			//- Write the specie reaction rates
			virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const specieReactionRates&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <specieReactionRatesI.hxx>

#endif // !_specieReactionRates_Header
