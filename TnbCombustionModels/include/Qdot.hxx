#pragma once
#ifndef _Qdot_Header
#define _Qdot_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::Qdot

Description
	Calculates and outputs the heat release rate for the current combustion
	model.

SourceFiles
	Qdot.C

\*---------------------------------------------------------------------------*/

#include <CombustionModels_Module.hxx>
#include <fvMeshFunctionObject.hxx>
#include <writeLocalObjects.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								  Class Qdot Declaration
		\*---------------------------------------------------------------------------*/

		class Qdot
			:
			public fvMeshFunctionObject,
			public writeLocalObjects
		{
		private:

			// Private Data

				//- The name of the phase
			word phaseName_;


		public:

			//- Runtime type information
			//TypeName("Qdot");
			static const char* typeName_() { return "Qdot"; }
			static FoamCombustionModels_EXPORT const ::tnbLib::word typeName;
			static FoamCombustionModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamCombustionModels_EXPORT Qdot
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			FoamCombustionModels_EXPORT virtual ~Qdot();


			// Member Functions

				//- Read the data
			FoamCombustionModels_EXPORT virtual bool read(const dictionary&);

			//- Calculate the Qdot field
			FoamCombustionModels_EXPORT virtual bool execute();

			//- Do nothing
			FoamCombustionModels_EXPORT virtual bool write();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Qdot_Header
