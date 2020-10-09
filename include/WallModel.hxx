#pragma once
#ifndef _WallModel_Header
#define _WallModel_Header

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
	tnbLib::WallModel

Description
	Templated wall interaction class

SourceFiles
	WallModel.C
	WallModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <WallSiteData.hxx>

#include <point.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class WallModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class WallModel
	{
		// Private Data

			//- The CollisionModel dictionary
		const dictionary& dict_;

		//- Reference to the owner cloud class
		CloudType& owner_;

		//- The coefficients dictionary
		const dictionary coeffDict_;


	public:

		//- Runtime type information
		TypeName("wallModel");

		//- Declare runtime constructor selection table
		declareRunTimeSelectionTable
		(
			autoPtr,
			WallModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);


		// Constructors

			//- Construct from components
		WallModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);


		//- Destructor
		virtual ~WallModel();


		//- Selector
		static autoPtr<WallModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Access

			//- Return the owner cloud object
		const CloudType& owner() const;

		//- Return non-const access to the owner cloud object
		CloudType& owner();

		//- Return the dictionary
		const dictionary& dict() const;

		//- Return the coefficients dictionary
		const dictionary& coeffDict() const;


		// Member Functions

			//- Return the effective radius for a particle for the model
		virtual scalar pREff(const typename CloudType::parcelType& p) const = 0;

		//- Whether the WallModel has a timestep limit that will
		//  require subCycling
		virtual bool controlsTimestep() const = 0;

		//- For WallModels that control the timestep, calculate the
		//  number of subCycles needed to satisfy the minimum
		//  allowable timestep
		virtual label nSubCycles() const = 0;

		//- Calculate the wall interaction for a parcel
		virtual void evaluateWall
		(
			typename CloudType::parcelType& p,
			const List<point>& flatSitePoints,
			const List<WallSiteData<vector>>& flatSiteData,
			const List<point>& sharpSitePoints,
			const List<WallSiteData<vector>>& sharpSiteData
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeWallModel(CloudType)                                               \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(tnbLib::WallModel<tnbLib::CloudType>, 0); \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            WallModel<tnbLib::CloudType>,                                        \
            dictionary                                                         \
        );                                                                     \
    }


#define makeWallModelType(SS, CloudType)                                       \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<tnbLib::CloudType>, 0);         \
                                                                               \
    tnbLib::WallModel<tnbLib::CloudType>::                                         \
        adddictionaryConstructorToTable<tnbLib::SS<tnbLib::CloudType>>             \
            add##SS##CloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <WallModelI.hxx>
#include <WallModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <WallModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_WallModel_Header