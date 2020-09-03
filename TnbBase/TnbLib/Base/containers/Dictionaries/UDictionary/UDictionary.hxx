#pragma once
#ifndef _UDictionary_Header
#define _UDictionary_Header

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
	tnbLib::UDictionary

Description
	Template dictionary class which does not manages the storage
	associated with it.

	It is derived from DictionaryBase instantiated on a non-memory managed
	form of intrusive doubly-linked list of \<T\>.

SourceFiles
	UDictionary.C

\*---------------------------------------------------------------------------*/

#include <DictionaryBase.hxx>
#include <UIDLList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class UDictionary Declaration
	\*---------------------------------------------------------------------------*/

	template<class T>
	class UDictionary
		:
		public DictionaryBase<UIDLList<T>, T>
	{

	public:

		// Constructors

			//- Null constructor
		UDictionary();

		//- Copy construct
		UDictionary(const UDictionary&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <UDictionaryI.hxx>

//#ifdef NoRepository
//#include <UDictionary.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_UDictionary_Header
