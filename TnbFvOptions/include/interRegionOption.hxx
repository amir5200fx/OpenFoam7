#pragma once
#ifndef _interRegionOption_Header
#define _interRegionOption_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::fv::interRegionOption

Description
	Base class for inter-region exchange.

\*---------------------------------------------------------------------------*/

#include <fvOption.hxx>
#include <volFields.hxx>
#include <autoPtr.hxx>
#include <meshToMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						Class interRegionOption Declaration
		\*---------------------------------------------------------------------------*/

		class interRegionOption
			:
			public option
		{
		protected:

			// Protected data

				//- Master or slave region
			bool master_;

			//- Name of the neighbour region to map
			word nbrRegionName_;

			//- Mesh to mesh interpolation object
			autoPtr<meshToMesh> meshInterpPtr_;


			// Protected member functions

				//- Set the mesh to mesh interpolation object
			FoamFvOptions_EXPORT void setMapper();


		public:

			//- Runtime type information
			//TypeName("interRegionOption");
			static const char* typeName_() { return "interRegionOption"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamFvOptions_EXPORT interRegionOption
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			FoamFvOptions_EXPORT virtual ~interRegionOption();


			// Member Functions

				// Access

					//- Return const access to the neighbour region name
			inline const word& nbrRegionName() const;

			//- Return const access to the mapToMap pointer
			inline const meshToMesh& meshInterp() const;


			// IO

				//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <interRegionOptionI.hxx>

#endif // !_interRegionOption_Header
