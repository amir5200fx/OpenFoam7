#pragma once
#ifndef _Callback_Header
#define _Callback_Header

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
	tnbLib::Callback

Description
	Abstract class to handle automatic call-back registration with the
	CallbackRegistry.  Derive from this class and extend by adding the
	appropriate callback functions.

SourceFiles
	Callback.C

\*---------------------------------------------------------------------------*/

#include <CallbackRegistry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class Callback Declaration
	\*---------------------------------------------------------------------------*/

	template<class CallbackType>
	class Callback
		:
		public CallbackRegistry<CallbackType>::link
	{
		// Private Data

			//- CallbackRegistry reference
		CallbackRegistry<CallbackType>& cbr_;


	public:

		// Constructors

			//- Construct and register with CallbackRegistry
		Callback(CallbackRegistry<CallbackType>&);

		//- Copy constructor
		Callback(const Callback<CallbackType>&);


		//- Destructor
		virtual ~Callback();


		// Member Functions

			// Registration

				//- Register Callback with CallbackRegistry
		bool checkIn();

		//- Check-out Callback from CallbackRegistry
		bool checkOut();


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const Callback<CallbackType>&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CallbackI.hxx>

//#ifdef NoRepository
//#include <Callback.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Callback_Header
