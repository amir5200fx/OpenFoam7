#pragma once
#ifndef _CodedSource_Header
#define _CodedSource_Header

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
	tnbLib::fv::CodedSource

Description
   Constructs on-the-fly fvOption source

	The hook functions take the following arguments:

	codeCorrect
	(
		GeometricField<Type, fvPatchField, volMesh>& field
	)

	codeAddSup
	(
		fvMatrix<Type}>& eqn,
		const label fieldi
	)

	constrain
	(
		fvMatrix<Type}>& eqn,
		const label fieldi
	)

	where :
		field is the field in fieldNames
		eqn is the fvMatrix

Usage
	Example usage in controlDict:
	\verbatim
	energySource
	{
		type            scalarCodedSource;

		active          yes;

		name    sourceTime;

		scalarCodedSourceCoeffs
		{
			selectionMode   all;

			fields          (h);

			codeInclude
			#{

			#};

			codeCorrect
			#{
				Pout<< "**codeCorrect**" << endl;
			#};

			codeAddSup
			#{
				const Time& time = mesh().time();
				const scalarField& V = mesh_.V();
				scalarField& heSource = eqn.source();
				heSource -= 0.1*sqr(time.value())*V;
			#};

			codeSetValue
			#{
				Pout<< "**codeSetValue**" << endl;
			#};
		}

		sourceTimeCoeffs
		{
			$scalarCodedSourceCoeffs;
		}
	}
	\endverbatim


SourceFiles
	codedSource.C

\*---------------------------------------------------------------------------*/

#include <cellSetOption.hxx>
#include <codedBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								 Class codedSource Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class CodedSource
			:
			public cellSetOption,
			public codedBase
		{
		protected:

			// Protected static data

				//- The keywords associated with source code
			static FoamFvOptions_EXPORT const wordList codeKeys_;


			// Protected data

				//- The name
			word name_;

			//- Underlying functionObject
			mutable autoPtr<option> redirectFvOptionPtr_;


			// Protected Member Functions

				//- Get the loaded dynamic libraries
			FoamFvOptions_EXPORT virtual dlLibraryTable& libs() const;

			//- Adapt the context for the current object
			FoamFvOptions_EXPORT virtual void prepare(dynamicCode&, const dynamicCodeContext&) const;

			//- Return a description (type + name) for the output
			FoamFvOptions_EXPORT virtual string description() const;

			//- Clear any redirected objects
			FoamFvOptions_EXPORT virtual void clearRedirect() const;

			//- Get the dictionary to initialize the codeContext
			FoamFvOptions_EXPORT virtual const dictionary& codeDict() const;

			//- Get the keywords associated with source code
			FoamFvOptions_EXPORT virtual const wordList& codeKeys() const;


		public:

			//- Runtime type information
			//TypeName("coded");
			static const char* typeName_() { return "coded"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT CodedSource
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			// Member Functions

				//- Dynamically compiled fvOption
			FoamFvOptions_EXPORT option& redirectFvOption() const;

			// Evaluation

				//- Correct field
			FoamFvOptions_EXPORT virtual void correct
			(
				GeometricField<Type, fvPatchField, volMesh>&
			);

			//- Explicit and implicit matrix contributions
			FoamFvOptions_EXPORT virtual void addSup
			(
				fvMatrix<Type>& eqn,
				const label fieldi
			);

			//- Explicit and implicit matrix contributions
			//  to compressible equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<Type>& eqn,
				const label fieldi
			);

			//- Set value
			FoamFvOptions_EXPORT virtual void constrain
			(
				fvMatrix<Type>& eqn,
				const label fieldi
			);


			// IO

				//- Read source dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <CodedSource.cxx>
//#include <CodedSourceIO.cxx>
//#endif

#include <CodedSource_Imp.hxx>
#include <CodedSourceIO_Imp.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CodedSource_Header
