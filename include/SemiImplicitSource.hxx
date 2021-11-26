#pragma once
#ifndef _SemiImplicitSource_Header
#define _SemiImplicitSource_Header

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
	tnbLib::fv::SemiImplicitSource

Description
	Semi-implicit source, described using an input dictionary.  The injection
	rate coefficients are specified as pairs of Su-Sp coefficients, i.e.

		\f[
			S(x) = S_u + S_p x
		\f]

	where
	\vartable
		S(x)    | net source for field 'x'
		S_u     | explicit source contribution
		S_p     | linearised implicit contribution
	\endvartable

	Example of the source specification:

	\verbatim
	volumeMode      absolute; // specific
	injectionRateSuSp
	{
		k           (30.7 0);
		epsilon     (1.5  0);
	}
	\endverbatim

	Valid options for the \c volumeMode entry include:
	- absolute: values are given as \<quantity\>
	- specific: values are given as \<quantity\>/m3

See also
	tnbLib::fvOption

SourceFiles
	SemiImplicitSource.C

\*---------------------------------------------------------------------------*/

#include <cellSetOption.hxx>
#include <Tuple2.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		// Forward declaration of classes

		template<class Type>
		class SemiImplicitSource;


		// Forward declaration of friend functions

		template<class Type>
		Ostream& operator<<
			(
				Ostream&,
				const SemiImplicitSource<Type>&
				);


		/*---------------------------------------------------------------------------*\
							 Class SemiImplicitSource Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class SemiImplicitSource
			:
			public cellSetOption
		{
		public:

			// Public data

				//- Enumeration for volume types
			enum volumeModeType
			{
				vmAbsolute,
				vmSpecific
			};

			//- Word list of volume mode type names
			static FoamFvOptions_EXPORT const wordList volumeModeTypeNames_;


		protected:

			// Protected data

				//- Volume mode
			volumeModeType volumeMode_;

			//- Volume normalisation
			scalar VDash_;

			//- Source field values
			List<Tuple2<Type, scalar>> injectionRate_;


			// Protected functions

				//- Helper function to convert from a word to a volumeModeType
			FoamFvOptions_EXPORT volumeModeType wordToVolumeModeType(const word& vtName) const;

			//- Helper function to convert from a volumeModeType to a word
			FoamFvOptions_EXPORT word volumeModeTypeToWord(const volumeModeType& vtType) const;

			//- Set the local field data
			FoamFvOptions_EXPORT void setFieldData(const dictionary& dict);


		public:

			//- Runtime type information
			//TypeName("SemiImplicitSource");
			static const char* typeName_() { return "SemiImplicitSource"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT SemiImplicitSource
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			// Member Functions

				// Access

					//- Return const access to the volume mode
			inline const volumeModeType& volumeMode() const;

			//- Return const access to the source field values
			inline const List<Tuple2<Type, scalar>>& injectionRate() const;


			// Edit

				//- Return access to the volume mode
			inline volumeModeType& volumeMode();

			//- Return access to the source field values
			inline List<Tuple2<Type, scalar>>& injectionRate();


			// Evaluation

				//- Add explicit contribution to equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				fvMatrix<Type>& eqn,
				const label fieldi
			);

			//- Add explicit contribution to compressible equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& rho,
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
//#include <SemiImplicitSource.cxx>
//#include <SemiImplicitSourceIO.cxx>
//#endif

#include <SemiImplicitSource_Imp.hxx>
#include <SemiImplicitSourceIO_Imp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SemiImplicitSourceI.hxx>

#endif // !_SemiImplicitSource_Header
