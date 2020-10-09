#pragma once
#ifndef _residuals_Header
#define _residuals_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::residuals

Description
	Writes out the initial residual for specified fields.

	Example of function object specification:
	\verbatim
	residuals
	{
		type            residuals;
		writeControl   timeStep;
		writeInterval  1;
		fields
		(
			U
			p
		);
	}
	\endverbatim

	Output data is written to the dir postProcessing/residuals/\<timeDir\>/
	For vector/tensor fields, e.g. U, where an equation is solved for each
	component, the largest residual of each component is written out.

See also
	tnbLib::functionObject
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles
	tnbLib::functionObjects::timeControl

SourceFiles
	residuals.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <logFiles.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class residuals Declaration
		\*---------------------------------------------------------------------------*/

		class residuals
			:
			public fvMeshFunctionObject,
			public logFiles
		{
		protected:

			// Protected data

				//- Fields to write residuals
			wordList fieldSet_;


			// Protected Member Functions

				//- Output field header information
			template<class Type>
			void writeFileHeader(const word& fieldName);

			//- Output file header information
			virtual void writeFileHeader(const label i);

			//- Calculate the field min/max
			template<class Type>
			void writeResidual(const word& fieldName);


		public:

			//- Runtime type information
			TypeName("residuals");


			// Constructors

				//- Construct from Time and dictionary
			residuals
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			residuals(const residuals&) = delete;


			//- Destructor
			virtual ~residuals();


			// Member Functions

				//- Read the controls
			virtual bool read(const dictionary&);

			//- Execute, currently does nothing
			virtual bool execute();

			//- Write the residuals
			virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const residuals&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <residualsTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_residuals_Header
