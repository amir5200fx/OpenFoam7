#pragma once
#ifndef _linearNormal_Header
#define _linearNormal_Header

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
	tnbLib::extrudeModels::linearNormal

Description
	Extrudes by transforming points normal to the surface by a given distance.

\*---------------------------------------------------------------------------*/

#include <point.hxx>
#include <extrudeModel.hxx>
#include <scalarList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		/*---------------------------------------------------------------------------*\
							Class linearNormal Declaration
		\*---------------------------------------------------------------------------*/

		class linearNormal
			:
			public extrudeModel
		{
			// Private Data

				//- Layer thickness
			scalar thickness_;

			//- First cell thickness
			scalar firstCellThickness_;

			//- Layer cell distribution
			scalarList layerPoints_;



		public:

			//- Runtime type information
			//TypeName("linearNormal");
			static const char* typeName_() { return "linearNormal"; }
			static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
			static FoamFvMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

				//- Construct from dictionary
			FoamFvMesh_EXPORT linearNormal(const dictionary& dict);


			//- Destructor
			FoamFvMesh_EXPORT virtual ~linearNormal();


			// Member Operators

			FoamFvMesh_EXPORT point operator()
				(
					const point& surfacePoint,
					const vector& surfaceNormal,
					const label layer
					) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace extrudeModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linearNormal_Header
