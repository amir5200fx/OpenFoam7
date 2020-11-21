#pragma once
#ifndef _blendedSchemeBase_Header
#define _blendedSchemeBase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::blendedSchemeBase

Description
	Base class for blended schemes to provide access to the blending factor
	surface field

\*---------------------------------------------------------------------------*/

#include <className.hxx>
#include <tmp.hxx>
#include <surfaceFieldsFwd.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*TemplateName(blendedSchemeBase);*/
	class blendedSchemeBaseName
	{
	public:
		blendedSchemeBaseName()
		{
		}

		static const char* typeName_() { return "blendedSchemeBase"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
	};

	/*---------------------------------------------------------------------------*\
						  Class blendedSchemeBase Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class blendedSchemeBase
		:
		public blendedSchemeBaseName
	{

	public:

		//- Constructor
		blendedSchemeBase()
		{}

		//- Destructor
		virtual ~blendedSchemeBase()
		{}


		// Member Functions

			//- Return the face-based blending factor
		virtual tmp<surfaceScalarField> blendingFactor
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_blendedSchemeBase_Header
