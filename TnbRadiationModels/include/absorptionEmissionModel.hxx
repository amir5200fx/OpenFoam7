#pragma once
#ifndef _absorptionEmissionModel_Header
#define _absorptionEmissionModel_Header

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
	tnbLib::radiationModels::absorptionEmissionModel

Description
	Model to supply absorption and emission coefficients for radiation
	modelling

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <volFields.hxx>
#include <Vector2DTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{

		/*---------------------------------------------------------------------------*\
						   Class absorptionEmissionModel Declaration
		\*---------------------------------------------------------------------------*/

		class absorptionEmissionModel
		{

		protected:

			// Protected data

				//- Radiation model dictionary
			const dictionary dict_;

			//- Reference to the fvMesh
			const fvMesh& mesh_;


		public:

			//- Runtime type information
			//TypeName("absorptionEmissionModel");
			static const char* typeName_() { return "absorptionEmissionModel"; }
			static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
			static FoamRadiationModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			//- Declare runtime constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				absorptionEmissionModel,
				dictionary,
				(
					const dictionary& dict,
					const fvMesh& mesh
					),
					(dict, mesh)
			);*/

			typedef autoPtr<absorptionEmissionModel> (*dictionaryConstructorPtr)(
				const dictionary& dict, const fvMesh& mesh);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamRadiationModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamRadiationModels_EXPORT void constructdictionaryConstructorTables();
			static FoamRadiationModels_EXPORT void destroydictionaryConstructorTables();

			template <class absorptionEmissionModelType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<absorptionEmissionModel> New(const dictionary& dict, const fvMesh& mesh)
				{
					return autoPtr<absorptionEmissionModel>(new absorptionEmissionModelType(dict, mesh));
				}

				adddictionaryConstructorToTable(const word& lookup = absorptionEmissionModelType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
							"absorptionEmissionModel" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class absorptionEmissionModelType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<absorptionEmissionModel> New(const dictionary& dict, const fvMesh& mesh)
				{
					return autoPtr<absorptionEmissionModel>(new absorptionEmissionModelType(dict, mesh));
				}

				addRemovabledictionaryConstructorToTable(
					const word& lookup = absorptionEmissionModelType::typeName) : lookup_(lookup)
				{
					constructdictionaryConstructorTables();
					dictionaryConstructorTablePtr_->set(lookup, New);
				}

				~addRemovabledictionaryConstructorToTable()
				{
					if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

				//- Construct from components
			FoamRadiationModels_EXPORT absorptionEmissionModel
			(
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Selector
			static FoamRadiationModels_EXPORT autoPtr<absorptionEmissionModel> New
			(
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			FoamRadiationModels_EXPORT virtual ~absorptionEmissionModel();


			// Member Functions

				// Access

					//- Reference to the mesh
			inline const fvMesh& mesh() const
			{
				return mesh_;
			}

			//- Reference to the dictionary
			inline const dictionary& dict() const
			{
				return dict_;
			}


			// Absorption coefficient

				//- Absorption coefficient (net)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> a(const label bandI = 0) const;

			//- Absorption coefficient for continuous phase
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> aCont(const label bandI = 0) const;

			//- Absorption coefficient for dispersed phase
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> aDisp(const label bandI = 0) const;


			// Emission coefficient

				//- Emission coefficient (net)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> e(const label bandI = 0) const;

			//- Return emission coefficient for continuous phase
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> eCont(const label bandI = 0) const;

			//- Return emission coefficient for dispersed phase
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> eDisp(const label bandI = 0) const;


			// Emission contribution

				//- Emission contribution (net)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> E(const label bandI = 0) const;

			//- Emission contribution for continuous phase
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> ECont(const label bandI = 0) const;

			//- Emission contribution for dispersed phase
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> EDisp(const label bandI = 0) const;


			//- Const access to the number of bands - defaults to 1 for grey
			//  absorption/emission
			FoamRadiationModels_EXPORT virtual label nBands() const;

			//- Const access to the bands - defaults to Vector2D::one for grey
			//  absorption/emission
			FoamRadiationModels_EXPORT virtual const Vector2D<scalar>& bands(const label n) const;

			//- Flag for whether the absorption/emission is for a grey gas
			FoamRadiationModels_EXPORT virtual bool isGrey() const;

			//- Correct absorption coefficients
			FoamRadiationModels_EXPORT virtual void correct
			(
				volScalarField& a,
				PtrList<volScalarField>& aj
			) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_absorptionEmissionModel_Header
