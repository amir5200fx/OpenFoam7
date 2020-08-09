#include <mappedPatchFieldBase.hxx>

#include <mappedPatchBase.hxx>
#include <interpolationCell.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	mappedPatchFieldBase<Type>::mappedPatchFieldBase
	(
		const mappedPatchBase& mapper,
		const fvPatchField<Type>& patchField,
		const word& fieldName,
		const bool setAverage,
		const Type average,
		const word& interpolationScheme
	)
		:
		mapper_(mapper),
		patchField_(patchField),
		fieldName_(fieldName),
		setAverage_(setAverage),
		average_(average),
		interpolationScheme_(interpolationScheme)
	{}


	template<class Type>
	mappedPatchFieldBase<Type>::mappedPatchFieldBase
	(
		const mappedPatchBase& mapper,
		const fvPatchField<Type>& patchField,
		const dictionary& dict
	)
		:
		mapper_(mapper),
		patchField_(patchField),
		fieldName_
		(
			dict.template lookupOrDefault<word>
			(
				"field",
				patchField_.internalField().name()
				)
		),
		setAverage_(readBool(dict.lookup("setAverage"))),
		average_(pTraits<Type>(dict.lookup("average"))),
		interpolationScheme_(interpolationCell<Type>::typeName)
	{
		if (mapper_.mode() == mappedPatchBase::NEARESTCELL)
		{
			dict.lookup("interpolationScheme") >> interpolationScheme_;
		}
	}


	template<class Type>
	mappedPatchFieldBase<Type>::mappedPatchFieldBase
	(
		const mappedPatchBase& mapper,
		const fvPatchField<Type>& patchField
	)
		:
		mapper_(mapper),
		patchField_(patchField),
		fieldName_(patchField_.internalField().name()),
		setAverage_(false),
		average_(Zero),
		interpolationScheme_(interpolationCell<Type>::typeName)
	{}


	template<class Type>
	mappedPatchFieldBase<Type>::mappedPatchFieldBase
	(
		const mappedPatchFieldBase<Type>& mapper
	)
		:
		mapper_(mapper.mapper_),
		patchField_(mapper.patchField_),
		fieldName_(mapper.fieldName_),
		setAverage_(mapper.setAverage_),
		average_(mapper.average_),
		interpolationScheme_(mapper.interpolationScheme_)
	{}


	template<class Type>
	mappedPatchFieldBase<Type>::mappedPatchFieldBase
	(
		const mappedPatchBase& mapper,
		const fvPatchField<Type>& patchField,
		const mappedPatchFieldBase<Type>& base
	)
		:
		mapper_(mapper),
		patchField_(patchField),
		fieldName_(base.fieldName_),
		setAverage_(base.setAverage_),
		average_(base.average_),
		interpolationScheme_(base.interpolationScheme_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	const GeometricField<Type, fvPatchField, volMesh>&
		mappedPatchFieldBase<Type>::sampleField() const
	{
		typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

		const fvMesh& nbrMesh = refCast<const fvMesh>(mapper_.sampleMesh());

		if (mapper_.sameRegion())
		{
			if (fieldName_ == patchField_.internalField().name())
			{
				// Optimisation: bypass field lookup
				return
					dynamic_cast<const fieldType&>
					(
						patchField_.internalField()
						);
			}
			else
			{
				const fvMesh& thisMesh = patchField_.patch().boundaryMesh().mesh();
				return thisMesh.template lookupObject<fieldType>(fieldName_);
			}
		}
		else
		{
			return nbrMesh.template lookupObject<fieldType>(fieldName_);
		}
	}


	template<class Type>
	tmp<Field<Type>> mappedPatchFieldBase<Type>::mappedField() const
	{
		typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

		// Since we're inside initEvaluate/evaluate there might be processor
		// comms underway. Change the tag we use.
		int oldTag = UPstream::msgType();
		UPstream::msgType() = oldTag + 1;

		const fvMesh& thisMesh = patchField_.patch().boundaryMesh().mesh();
		const fvMesh& nbrMesh = refCast<const fvMesh>(mapper_.sampleMesh());

		// Result of obtaining remote values
		tmp<Field<Type>> tnewValues(new Field<Type>(0));
		Field<Type>& newValues = tnewValues.ref();

		switch (mapper_.mode())
		{
		case mappedPatchBase::NEARESTCELL:
		{
			const mapDistribute& distMap = mapper_.map();

			if (interpolationScheme_ != interpolationCell<Type>::typeName)
			{
				// Send back sample points to the processor that holds the cell
				vectorField samples(mapper_.samplePoints());
				distMap.reverseDistribute
				(
					(
						mapper_.sameRegion()
						? thisMesh.nCells()
						: nbrMesh.nCells()
						),
					point::max,
					samples
				);

				autoPtr<interpolation<Type>> interpolator
				(
					interpolation<Type>::New
					(
						interpolationScheme_,
						sampleField()
					)
				);
				const interpolation<Type>& interp = interpolator();

				newValues.setSize(samples.size(), pTraits<Type>::max);
				forAll(samples, celli)
				{
					if (samples[celli] != point::max)
					{
						newValues[celli] = interp.interpolate
						(
							samples[celli],
							celli
						);
					}
				}
			}
			else
			{
				newValues = sampleField();
			}

			distMap.distribute(newValues);

			break;
		}
		case mappedPatchBase::NEARESTPATCHFACE:
		case mappedPatchBase::NEARESTPATCHFACEAMI:
		{
			const label nbrPatchID =
				nbrMesh.boundaryMesh().findPatchID(mapper_.samplePatch());

			if (nbrPatchID < 0)
			{
				FatalErrorInFunction
					<< "Unable to find sample patch " << mapper_.samplePatch()
					<< " in region " << mapper_.sampleRegion()
					<< " for patch " << patchField_.patch().name() << nl
					<< abort(FatalError);
			}

			const fieldType& nbrField = sampleField();

			newValues = nbrField.boundaryField()[nbrPatchID];
			mapper_.distribute(newValues);

			break;
		}
		case mappedPatchBase::NEARESTFACE:
		{
			Field<Type> allValues(nbrMesh.nFaces(), Zero);

			const fieldType& nbrField = sampleField();

			forAll(nbrField.boundaryField(), patchi)
			{
				const fvPatchField<Type>& pf =
					nbrField.boundaryField()[patchi];
				label faceStart = pf.patch().start();

				forAll(pf, facei)
				{
					allValues[faceStart++] = pf[facei];
				}
			}

			mapper_.distribute(allValues);
			newValues.transfer(allValues);

			break;
		}
		default:
		{
			FatalErrorInFunction
				<< "Unknown sampling mode: " << mapper_.mode()
				<< nl << abort(FatalError);
		}
		}

		if (setAverage_)
		{
			Type averagePsi =
				gSum(patchField_.patch().magSf()*newValues)
				/ gSum(patchField_.patch().magSf());

			if (mag(averagePsi) / mag(average_) > 0.5)
			{
				newValues *= mag(average_) / mag(averagePsi);
			}
			else
			{
				newValues += (average_ - averagePsi);
			}
		}

		// Restore tag
		UPstream::msgType() = oldTag;

		return tnewValues;
	}


	template<class Type>
	void mappedPatchFieldBase<Type>::write(Ostream& os) const
	{
		writeEntry(os, "field", fieldName_);
		writeEntry(os, "setAverage", setAverage_);
		writeEntry(os, "average", average_);
		writeEntry(os, "interpolationScheme", interpolationScheme_);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //