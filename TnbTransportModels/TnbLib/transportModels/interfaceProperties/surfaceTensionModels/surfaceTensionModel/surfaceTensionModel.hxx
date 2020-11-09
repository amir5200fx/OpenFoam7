#pragma once
#ifndef _surfaceTensionModel_Header
#define _surfaceTensionModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::surfaceTensionModel

Description
	Abstract base-class for surface tension models which return the surface
	tension coefficient field.

Usage
	Example of the surface tension specification:
	\verbatim
		sigma
		{
			type                <surface tension model type>;
			<coefficient name>  <coefficient value>;
			.
			.
			.
		}
	\endverbatim
	For simplicity and backward-compatibility the constant value format is
	also supported, e.g.
	\verbatim
		sigma           0.07;
	\endverbatim

SourceFiles
	surfaceTensionModel.C
	newSurfaceTensionModel.C

\*---------------------------------------------------------------------------*/

#include <regIOobject.hxx>
#include <dimensionedTypes.hxx>
#include <volFieldsFwd.hxx>
#include <runTimeSelectionTables.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
							   Class surfaceTensionModel Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceTensionModel
		:
		public regIOobject
	{
	protected:

		// Protected member data

			//- Reference to mesh
		const fvMesh& mesh_;


		// Protected member functions

		static const dictionary& sigmaDict(const dictionary& dict)
		{
			return dict.subDict("sigma");
		}


	public:

		//- Runtime type information
		//TypeName("surfaceTensionModel");
		static const char* typeName_() { return "surfaceTensionModel"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare runtime construction

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			surfaceTensionModel,
			dictionary,
			(
				const dictionary& dict,
				const fvMesh& mesh
				),
				(dict, mesh)
		);*/

		typedef autoPtr<surfaceTensionModel> (*dictionaryConstructorPtr)(const dictionary& dict, const fvMesh& mesh);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamTransportModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamTransportModels_EXPORT void constructdictionaryConstructorTables();
		static FoamTransportModels_EXPORT void destroydictionaryConstructorTables();

		template <class surfaceTensionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<surfaceTensionModel> New(const dictionary& dict, const fvMesh& mesh)
			{
				return autoPtr<surfaceTensionModel>(new surfaceTensionModelType(dict, mesh));
			}

			adddictionaryConstructorToTable(const word& lookup = surfaceTensionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "surfaceTensionModel"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class surfaceTensionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<surfaceTensionModel> New(const dictionary& dict, const fvMesh& mesh)
			{
				return autoPtr<surfaceTensionModel>(new surfaceTensionModelType(dict, mesh));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = surfaceTensionModelType::typeName) : lookup_(
				lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Static Data Members

			//- Surface tension coefficient dimensions
		static FoamTransportModels_EXPORT const dimensionSet dimSigma;


		// Constructors

			// Construct from mesh
		FoamTransportModels_EXPORT surfaceTensionModel(const fvMesh& mesh);


		//- Destructor
		FoamTransportModels_EXPORT virtual ~surfaceTensionModel();


		// Selectors

		static FoamTransportModels_EXPORT autoPtr<surfaceTensionModel> New
		(
			const dictionary& dict,
			const fvMesh& mesh
		);


		// Member Functions

			//- Surface tension coefficient
		FoamTransportModels_EXPORT virtual tmp<volScalarField> sigma() const = 0;

		//- Update surface tension coefficient from given dictionary
		FoamTransportModels_EXPORT virtual bool readDict(const dictionary& dict) = 0;

		//- Write in dictionary format
		FoamTransportModels_EXPORT virtual bool writeData(Ostream& os) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceTensionModel_Header
