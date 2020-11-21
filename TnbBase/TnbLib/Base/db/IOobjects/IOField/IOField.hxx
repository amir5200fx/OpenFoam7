#pragma once
#ifndef _IOField_Header
#define _IOField_Header

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
	tnbLib::IOField

Description
	A primitive field of type \<T\> with automated input and output.

SourceFiles
	IOField.C

\*---------------------------------------------------------------------------*/

#include <regIOobject.hxx>
#include <Field.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class IOField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class IOField
		:
		public regIOobject,
		public Field<Type>
	{

	public:

		//TypeName("Field");
		static const char* typeName_() { return "Field"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from IOobject
		IOField(const IOobject&);

		//- Construct from IOobject; does local processor require reading?
		IOField(const IOobject&, const bool read);

		//- Construct from IOobject and size (does not set values)
		IOField(const IOobject&, const label size);

		//- Construct from components
		IOField(const IOobject&, const Field<Type>&);

		//- Move construct by transferring the Field contents
		IOField(const IOobject&, Field<Type>&&);

		//- Move construct by transferring the Field contents
		IOField(const IOobject&, const tmp<Field<Type>>&);

		//- Move constructor
		IOField(IOField<Type>&&);


		//- Destructor
		virtual ~IOField();


		// Member Functions

		bool writeData(Ostream&) const;


		// Member Operators

		void operator=(const IOField<Type>&);
		void operator=(IOField<Type>&&);

		void operator=(const Field<Type>&);
		void operator=(Field<Type>&&);
		void operator=(const tmp<Field<Type>>&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <IOFieldI.hxx>

//#ifdef NoRepository
//#include <IOField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IOField_Header
