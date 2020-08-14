#include <turbulentTemperatureCoupledBaffleMixedFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <mappedPatchBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		turbulentTemperatureCoupledBaffleMixedFvPatchScalarField::
			turbulentTemperatureCoupledBaffleMixedFvPatchScalarField
			(
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF
			)
			:
			mixedFvPatchScalarField(p, iF),
			temperatureCoupledBase(patch(), "undefined", "undefined", "undefined-K"),
			TnbrName_("undefined-Tnbr"),
			thicknessLayers_(0),
			kappaLayers_(0),
			contactRes_(0)
		{
			this->refValue() = 0.0;
			this->refGrad() = 0.0;
			this->valueFraction() = 1.0;
		}


		turbulentTemperatureCoupledBaffleMixedFvPatchScalarField::
			turbulentTemperatureCoupledBaffleMixedFvPatchScalarField
			(
				const turbulentTemperatureCoupledBaffleMixedFvPatchScalarField& ptf,
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF,
				const fvPatchFieldMapper& mapper
			)
			:
			mixedFvPatchScalarField(ptf, p, iF, mapper),
			temperatureCoupledBase(patch(), ptf),
			TnbrName_(ptf.TnbrName_),
			thicknessLayers_(ptf.thicknessLayers_),
			kappaLayers_(ptf.kappaLayers_),
			contactRes_(ptf.contactRes_)
		{}


		turbulentTemperatureCoupledBaffleMixedFvPatchScalarField::
			turbulentTemperatureCoupledBaffleMixedFvPatchScalarField
			(
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF,
				const dictionary& dict
			)
			:
			mixedFvPatchScalarField(p, iF),
			temperatureCoupledBase(patch(), dict),
			TnbrName_(dict.lookup("Tnbr")),
			thicknessLayers_(0),
			kappaLayers_(0),
			contactRes_(0.0)
		{
			if (!isA<mappedPatchBase>(this->patch().patch()))
			{
				FatalErrorInFunction
					<< "' not type '" << mappedPatchBase::typeName << "'"
					<< "\n    for patch " << p.name()
					<< " of field " << internalField().name()
					<< " in file " << internalField().objectPath()
					<< exit(FatalError);
			}

			if (dict.found("thicknessLayers"))
			{
				dict.lookup("thicknessLayers") >> thicknessLayers_;
				dict.lookup("kappaLayers") >> kappaLayers_;

				if (thicknessLayers_.size() > 0)
				{
					// Calculate effective thermal resistance by harmonic averaging
					forAll(thicknessLayers_, iLayer)
					{
						contactRes_ += thicknessLayers_[iLayer] / kappaLayers_[iLayer];
					}
					contactRes_ = 1.0 / contactRes_;
				}
			}

			fvPatchScalarField::operator=(scalarField("value", dict, p.size()));

			if (dict.found("refValue"))
			{
				// Full restart
				refValue() = scalarField("refValue", dict, p.size());
				refGrad() = scalarField("refGradient", dict, p.size());
				valueFraction() = scalarField("valueFraction", dict, p.size());
			}
			else
			{
				// Start from user entered data. Assume fixedValue.
				refValue() = *this;
				refGrad() = 0.0;
				valueFraction() = 1.0;
			}
		}


		turbulentTemperatureCoupledBaffleMixedFvPatchScalarField::
			turbulentTemperatureCoupledBaffleMixedFvPatchScalarField
			(
				const turbulentTemperatureCoupledBaffleMixedFvPatchScalarField& wtcsf,
				const DimensionedField<scalar, volMesh>& iF
			)
			:
			mixedFvPatchScalarField(wtcsf, iF),
			temperatureCoupledBase(patch(), wtcsf),
			TnbrName_(wtcsf.TnbrName_),
			thicknessLayers_(wtcsf.thicknessLayers_),
			kappaLayers_(wtcsf.kappaLayers_),
			contactRes_(wtcsf.contactRes_)
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		void turbulentTemperatureCoupledBaffleMixedFvPatchScalarField::updateCoeffs()
		{
			if (updated())
			{
				return;
			}

			// Since we're inside initEvaluate/evaluate there might be processor
			// comms underway. Change the tag we use.
			int oldTag = UPstream::msgType();
			UPstream::msgType() = oldTag + 1;

			// Get the coupling information from the mappedPatchBase
			const mappedPatchBase& mpp =
				refCast<const mappedPatchBase>(patch().patch());
			const polyMesh& nbrMesh = mpp.sampleMesh();
			const label samplePatchi = mpp.samplePolyPatch().index();
			const fvPatch& nbrPatch =
				refCast<const fvMesh>(nbrMesh).boundary()[samplePatchi];

			// Calculate the temperature by harmonic averaging
			// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			typedef turbulentTemperatureCoupledBaffleMixedFvPatchScalarField thisType;

			const fvPatchScalarField& nbrTp =
				nbrPatch.lookupPatchField<volScalarField, scalar>(TnbrName_);

			if (!isA<thisType>(nbrTp))
			{
				FatalErrorInFunction
					<< "Patch field for " << internalField().name() << " on "
					<< patch().name() << " is of type " << thisType::typeName
					<< endl << "The neighbouring patch field " << TnbrName_ << " on "
					<< nbrPatch.name() << " is required to be the same, but is "
					<< "currently of type " << nbrTp.type() << exit(FatalError);
			}

			const thisType& nbrField = refCast<const thisType>(nbrTp);

			// Swap to obtain full local values of neighbour internal field
			tmp<scalarField> nbrIntFld(new scalarField(nbrField.size(), 0.0));
			tmp<scalarField> nbrKDelta(new scalarField(nbrField.size(), 0.0));

			if (contactRes_ == 0.0)
			{
				nbrIntFld.ref() = nbrField.patchInternalField();
				nbrKDelta.ref() = nbrField.kappa(nbrField)*nbrPatch.deltaCoeffs();
			}
			else
			{
				nbrIntFld.ref() = nbrField;
				nbrKDelta.ref() = contactRes_;
			}

			mpp.distribute(nbrIntFld.ref());
			mpp.distribute(nbrKDelta.ref());

			tmp<scalarField> myKDelta = kappa(*this)*patch().deltaCoeffs();


			// Both sides agree on
			// - temperature : (myKDelta*fld + nbrKDelta*nbrFld)/(myKDelta+nbrKDelta)
			// - gradient    : (temperature-fld)*delta
			// We've got a degree of freedom in how to implement this in a mixed bc.
			// (what gradient, what fixedValue and mixing coefficient)
			// Two reasonable choices:
			// 1. specify above temperature on one side (preferentially the high side)
			//    and above gradient on the other. So this will switch between pure
			//    fixedvalue and pure fixedgradient
			// 2. specify gradient and temperature such that the equations are the
			//    same on both sides. This leads to the choice of
			//    - refGradient = zero gradient
			//    - refValue = neighbour value
			//    - mixFraction = nbrKDelta / (nbrKDelta + myKDelta())

			this->refValue() = nbrIntFld();
			this->refGrad() = 0.0;
			this->valueFraction() = nbrKDelta() / (nbrKDelta() + myKDelta());

			mixedFvPatchScalarField::updateCoeffs();

			if (debug)
			{
				scalar Q = gSum(kappa(*this)*patch().magSf()*snGrad());

				Info << patch().boundaryMesh().mesh().name() << ':'
					<< patch().name() << ':'
					<< this->internalField().name() << " <- "
					<< nbrMesh.name() << ':'
					<< nbrPatch.name() << ':'
					<< this->internalField().name() << " :"
					<< " heat transfer rate:" << Q
					<< " walltemperature "
					<< " min:" << gMin(*this)
					<< " max:" << gMax(*this)
					<< " avg:" << gAverage(*this)
					<< endl;
			}

			// Restore tag
			UPstream::msgType() = oldTag;
		}


		void turbulentTemperatureCoupledBaffleMixedFvPatchScalarField::write
		(
			Ostream& os
		) const
		{
			mixedFvPatchScalarField::write(os);
			writeEntry(os, "Tnbr", TnbrName_);
			writeEntry(os, "thicknessLayers", thicknessLayers_);
			writeEntry(os, "kappaLayers", kappaLayers_);

			temperatureCoupledBase::write(os);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		makePatchTypeField
		(
			fvPatchScalarField,
			turbulentTemperatureCoupledBaffleMixedFvPatchScalarField
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace compressible
} // End namespace tnbLib


// ************************************************************************* //