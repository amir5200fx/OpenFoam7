#pragma once
#ifndef _ListCompactIO_Header
#define _ListCompactIO_Header

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
	tnbLib::ListCompactIO

Description
	A List of objects of type \<T\> with input and output using
	a compact storage.  Behaves like List except when binary output in
	case it writes a CompactListList.

	Useful for lists of small sublists e.g. faceList, cellList.

SourceFiles
	ListCompactIO.C

\*---------------------------------------------------------------------------*/


#include <labelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Istream;
	class Ostream;

	// Forward declaration of friend functions and operators
	template<class T, class BaseType> class ListCompactIO;

	template<class T, class BaseType>
	void writeEntry(Ostream& os, const ListCompactIO<T, BaseType>& l);

	template<class T, class BaseType> Istream& operator>>
		(
			Istream&,
			ListCompactIO<T, BaseType>&
			);

	template<class T, class BaseType> Ostream& operator<<
		(
			Ostream&,
			const ListCompactIO<T, BaseType>&
			);


	/*---------------------------------------------------------------------------*\
							   Class ListCompactIO Declaration
	\*---------------------------------------------------------------------------*/

	template<class T, class BaseType>
	class ListCompactIO
		:
		public List<T>
	{
	protected:

		// Protected Member Functions

			//- Has too many elements in it?
		bool overflows() const;

		void convertToCompact
		(
			labelList& start,
			List<BaseType>& elems
		) const;

		void convertFromCompact
		(
			const labelList& start,
			const List<BaseType>& elems
		);


	public:

		// Constructors

			//- Construct null
		ListCompactIO();

		//- Construct from UList
		ListCompactIO(const UList<T>&);

		//- Construct from Istream
		ListCompactIO(Istream&);

		//- Move constructor
		ListCompactIO(ListCompactIO<T, BaseType>&&);

		//- Move constructor from List
		ListCompactIO(List<T>&&);


		// Member Operators

		void operator=(const ListCompactIO<T, BaseType>&);
		void operator=(ListCompactIO<T, BaseType>&&);

		void operator=(const List<T>&);
		void operator=(List<T>&&);


		// IOstream functions

		friend void writeEntry <T, BaseType>
			(
				Ostream& os,
				const ListCompactIO<T, BaseType>& l
				);


		// IOstream Operators

			//- Read List from Istream, discarding contents of existing List.
		friend Istream& operator>> <T, BaseType>
			(
				Istream&,
				ListCompactIO<T, BaseType>&
				);

		// Write List to Ostream.
		friend Ostream& operator<< <T, BaseType>
			(
				Ostream&,
				const ListCompactIO<T, BaseType>&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ListCompactIOI.hxx>

//#ifdef NoRepository
//#include <ListCompactIO.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ListCompactIO_Header
