#pragma once
#ifndef _patchSummaryTemplates_Header
#define _patchSummaryTemplates_Header

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

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	template<class GeoField>
	void addToFieldList
	(
		PtrList<GeoField>& fieldList,
		const IOobject& obj,
		const label fieldi,
		const typename GeoField::Mesh& mesh
	);

	template<class GeoField>
	void outputFieldList
	(
		const PtrList<GeoField>& fieldList,
		const label patchi
	);

	template<class GeoField>
	void collectFieldList
	(
		const PtrList<GeoField>& fieldList,
		const label patchi,
		HashTable<word>& fieldToType
	);
} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "patchSummaryTemplatesI.hxx"

//#ifdef NoRepository
//#include "patchSummaryTemplates.C"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_patchSummaryTemplates_Header
