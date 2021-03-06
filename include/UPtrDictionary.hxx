#pragma once
#ifndef _UPtrDictionary_Header
#define _UPtrDictionary_Header

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
	tnbLib::UPtrDictionary

Description
	Template dictionary class which does not manages the storage
	associated with it.

	It is derived from DictionaryBase instantiated on a non-memory managed
	form of intrusive doubly-linked list of \<T\>.

SourceFiles
	UPtrDictionary.C

\*---------------------------------------------------------------------------*/

#include <DictionaryBase.hxx>
#include <DLList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class UPtrDictionary Declaration
	\*---------------------------------------------------------------------------*/

	template<class T>
	class UPtrDictionary
		:
		public DictionaryBase<DLList<T*>, T>
	{

	public:

		// Constructors

			//- Construct given initial table size
		UPtrDictionary(const label size = 128);

		//- Copy construct
		UPtrDictionary(const UPtrDictionary&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <UPtrDictionaryI.hxx>

//#ifdef NoRepository
//#include <UPtrDictionary.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_UPtrDictionary_Header
