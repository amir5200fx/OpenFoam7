#pragma once
#ifndef _fieldDictionary_Header
#define _fieldDictionary_Header


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
	tnbLib::fieldDictionary

Description
	Read field as dictionary (without mesh).

\*---------------------------------------------------------------------------*/

#include <regIOobject.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{


	/*---------------------------------------------------------------------------*\
							   Class fieldDictionary Declaration
	\*---------------------------------------------------------------------------*/

	class fieldDictionary
		:
		public regIOobject,
		public dictionary
	{
		const word type_;

	public:

		// Redefine type name to be of the instantiated type
		virtual const word& type() const
		{
			return type_;
		}


		// Constructors

			//- Construct from ioobject and overloaded typename.
		fieldDictionary(const IOobject& io, const word& type)
			:
			regIOobject(io),
			dictionary(readStream(type)),
			type_(type)
		{
			close();
		}



		// Member Functions

		bool writeData(Ostream& os) const
		{
			static_cast<const dictionary&>(*this).write(os, false);

			return os.good();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fieldDictionary_Header
