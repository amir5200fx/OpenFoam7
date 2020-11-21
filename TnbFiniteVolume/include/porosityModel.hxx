#pragma once
#ifndef _porosityModel_Header
#define _porosityModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::porosityModel

Description
	Top level model for porosity models

SourceFiles
	porosityModel.C
	porosityModelNew.C

\*---------------------------------------------------------------------------*/

#include <fvMesh.hxx>
#include <dictionary.hxx>
#include <fvMatricesFwd.hxx>
#include <runTimeSelectionTables.hxx>
#include <coordinateSystem.hxx>
#include <dimensionedVector.hxx>
#include <keyType.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class porosityModel Declaration
	\*---------------------------------------------------------------------------*/

	class porosityModel
		:
		public regIOobject
	{
		// Private Member Functions

			//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT porosityModel(const porosityModel&) = delete;

		//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const porosityModel&) = delete;


	protected:

		// Protected data

			//- Porosity name
		word name_;

		//- Reference to the mesh database
		const fvMesh& mesh_;

		//- Dictionary used for model construction
		const dictionary dict_;

		//- Model coefficients dictionary
		dictionary coeffs_;

		//- Porosity active flag
		bool active_;

		//- Name(s) of cell-zone
		keyType zoneName_;

		//- Cell zone IDs
		labelList cellZoneIDs_;

		//- Local co-ordinate system
		coordinateSystem coordSys_;


		// Protected Member Functions


			//- Transform the model data wrt mesh changes
		FoamFiniteVolume_EXPORT virtual void calcTransformModelData() = 0;

		//- Adjust negative resistance values to be multiplier of max value
		FoamFiniteVolume_EXPORT void adjustNegativeResistance(dimensionedVector& resist);

		//- Calculate the porosity force
		FoamFiniteVolume_EXPORT virtual void calcForce
		(
			const volVectorField& U,
			const volScalarField& rho,
			const volScalarField& mu,
			vectorField& force
		) const = 0;

		FoamFiniteVolume_EXPORT virtual void correct(fvVectorMatrix& UEqn) const = 0;

		FoamFiniteVolume_EXPORT 	virtual void correct
		(
			fvVectorMatrix& UEqn,
			const volScalarField& rho,
			const volScalarField& mu
		) const = 0;

		FoamFiniteVolume_EXPORT virtual void correct
		(
			const fvVectorMatrix& UEqn,
			volTensorField& AU
		) const = 0;

		//- Return label index
		FoamFiniteVolume_EXPORT label fieldIndex(const label index) const;


	public:

		//- Runtime type information
		//TypeName("porosityModel");
		static const char* typeName_() { return "porosityModel"; }
		static const ::tnbLib::word typeName;
		static int debug;
		virtual const word& type() const { return typeName; };

		//- Selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			porosityModel,
			mesh,
			(
				const word& modelName,
				const word& name,
				const fvMesh& mesh,
				const dictionary& dict,
				const word& cellZoneName
				),
				(modelName, name, mesh, dict, cellZoneName)
		);*/

		typedef autoPtr<porosityModel> (*meshConstructorPtr)(const word& modelName, const word& name, const fvMesh& mesh,
		                                                     const dictionary& dict, const word& cellZoneName);
		typedef HashTable<meshConstructorPtr, word, string::hash> meshConstructorTable;
		static FoamFiniteVolume_EXPORT meshConstructorTable* meshConstructorTablePtr_;
		static FoamFiniteVolume_EXPORT void constructmeshConstructorTables();
		static FoamFiniteVolume_EXPORT void destroymeshConstructorTables();

		template <class porosityModelType>
		class addmeshConstructorToTable
		{
		public:
			static autoPtr<porosityModel> New(const word& modelName, const word& name, const fvMesh& mesh,
			                                  const dictionary& dict, const word& cellZoneName)
			{
				return autoPtr<porosityModel>(new porosityModelType(modelName, name, mesh, dict, cellZoneName));
			}

			addmeshConstructorToTable(const word& lookup = porosityModelType::typeName)
			{
				constructmeshConstructorTables();
				if (!meshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "porosityModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addmeshConstructorToTable() { destroymeshConstructorTables(); }
		};

		template <class porosityModelType>
		class addRemovablemeshConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<porosityModel> New(const word& modelName, const word& name, const fvMesh& mesh,
			                                  const dictionary& dict, const word& cellZoneName)
			{
				return autoPtr<porosityModel>(new porosityModelType(modelName, name, mesh, dict, cellZoneName));
			}

			addRemovablemeshConstructorToTable(const word& lookup = porosityModelType::typeName) : lookup_(lookup)
			{
				constructmeshConstructorTables();
				meshConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablemeshConstructorToTable() { if (meshConstructorTablePtr_) { meshConstructorTablePtr_->erase(lookup_); } }
		};;

		//- Constructor
		FoamFiniteVolume_EXPORT porosityModel
		(
			const word& name,
			const word& modelType,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& cellZoneName = word::null
		);

		//- Return pointer to new porosityModel object created on the freestore
		//  from an Istream
		class iNew
		{
			//- Reference to the mesh database
			const fvMesh& mesh_;
			const word& name_;

		public:

			iNew
			(
				const fvMesh& mesh,
				const word& name
			)
				:
				mesh_(mesh),
				name_(name)
			{}

			autoPtr<porosityModel> operator()(Istream& is) const
			{
				const dictionary dict(is);

				return autoPtr<porosityModel>
					(
						porosityModel::New
						(
							name_,
							mesh_,
							dict
						)
						);
			}
		};

		//- Selector
		static FoamFiniteVolume_EXPORT autoPtr<porosityModel> New
		(
			const word& name,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& cellZoneName = word::null
		);

		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~porosityModel();


		// Member Functions

			//- Return const access to the porosity model name
		inline const word& name() const;

		//- Return const access to the porosity active flag
		inline bool active() const;

		//- Return const access to the cell zone IDs
		inline const labelList& cellZoneIDs() const;

		//- Return dictionary used for model construction
		FoamFiniteVolume_EXPORT const dictionary& dict() const;

		//- Transform the model data wrt mesh changes
		FoamFiniteVolume_EXPORT virtual void transformModelData();

		//- Return the force over the cell zone(s)
		FoamFiniteVolume_EXPORT virtual tmp<vectorField> force
		(
			const volVectorField& U,
			const volScalarField& rho,
			const volScalarField& mu
		);

		//- Add resistance
		FoamFiniteVolume_EXPORT virtual void addResistance(fvVectorMatrix& UEqn);

		//- Add resistance
		FoamFiniteVolume_EXPORT virtual void addResistance
		(
			fvVectorMatrix& UEqn,
			const volScalarField& rho,
			const volScalarField& mu
		);

		//- Add resistance
		FoamFiniteVolume_EXPORT virtual void addResistance
		(
			const fvVectorMatrix& UEqn,
			volTensorField& AU,
			bool correctAUprocBC
		);


		// I-O

			//- Write
		FoamFiniteVolume_EXPORT virtual bool writeData(Ostream& os) const;

		//- Inherit read from regIOobject
		using regIOobject::read;

		//- Read porosity dictionary
		FoamFiniteVolume_EXPORT virtual bool read(const dictionary& dict);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <porosityModelI.hxx>

#endif // !_porosityModel_Header
