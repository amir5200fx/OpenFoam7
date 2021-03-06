#pragma once
#ifndef _regionModelFunctionObjectList_Header
#define _regionModelFunctionObjectList_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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
	tnbLib::regionModels::regionModelFunctionObjectList

Description
	List of cloud function objects

SourceFiles
	regionModelFunctionObjectListI.H
	regionModelFunctionObjectList.C

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <regionModelFunctionObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{

		class regionModel;

		/*---------------------------------------------------------------------------*\
						Class regionModelFunctionObjectList Declaration
		\*---------------------------------------------------------------------------*/

		class regionModelFunctionObjectList
			:
			public PtrList<regionModelFunctionObject>
		{
		protected:

			// Protected Data

				//- Reference to the region region model
			regionModel& regionModel_;

			//- Dictionary
			const dictionary dict_;


		public:

			// Constructors

				//- Null constructor
			FoamLagrangian_EXPORT regionModelFunctionObjectList(regionModel& region);

			//- Construct from mesh
			FoamLagrangian_EXPORT regionModelFunctionObjectList
			(
				regionModel& region,
				const dictionary& dict,
				const bool readFields = true
			);

			//- Construct copy
			FoamLagrangian_EXPORT regionModelFunctionObjectList
			(
				const regionModelFunctionObjectList& rmfol
			);


			//- Destructor
			FoamLagrangian_EXPORT virtual ~regionModelFunctionObjectList();


			// Member Functions

				// Access

					//- Return const access to the cloud region
			inline const regionModel& region() const;

			//- Return references to the cloud region
			inline regionModel& region();

			//- Return the forces dictionary
			inline const dictionary& dict() const;


			// Evaluation

				//- Pre-evolve hook
			FoamLagrangian_EXPORT virtual void preEvolveRegion();

			//- Post-evolve hook
			FoamLagrangian_EXPORT virtual void postEvolveRegion();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <regionModelFunctionObjectListI.hxx>

#endif // !_regionModelFunctionObjectList_Header
