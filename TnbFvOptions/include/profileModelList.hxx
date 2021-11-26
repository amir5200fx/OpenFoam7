#pragma once
#ifndef _profileModelList_Header
#define _profileModelList_Header

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
	tnbLib::profileModelList

Description
	Base class for profile models

SourceFiles
	profileModelList.C

\*---------------------------------------------------------------------------*/

#include <profileModel.hxx>
#include <PtrList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class profileModelList Declaration
	\*---------------------------------------------------------------------------*/

	class profileModelList
		:
		public PtrList<profileModel>
	{

	protected:

		// Protected data

			//- Dictionary
		const dictionary dict_;


	public:

		//- Constructor
		FoamFvOptions_EXPORT profileModelList(const dictionary& dict, const bool readFields = true);

		//- Destructor
		FoamFvOptions_EXPORT ~profileModelList();


		// Member Functions

			//- Set blade->profile addressing
		FoamFvOptions_EXPORT void connectBlades
		(
			const List<word>& names,
			List<label>& addr
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_profileModelList_Header
