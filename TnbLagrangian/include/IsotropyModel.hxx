#pragma once
#ifndef _IsotropyModel_Header
#define _IsotropyModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::IsotropyModel

Description
	Base class for collisional return-to-isotropy models.

SourceFiles
	IsotropyModel.C
	IsotropyModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes

	class TimeScaleModel;

	/*---------------------------------------------------------------------------*\
							Class IsotropyModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class IsotropyModel
		:
		public CloudSubModelBase<CloudType>
	{
	protected:

		//- Time scale model
		autoPtr<TimeScaleModel> timeScaleModel_;


	public:

		//- Runtime type information
		TypeName("isotropyModel");

		//- Declare runtime constructor selection table
		declareRunTimeSelectionTable
		(
			autoPtr,
			IsotropyModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);


		// Constructors

			//- Construct null from owner
		IsotropyModel(CloudType& owner);

		//- Construct from components
		IsotropyModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct a copy
		IsotropyModel(const IsotropyModel<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<IsotropyModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~IsotropyModel();


		//- Selector
		static autoPtr<IsotropyModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		//- Member Functions

			//- Calculate velocities
		virtual void calculate() = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeIsotropyModel(CloudType)                                           \
                                                                               \
    typedef tnbLib::CloudType::MPPICCloudType MPPICCloudType;                    \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::IsotropyModel<MPPICCloudType>,                                   \
        0                                                                      \
    );                                                                         \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            IsotropyModel<MPPICCloudType>,                                     \
            dictionary                                                         \
        );                                                                     \
    }


#define makeIsotropyModelType(SS, CloudType)                                   \
                                                                               \
    typedef tnbLib::CloudType::MPPICCloudType MPPICCloudType;                    \
    defineNamedTemplateTypeNameAndDebug                                        \
        (tnbLib::IsotropyModels::SS<MPPICCloudType>, 0);                         \
                                                                               \
    tnbLib::IsotropyModel<MPPICCloudType>::                                      \
        adddictionaryConstructorToTable                                        \
        <tnbLib::IsotropyModels::SS<MPPICCloudType>>                             \
            add##SS##CloudType##MPPICCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <IsotropyModelI.hxx>

//#ifdef NoRepository
//#include <IsotropyModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IsotropyModel_Header
