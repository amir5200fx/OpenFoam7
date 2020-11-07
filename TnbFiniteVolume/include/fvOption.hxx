#pragma once
#ifndef _fvOption_Header
#define _fvOption_Header

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
	tnbLib::fv::option

Description
	Finite volume options abstract base class.  Provides a base set of
	controls, e.g.:
	\verbatim
		type            scalarExplicitSource    // source type
		active          on;                     // on/off switch
	\endverbatim

Note
	On evaluation, source/sink options are to be added to the equation R.H.S.

SourceFiles
	fvOption.C
	fvOptionIO.C

\*---------------------------------------------------------------------------*/

#include <fvMatricesFwd.hxx>
#include <volFieldsFwd.hxx>
#include <dictionary.hxx>
#include <Switch.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								   Class option Declaration
		\*---------------------------------------------------------------------------*/

		class option
		{
		protected:

			// Protected data

				//- Source name
			const word name_;

			//- Model type
			const word modelType_;

			//- Reference to the mesh database
			const fvMesh& mesh_;

			//- Top level source dictionary
			dictionary dict_;

			//- Dictionary containing source coefficients
			dictionary coeffs_;

			//- Source active flag
			Switch active_;

			//- Field names to apply source to - populated by derived models
			wordList fieldNames_;

			//- Applied flag list - corresponds to each fieldNames_ entry
			List<bool> applied_;


		public:

			//- Runtime type information
			//TypeName("option");
			static const char* typeName_() { return "option"; }
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
			static FoamFiniteVolume_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Declare run-time constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				option,
				dictionary,
				(
					const word& name,
					const word& modelType,
					const dictionary& dict,
					const fvMesh& mesh
					),
					(name, modelType, dict, mesh)
			);*/

			typedef autoPtr<option> (*dictionaryConstructorPtr)(const word& name, const word& modelType, const dictionary& dict,
			                                                    const fvMesh& mesh);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamFiniteVolume_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamFiniteVolume_EXPORT void constructdictionaryConstructorTables();
			static FoamFiniteVolume_EXPORT void destroydictionaryConstructorTables();

			template <class optionType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<option> New(const word& name, const word& modelType, const dictionary& dict, const fvMesh& mesh)
				{
					return autoPtr<option>(new optionType(name, modelType, dict, mesh));
				}

				adddictionaryConstructorToTable(const word& lookup = optionType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "option" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class optionType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<option> New(const word& name, const word& modelType, const dictionary& dict, const fvMesh& mesh)
				{
					return autoPtr<option>(new optionType(name, modelType, dict, mesh));
				}

				addRemovabledictionaryConstructorToTable(const word& lookup = optionType::typeName) : lookup_(lookup)
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
			FoamFiniteVolume_EXPORT option
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Return clone
			autoPtr<option> clone() const
			{
				NotImplemented;
				return autoPtr<option>(nullptr);
			}

			//- Return pointer to new fvOption object created
			//  on the freestore from an Istream
			class iNew
			{
				//- Reference to the mesh
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

				autoPtr<option> operator()(Istream& is) const
				{
					// const word name(is);
					const dictionary dict(is);

					return autoPtr<option>
						(
							option::New(name_, dict, mesh_)
							);
				}
			};


			// Selectors

				//- Return a reference to the selected fvOption model
			static FoamFiniteVolume_EXPORT autoPtr<option> New
			(
				const word& name,
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			virtual FoamFiniteVolume_EXPORT ~option();


			// Member Functions

				// Access

					//- Return const access to the source name
			inline const word& name() const;

			//- Return const access to the mesh database
			inline const fvMesh& mesh() const;

			//- Return dictionary
			inline const dictionary& coeffs() const;

			//- Return const access to the source active flag
			inline bool active() const;

			//- Set the applied flag to true for field index fieldi
			inline void setApplied(const label fieldi);


			// Edit

				//- Return access to the source active flag
			inline Switch& active();


			// Checks

				//- Is the source active?
			FoamFiniteVolume_EXPORT virtual bool isActive();

			//- Return index of field name if found in fieldNames list
			FoamFiniteVolume_EXPORT virtual label applyToField(const word& fieldName) const;

			//- Check that the source has been applied
			FoamFiniteVolume_EXPORT virtual void checkApplied() const;


			// Evaluation

				// Explicit and implicit sources

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				fvMatrix<scalar>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				fvMatrix<symmTensor>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				fvMatrix<sphericalTensor>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				fvMatrix<tensor>& eqn,
				const label fieldi
			);


			// Explicit and implicit sources for compressible equations

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<scalar>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<symmTensor>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<sphericalTensor>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<tensor>& eqn,
				const label fieldi
			);


			// Explicit and implicit sources for phase equations

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				fvMatrix<scalar>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				fvMatrix<symmTensor>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				fvMatrix<sphericalTensor>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void addSup
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				fvMatrix<tensor>& eqn,
				const label fieldi
			);


			// Constraints

			FoamFiniteVolume_EXPORT virtual void constrain
			(
				fvMatrix<scalar>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void constrain
			(
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void constrain
			(
				fvMatrix<sphericalTensor>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void constrain
			(
				fvMatrix<symmTensor>& eqn,
				const label fieldi
			);

			FoamFiniteVolume_EXPORT virtual void constrain
			(
				fvMatrix<tensor>& eqn,
				const label fieldi
			);


			// Correction

			FoamFiniteVolume_EXPORT virtual void correct(volScalarField& field);
			FoamFiniteVolume_EXPORT virtual void correct(volVectorField& field);
			FoamFiniteVolume_EXPORT virtual void correct(volSphericalTensorField& field);
			FoamFiniteVolume_EXPORT virtual void correct(volSymmTensorField& field);
			FoamFiniteVolume_EXPORT virtual void correct(volTensorField& field);


			// IO

				//- Write the source header information
			FoamFiniteVolume_EXPORT virtual void writeHeader(Ostream&) const;

			//- Write the source footer information
			FoamFiniteVolume_EXPORT virtual void writeFooter(Ostream&) const;

			//- Write the source properties
			FoamFiniteVolume_EXPORT virtual void writeData(Ostream&) const;

			//- Read source dictionary
			FoamFiniteVolume_EXPORT virtual bool read(const dictionary& dict);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvOptionI.hxx>

#endif // !_fvOption_Header
