#pragma once
#ifndef _lduMesh_Header
#define _lduMesh_Header

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
	tnbLib::lduMesh

Description
	Abstract base class for meshes which provide LDU addressing for the
	construction of lduMatrix and LDU-solvers.

\*---------------------------------------------------------------------------*/

#include <lduAddressing.hxx>
#include <lduInterfaceFieldPtrsList.hxx>
#include <typeInfo.hxx>
#include <InfoProxy.hxx>

#include <lduInterfacePtrsList.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class objectRegistry;


	// Forward declaration of friend functions and operators

	class lduMesh;

	Ostream& operator<<(Ostream&, const InfoProxy<lduMesh>&);


	/*---------------------------------------------------------------------------*\
							   Class lduMesh Declaration
	\*---------------------------------------------------------------------------*/

	class lduMesh
	{

	public:

		//- Runtime type information
		TypeName("lduMesh");


		// Constructors

		//- Destructor
		virtual ~lduMesh()
		{}


		// Member Functions

			// Access

				//- Return the object registry
		virtual const objectRegistry& thisDb() const;

		//- Return ldu addressing
		virtual const lduAddressing& lduAddr() const = 0;

		//- Return a list of pointers for each patch
		//  with only those pointing to interfaces being set
		virtual lduInterfacePtrsList interfaces() const = 0;

		//- Return communicator used for parallel communication
		virtual label comm() const = 0;

		//- Helper: reduce with current communicator
		template<class T, class BinaryOp>
		void reduce
		(
			T& Value,
			const BinaryOp& bop
		) const;


		// Info

			//- Return info proxy.
			//  Used to print mesh information to a stream
		InfoProxy<lduMesh> info() const
		{
			return *this;
		}


		// Ostream operator

		friend Ostream& operator<<(Ostream&, const InfoProxy<lduMesh>&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <lduMeshTemplatesI.hxx>

//#ifdef NoRepository
//#include <lduMeshTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_lduMesh_Header
