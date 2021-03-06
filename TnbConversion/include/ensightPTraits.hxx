#pragma once
#ifndef _ensightPTraits_Header
#define _ensightPTraits_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::ensightPTraits

Description
	Conversion of OpenFOAM pTraits into the Ensight equivalent

\*---------------------------------------------------------------------------*/

#include <pTraits.hxx>
#include <fieldTypes.hxx>

#ifdef FoamConversion_EXPORT_DEFINE
#define FoamensightPTraits_EXPORT __declspec(dllexport)
#else
#ifdef FoamensightPTraits_EXPORT_DEFINE
#define FoamensightPTraits_EXPORT __declspec(dllexport)
#else
#define FoamensightPTraits_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class ensightPTraits Declaration
	\*---------------------------------------------------------------------------*/

	template<class PrimitiveType>
	class ensightPTraits
	{
	public:

		// Static Data Members

		static FoamensightPTraits_EXPORT const char* const typeName;

	};


	template<>
	class ensightPTraits<scalar>
	{
	public:

		static FoamConversion_EXPORT const char* const typeName;
	};

	template<>
	class ensightPTraits<vector>
	{
	public:

		static FoamConversion_EXPORT const char* const typeName;
	};

	template<>
	class ensightPTraits<sphericalTensor>
	{
	public:

		static FoamConversion_EXPORT const char* const typeName;
	};

	template<>
	class ensightPTraits<symmTensor>
	{
	public:

		static FoamConversion_EXPORT const char* const typeName;
	};

	template<>
	class ensightPTraits<tensor>
	{
	public:

		static FoamConversion_EXPORT const char* const typeName;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ensightPTraits_Header
