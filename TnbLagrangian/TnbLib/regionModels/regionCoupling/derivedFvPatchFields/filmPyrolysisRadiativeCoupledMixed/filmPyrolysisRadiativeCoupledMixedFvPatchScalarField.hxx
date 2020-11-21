#pragma once
#ifndef _filmPyrolysisRadiativeCoupledMixedFvPatchScalarField_Header
#define _filmPyrolysisRadiativeCoupledMixedFvPatchScalarField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::filmPyrolysisRadiativeCoupledMixedFvPatchScalarField

Description
	Mixed boundary condition for temperature, to be used in the flow and
	pyrolysis regions when a film region model is used.

	Example usage:
	\verbatim
	myInterfacePatchName
	{
		type            filmPyrolysisRadiativeCoupledMixed;
		Tnbr            T;
		kappa           fluidThermo;
		qr              qr;
		kappaName       none;
		filmDeltaDry    0.0;
		filmDeltaWet    3e-4;
		value           $internalField;
	}
	\endverbatim

	Needs to be on underlying mapped(Wall)FvPatch.
	It calculates local field as:

	\verbatim
		ratio = (filmDelta - filmDeltaDry)/(filmDeltaWet - filmDeltaDry)
	\endverbatim

	when ratio = 1 is considered wet and the film temperature is fixed at
	the wall. If ratio = 0 (dry) it emulates the normal radiative solid BC.

	In between ratio 0 and 1 the gradient and value contributions are
	weighted using the ratio field in the following way:

	\verbatim
		qConv = ratio*htcwfilm*(Tfilm - *this);
		qRad = (1.0 - ratio)*qr;
	\endverbatim

	Then the solid can gain or loose energy through radiation or conduction
	towards the film.

	Notes:

	- kappa and \c kappaName are inherited from temperatureCoupledBase.
	- qr is the radiative flux defined in the radiation model.


See also
	tnbLib::temperatureCoupledBase

SourceFiles
	filmPyrolysisRadiativeCoupledMixedFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <mixedFvPatchFields.hxx>
#include <temperatureCoupledBase.hxx>
#include <thermoSingleLayer.hxx>
#include <pyrolysisModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		Class filmPyrolysisRadiativeCoupledMixedFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class filmPyrolysisRadiativeCoupledMixedFvPatchScalarField
		:
		public mixedFvPatchScalarField,
		public temperatureCoupledBase
	{
	public:

		typedef tnbLib::regionModels::surfaceFilmModels::thermoSingleLayer
			filmModelType;

		typedef tnbLib::regionModels::pyrolysisModels::pyrolysisModel
			pyrolysisModelType;


	private:

		// Private Data

			//- Name of film region
		const word filmRegionName_;

		//- Name of pyrolysis region
		const word pyrolysisRegionName_;

		//- Name of field on the neighbour region
		const word TnbrName_;

		//- Name of the radiative heat flux
		const word qrName_;

		//- Convective Scaling Factor (as determined by Prateep's tests)
		const scalar convectiveScaling_;

		//- Minimum delta film to be consired dry
		const scalar filmDeltaDry_;

		//- Maximum delta film to be consired wet
		const scalar filmDeltaWet_;

		//- Retrieve film model from the database
		FoamLagrangian_EXPORT const filmModelType& filmModel() const;

		//- Retrieve pyrolysis model from the database
		FoamLagrangian_EXPORT const pyrolysisModelType& pyrModel() const;


	public:

		//- Runtime type information
		//TypeName("filmPyrolysisRadiativeCoupledMixed");
		static const char* typeName_() { return "filmPyrolysisRadiativeCoupledMixed"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamLagrangian_EXPORT filmPyrolysisRadiativeCoupledMixedFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamLagrangian_EXPORT filmPyrolysisRadiativeCoupledMixedFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  turbulentTemperatureCoupledBaffleMixedFvPatchScalarField onto a
		//  new patch
		FoamLagrangian_EXPORT filmPyrolysisRadiativeCoupledMixedFvPatchScalarField
		(
			const
			filmPyrolysisRadiativeCoupledMixedFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new filmPyrolysisRadiativeCoupledMixedFvPatchScalarField
					(
						*this
					)
					);
		}

		//- Construct as copy setting internal field reference
		FoamLagrangian_EXPORT filmPyrolysisRadiativeCoupledMixedFvPatchScalarField
		(
			const filmPyrolysisRadiativeCoupledMixedFvPatchScalarField&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchScalarField> clone
		(
			const DimensionedField<scalar, volMesh>& iF
		) const
		{
			return tmp<fvPatchScalarField>
				(
					new filmPyrolysisRadiativeCoupledMixedFvPatchScalarField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			//- Get corresponding K field
		FoamLagrangian_EXPORT tmp<scalarField> K() const;

		//- Update the coefficients associated with the patch field
		FoamLagrangian_EXPORT virtual void updateCoeffs();

		//- Write
		FoamLagrangian_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_filmPyrolysisRadiativeCoupledMixedFvPatchScalarField_Header
