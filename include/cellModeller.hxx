#pragma once
#ifndef _cellModeller_Header
#define _cellModeller_Header

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
	tnbLib::cellModeller

Description
	A static collection of cell models, and a means of looking them up.

SourceFiles
	cellModeller.C
	cellModellerIO.C
	globalCellModeller.C

\*---------------------------------------------------------------------------*/

#include <cellModel.hxx>
#include <PtrList.hxx>
#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class cellModeller Declaration
	\*---------------------------------------------------------------------------*/

	class cellModeller
	{
		// Private Data

			//- PtrList of models
		static FoamBase_EXPORT PtrList<cellModel> models_;

		//- List of model pointers
		static FoamBase_EXPORT List<cellModel*> modelPtrs_;

		//- HashTable of model pointers
		static FoamBase_EXPORT HashTable<const cellModel*> modelDictionary_;


	public:

		// Constructors

			//- Construct from central "cellModels" file
		FoamBase_EXPORT cellModeller();

		//- Destructor
		FoamBase_EXPORT ~cellModeller();


		// Member Functions

			//- Look up a model by name and return a pointer to the model or nullptr
		static FoamBase_EXPORT const cellModel* lookup(const word&);

		//- Look up a model by index and return a pointer to the model or
		//  nullptr
		static FoamBase_EXPORT const cellModel* lookup(const label i);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellModeller_Header
