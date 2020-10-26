#pragma once
#ifndef _LduInterfaceFieldTemplate_Header
#define _LduInterfaceFieldTemplate_Header

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
	tnbLib::LduInterfaceField

Description
	An abstract base class for implicitly-coupled interface fields
	e.g. processor and cyclic patch fields.

SourceFiles
	LduInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <lduInterfaceField.hxx>
#include <primitiveFieldsFwd.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class lduMatrix;

	/*---------------------------------------------------------------------------*\
						 Class LduInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class LduInterfaceField
		:
		public lduInterfaceField
	{

	public:

		//- Runtime type information
		//TypeName("LduInterfaceField");
		static const char* typeName_() { return "LduInterfaceField"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given coupled patch
		LduInterfaceField(const lduInterface& patch)
			:
			lduInterfaceField(patch)
		{}

		//- Disallow default bitwise copy construction
		LduInterfaceField(const LduInterfaceField&) = delete;


		//- Destructor
		virtual ~LduInterfaceField();


		// Member Functions

			// Coupled interface functionality

				//- Inherit initInterfaceMatrixUpdate from lduInterfaceField
		using lduInterfaceField::initInterfaceMatrixUpdate;

		//- Initialise neighbour matrix update
		virtual void initInterfaceMatrixUpdate
		(
			Field<Type>&,
			const Field<Type>&,
			const scalarField&,
			const Pstream::commsTypes commsType
		) const
		{}

		//- Inherit updateInterfaceMatrix from lduInterfaceField
		using lduInterfaceField::updateInterfaceMatrix;

		//- Update result field based on interface functionality
		virtual void updateInterfaceMatrix
		(
			Field<Type>&,
			const Field<Type>&,
			const scalarField&,
			const Pstream::commsTypes commsType
		) const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const LduInterfaceField&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <LduInterfaceFieldTemplateI.hxx>

//#ifdef NoRepository
//#include <LduInterfaceFieldTemplate.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LduInterfaceFieldTemplate_Header
