#pragma once
#ifndef _smoluchowskiJumpTFvPatchScalarField_Header
#define _smoluchowskiJumpTFvPatchScalarField_Header

#include <Base_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <ThermophysicalModels_Module.hxx>

#include <mixedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class smoluchowskiJumpTFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class smoluchowskiJumpTFvPatchScalarField
		:
		public mixedFvPatchScalarField
	{

		// Private Data

			//- Velocity field name, default = "U"
		word UName_;

		//- Density field name, default = "rho"
		word rhoName_;

		//- Compressibility field name, default = "thermo:psi"
		word psiName_;

		//- Dynamic viscosity field name, default = "thermo:mu"
		word muName_;

		//- Accommodation coefficient
		scalar accommodationCoeff_;

		//- Wall surface temperature
		scalarField Twall_;

		//- Heat capacity ratio (default 1.4)
		scalar gamma_;

	public:

		//- Runtime type information
		TypeName("smoluchowskiJumpT");


		// Constructors

			//- Construct from patch and internal field
		smoluchowskiJumpTFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		smoluchowskiJumpTFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given smoluchowskiJumpTFvPatchScalarField
		//  onto a new patch
		smoluchowskiJumpTFvPatchScalarField
		(
			const smoluchowskiJumpTFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new smoluchowskiJumpTFvPatchScalarField(*this)
					);
		}

		//- Construct as copy setting internal field reference
		smoluchowskiJumpTFvPatchScalarField
		(
			const smoluchowskiJumpTFvPatchScalarField&,
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
					new smoluchowskiJumpTFvPatchScalarField(*this, iF)
					);
		}

		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		virtual void rmap(const fvPatchScalarField&, const labelList&);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_smoluchowskiJumpTFvPatchScalarField_Header
