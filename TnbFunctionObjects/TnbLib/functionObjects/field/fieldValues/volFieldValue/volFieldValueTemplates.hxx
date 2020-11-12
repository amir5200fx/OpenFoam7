#pragma once

// .cxx

#include <volFields.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Type>
bool tnbLib::functionObjects::fieldValues::volFieldValue::validField
(
	const word& fieldName
) const
{
	typedef GeometricField<Type, fvPatchField, volMesh> vf;

	if (obr_.foundObject<vf>(fieldName))
	{
		return true;
	}

	return false;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::functionObjects::fieldValues::volFieldValue::setFieldValues
(
	const word& fieldName,
	const bool mustGet
) const
{
	typedef GeometricField<Type, fvPatchField, volMesh> vf;

	if (obr_.foundObject<vf>(fieldName))
	{
		return filterField(obr_.lookupObject<vf>(fieldName));
	}

	if (mustGet)
	{
		FatalErrorInFunction
			<< "Field " << fieldName << " not found in database"
			<< abort(FatalError);
	}

	return tmp<Field<Type>>(new Field<Type>(0.0));
}


template<class Type>
Type tnbLib::functionObjects::fieldValues::volFieldValue::processValues
(
	const Field<Type>& values,
	const scalarField& V,
	const scalarField& weightField
) const
{
	Type result = Zero;
	switch (operation_)
	{
	case operationType::sum:
	{
		result = gSum(values);
		break;
	}
	case operationType::weightedSum:
	{
		result = gSum(weightField * values);
		break;
	}
	case operationType::sumMag:
	{
		result = gSum(cmptMag(values));
		break;
	}
	case operationType::average:
	{
		result = gSum(values) / nCells();
		break;
	}
	case operationType::weightedAverage:
	{
		result = gSum(weightField * values) / gSum(weightField);
		break;
	}
	case operationType::volAverage:
	{
		result = gSum(V * values) / this->V();
		break;
	}
	case operationType::weightedVolAverage:
	{
		result = gSum(weightField * V * values) / gSum(weightField * V);
		break;
	}
	case operationType::volIntegrate:
	{
		result = gSum(V * values);
		break;
	}
	case operationType::weightedVolIntegrate:
	{
		result = gSum(weightField * V * values);
		break;
	}
	case operationType::min:
	{
		result = gMin(values);
		break;
	}
	case operationType::max:
	{
		result = gMax(values);
		break;
	}
	case operationType::CoV:
	{
		Type meanValue = gSum(values * V) / this->V();

		const label nComp = pTraits<Type>::nComponents;

		for (direction d = 0; d < nComp; ++d)
		{
			scalarField vals(values.component(d));
			scalar mean = component(meanValue, d);
			scalar& res = setComponent(result, d);

			res = sqrt(gSum(V * sqr(vals - mean)) / this->V()) / mean;
		}

		break;
	}
	case operationType::none:
	{}
	}

	return result;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::functionObjects::fieldValues::volFieldValue::writeValues
(
	const word& fieldName
)
{
	const bool ok = validField<Type>(fieldName);

	if (ok)
	{
		Field<Type> values(setFieldValues<Type>(fieldName));
		scalarField V(filterField(fieldValue::mesh_.V()));
		scalarField weightField(values.size(), 1.0);

		if (weightFieldName_ != "none")
		{
			weightField = setFieldValues<scalar>(weightFieldName_, true);
		}

		Type result = processValues(values, V, weightField);

		if (Pstream::master())
		{
			// Add to result dictionary, over-writing any previous entry
			resultDict_.add(fieldName, result, true);

			if (writeFields_)
			{
				IOField<Type>
					(
						IOobject
						(
							fieldName + '_' + regionTypeNames_[regionType_]
							+ '-' + volRegion::regionName_,
							obr_.time().timeName(),
							obr_,
							IOobject::NO_READ,
							IOobject::NO_WRITE
						),
						(weightField * values).ref()
						).write();
			}


			file() << tab << result;

			TnbLog << "    " << operationTypeNames_[operation_]
				<< "(" << volRegion::regionName_ << ") of " << fieldName
				<< " = " << result << endl;
		}
	}

	return ok;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::functionObjects::fieldValues::volFieldValue::filterField
(
	const Field<Type>& field
) const
{
	if (isNull(cellIDs()))
	{
		return field;
	}
	else
	{
		return tmp<Field<Type>>(new Field<Type>(field, cellIDs()));
	}
}


// ************************************************************************* //
