#pragma once
#ifndef _nullObject_Header
#define _nullObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
	tnbLib::NullObject

Description
	Singleton null-object class and instance

SourceFiles
	nullObjectI.H
	nullObject.C

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <includeModule.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class nullObject Declaration
	\*---------------------------------------------------------------------------*/

	class NullObject
	{
		//- Private constructor
		NullObject()
		{}

	public:

		//- The unique null object
		static FoamBase_EXPORT const NullObject nullObject;

		//- Disallow default bitwise copy construction
		NullObject(const NullObject&) = delete;

		//- Disallow default bitwise assignment
		void operator=(const NullObject&) = delete;
	};


	//- Pointer to the unique nullObject
	FoamBase_EXPORT extern const NullObject* nullObjectPtr;


	//- Return reference to the nullObject of type T
	template<class T>
	inline const T& NullObjectRef();

	//- Return pointer to the nullObject of type T
	template<class T>
	inline const T* NullObjectPtr();

	//- Return reference to the nullObject of type T
	template<class T>
	inline T&& NullObjectMove();


	//- Return true if t is a reference to the nullObject of type T
	template<class T>
	inline bool isNull(const T& t);

	//- Return true if t is not a reference to the nullObject of type T
	template<class T>
	inline bool notNull(const T& t);


	//- Return true if t is a pointer to the nullObject of type T
	template<class T>
	inline bool isNull(const T* t);

	//- Return true if t is not a pointer to the nullObject of type T
	template<class T>
	inline bool notNull(const T* t);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <nullObjectI.hxx>

#endif // !_nullObject_Header
