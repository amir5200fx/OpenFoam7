#pragma once
#ifndef _linearRadial_Header
#define _linearRadial_Header

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
	tnbLib::extrudeModels::linearRadial

Description

\*---------------------------------------------------------------------------*/

#include <extrudeModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace extrudeModels
	{

		/*---------------------------------------------------------------------------*\
								   Class linearRadial Declaration
		\*---------------------------------------------------------------------------*/

		class linearRadial
			:
			public extrudeModel
		{
			// Private Data

			scalar R_;
			scalar Rsurface_;


		public:

			//- Runtime type information
			//TypeName("linearRadial");
			static const char* typeName_() { return "linearRadial"; }
			static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
			static FoamFvMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

				//- Construct from dictionary
			FoamFvMesh_EXPORT linearRadial(const dictionary& dict);


			//- Destructor
			FoamFvMesh_EXPORT virtual ~linearRadial();


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

#endif // !_linearRadial_Header
