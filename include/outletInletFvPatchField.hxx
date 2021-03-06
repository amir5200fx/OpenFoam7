#pragma once
#ifndef _outletInletFvPatchField_Header
#define _outletInletFvPatchField_Header

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
	tnbLib::outletInletFvPatchField

Description
	This boundary condition provides a generic inflow condition, with
	specified outflow for the case of reverse flow.

Usage
	\table
		Property     | Description             | Required    | Default value
		phi          | Flux field name         | no          | phi
		outletValue  | Outlet value for reverse flow | yes   |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            outletInlet;
		phi             phi;
		outletValue     uniform 0;
		value           uniform 0;
	}
	\endverbatim

	The mode of operation is determined by the sign of the flux across the
	patch faces.

Note
	Sign conventions:
	- Positive flux (out of domain): apply the "outletValue" fixed-value
	- Negative flux (into of domain): apply zero-gradient condition

See also
	tnbLib::mixedFvPatchField
	tnbLib::zeroGradientFvPatchField
	tnbLib::inletOutletFvPatchField

SourceFiles
	outletInletFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <mixedFvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamOutletInletFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamOutletInletFvPatchField_EXPORT_DEFINE
#define FoamOutletInletFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamOutletInletFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class outletInletFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class outletInletFvPatchField
		:
		public mixedFvPatchField<Type>
	{

	protected:

		// Protected data

			//- Name of flux field
		word phiName_;


	public:

		//- Runtime type information
		/*TypeName("outletInlet");*/
		static const char* typeName_() { return "outletInlet"; }
		static FoamOutletInletFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamOutletInletFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		outletInletFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		outletInletFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given outletInletFvPatchField onto a new patch
		outletInletFvPatchField
		(
			const outletInletFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		outletInletFvPatchField
		(
			const outletInletFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new outletInletFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		outletInletFvPatchField
		(
			const outletInletFvPatchField<Type>&,
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
					new outletInletFvPatchField<Type>(*this, iF)
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

#include <outletInletFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <outletInletFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_outletInletFvPatchField_Header
