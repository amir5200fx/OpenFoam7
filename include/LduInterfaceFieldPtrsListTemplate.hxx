#pragma once
#ifndef _LduInterfaceFieldPtrsListTemplate_Header
#define _LduInterfaceFieldPtrsListTemplate_Header

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

Type
	lduInterfaceFieldPtrsList

Description
	List of coupled interface fields to be used in coupling.

\*---------------------------------------------------------------------------*/

#include <LduInterfaceFieldTemplate.hxx>
#include <UPtrList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class LduInterfaceFieldPtrsList Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class LduInterfaceFieldPtrsList
		:
		public UPtrList<const LduInterfaceField<Type>>
	{
	public:

		LduInterfaceFieldPtrsList(label size)
			:
			UPtrList<const LduInterfaceField<Type>>(size)
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LduInterfaceFieldPtrsListTemplate_Header
