#pragma once
#ifndef _PackingModel_Header
#define _PackingModel_Header

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
	tnbLib::PackingModel

Description
	Base class for packing models.

SourceFiles
	PackingModel.C
	PackingModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#include <vector.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes

	class ParticleStressModel;

	class CorrectionLimitingMethod;

	template<class Type>
	class AveragingMethod;

	/*---------------------------------------------------------------------------*\
							 Class PackingModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class PackingModel
		:
		public CloudSubModelBase<CloudType>
	{
	protected:

		//- Protected data

			//- Particle stress model
		autoPtr<ParticleStressModel> particleStressModel_;


	public:

		//- Runtime type information
		TypeName("packingModel");

		//- Declare runtime constructor selection table
		declareRunTimeSelectionTable
		(
			autoPtr,
			PackingModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);


		// Constructors

			//- Construct null from owner
		PackingModel(CloudType& owner);

		//- Construct from components
		PackingModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		PackingModel(const PackingModel<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<PackingModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~PackingModel();


		//- Selector
		static autoPtr<PackingModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Member Functions

			//- Calculate the velocity correction
		virtual vector velocityCorrection
		(
			typename CloudType::parcelType& p,
			const scalar deltaT
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makePackingModel(CloudType)                                            \
                                                                               \
    typedef tnbLib::CloudType::MPPICCloudType MPPICCloudType;                    \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::PackingModel<MPPICCloudType>,                                    \
        0                                                                      \
    );                                                                         \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            PackingModel<MPPICCloudType>,                                      \
            dictionary                                                         \
        );                                                                     \
    }


#define makePackingModelType(SS, CloudType)                                    \
                                                                               \
    typedef tnbLib::CloudType::MPPICCloudType MPPICCloudType;                    \
    defineNamedTemplateTypeNameAndDebug                                        \
        (tnbLib::PackingModels::SS<MPPICCloudType>, 0);                          \
                                                                               \
    tnbLib::PackingModel<MPPICCloudType>::                                       \
        adddictionaryConstructorToTable                                        \
        <tnbLib::PackingModels::SS<MPPICCloudType>>                              \
            add##SS##CloudType##MPPICCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PackingModelI.hxx>

//#ifdef NoRepository
//#include <PackingModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PackingModel_Header
