#pragma once
#ifndef _waveInletOutletFvPatchField_Header
#define _waveInletOutletFvPatchField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
	tnbLib::waveInletOutletFvPatchField

Description
	This boundary condition provides an inlet-outlet condition with differing
	inlet values on either side of a wave interface. All the wave modelling
	parameters are obtained from a centrally registered waveSuperposition
	class.

Usage
	\table
		Property        | Description                | Req'd? | Default
		phi             | Name of the flux field     | no     | phi
		inletValueAbove | inlet value above the wave | no     | None
		inletValueBelow | inlet value below the wave | no     | None
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type        waveInletOutlet;
		phi         phi;
		inletValueAbove 0.01;
		inletValueBelow table ((0 0.01) (10 0.1));
	}
	\endverbatim

See also
	tnbLib::waveSuperposition

SourceFiles
	waveInletOutletFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <Wave_Module.hxx>
#include <mixedFvPatchField.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef FoamWave_EXPORT_DEFINE
#define FoamWaveInletOutletFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamWaveInletOutletFvPatchField_EXPORT_DEFINE
#define FoamWaveInletOutletFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamWaveInletOutletFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class waveInletOutletFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class waveInletOutletFvPatchField
		:
		public mixedFvPatchField<Type>
	{
		// Private Data

			//- Inlet value above the wave
		const autoPtr<Function1<Type>> inletValueAbove_;

		//- Inlet value below the wave
		const autoPtr<Function1<Type>> inletValueBelow_;

		//- Name of flux field
		const word phiName_;


	public:

		//- Runtime type information
		//TypeName("waveInletOutlet");
		static const char* typeName_() { return "waveInletOutlet"; }
		static FoamWaveInletOutletFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamWaveInletOutletFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		waveInletOutletFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		waveInletOutletFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given field onto a new patch
		waveInletOutletFvPatchField
		(
			const waveInletOutletFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		waveInletOutletFvPatchField
		(
			const waveInletOutletFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new waveInletOutletFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		waveInletOutletFvPatchField
		(
			const waveInletOutletFvPatchField<Type>&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchField<Type>> clone
		(
			const DimensionedField<Type, volMesh>& iF
		) const
		{
			return tmp<fvPatchField<Type>>
				(
					new waveInletOutletFvPatchField<Type>
					(
						*this,
						iF
						)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();

		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <waveInletOutletFvPatchField.cxx>
//#endif

#include <waveInletOutletFvPatchFieldI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_waveInletOutletFvPatchField_Header
