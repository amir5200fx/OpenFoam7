#pragma once
#ifndef _DevolatilisationModel_Header
#define _DevolatilisationModel_Header

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
	tnbLib::DevolatilisationModel

Description
	Templated devolatilisation model class

SourceFiles
	DevolatilisationModel.C
	DevolatilisationModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#include <primitiveFieldsFwd.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class DevolatilisationModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class DevolatilisationModel
		:
		public CloudSubModelBase<CloudType>
	{
	protected:

		// Protected data

			//- Mass of lagrangian phase converted
		scalar dMass_;


	public:

		//- Runtime type information
		TypeName("devolatilisationModel");

		//- Declare runtime constructor selection table
		declareRunTimeSelectionTable
		(
			autoPtr,
			DevolatilisationModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);


		// Constructors

			//- Construct null from owner
		DevolatilisationModel(CloudType& owner);

		//- Construct from dictionary
		DevolatilisationModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		DevolatilisationModel(const DevolatilisationModel<CloudType>& dm);

		//- Construct and return a clone
		virtual autoPtr<DevolatilisationModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~DevolatilisationModel();


		//- Selector
		static autoPtr<DevolatilisationModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Member Functions

			//- Update model
		virtual void calculate
		(
			const scalar dt,
			const scalar age,
			const scalar mass0,
			const scalar mass,
			const scalar T,
			const scalarField& YGasEff,
			const scalarField& YLiquidEff,
			const scalarField& YSolidEff,
			label& canCombust,
			scalarField& dMassDV
		) const = 0;

		//- Add to devolatilisation mass
		void addToDevolatilisationMass(const scalar dMass);


		// I-O

			//- Write injection info to stream
		virtual void info(Ostream& os);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeDevolatilisationModel(CloudType)                                   \
                                                                               \
    typedef tnbLib::CloudType::reactingMultiphaseCloudType                       \
        reactingMultiphaseCloudType;                                           \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::DevolatilisationModel<reactingMultiphaseCloudType>,              \
        0                                                                      \
    );                                                                         \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            DevolatilisationModel<reactingMultiphaseCloudType>,                \
            dictionary                                                         \
        );                                                                     \
    }


#define makeDevolatilisationModelType(SS, CloudType)                           \
                                                                               \
    typedef tnbLib::CloudType::reactingMultiphaseCloudType                       \
        reactingMultiphaseCloudType;                                           \
    defineNamedTemplateTypeNameAndDebug                                        \
        (tnbLib::SS<reactingMultiphaseCloudType>, 0);                            \
                                                                               \
    tnbLib::DevolatilisationModel<reactingMultiphaseCloudType>::                 \
        adddictionaryConstructorToTable                                        \
        <tnbLib::SS<reactingMultiphaseCloudType>>                                \
        add##SS##CloudType##reactingMultiphaseCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <DevolatilisationModel.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DevolatilisationModel_Header
