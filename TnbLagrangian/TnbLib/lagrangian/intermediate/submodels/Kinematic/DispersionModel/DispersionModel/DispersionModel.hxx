#pragma once
#ifndef _DispersionModel_Header
#define _DispersionModel_Header

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
	tnbLib::DispersionModel

Description

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#include <vector.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class DispersionModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class DispersionModel
		:
		public CloudSubModelBase<CloudType>
	{
	public:

		//- Runtime type information
		TypeName("dispersionModel");


		// Declare runtime constructor selection table

		declareRunTimeSelectionTable
		(
			autoPtr,
			DispersionModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);


		// Constructors

			//- Construct null from owner
		DispersionModel(CloudType& owner);

		//- Construct from components
		DispersionModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		DispersionModel(const DispersionModel<CloudType>& dm);

		//- Construct and return a clone
		virtual autoPtr<DispersionModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~DispersionModel();


		//- Selector
		static autoPtr<DispersionModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Member Functions

			//- Update (disperse particles)
		virtual vector update
		(
			const scalar dt,
			const label celli,
			const vector& U,
			const vector& Uc,
			vector& UTurb,
			scalar& tTurb
		) = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeDispersionModel(CloudType)                                         \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineTemplateTypeNameAndDebug                                             \
        (tnbLib::DispersionModel<kinematicCloudType>, 0);                        \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            DispersionModel<kinematicCloudType>,                               \
            dictionary                                                         \
        );                                                                     \
    }

#define makeDispersionModelType(SS, CloudType)                                 \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<kinematicCloudType>, 0);      \
                                                                               \
    tnbLib::DispersionModel<kinematicCloudType>::                                \
        adddictionaryConstructorToTable<tnbLib::SS<kinematicCloudType>>          \
            add##SS##CloudType##kinematicCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <DispersionModel.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DispersionModel_Header
