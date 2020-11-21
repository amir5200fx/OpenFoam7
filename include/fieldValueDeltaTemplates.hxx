#pragma once

// .cxx

#include <GeometricField.hxx>
#include <volMesh.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Type tnbLib::functionObjects::fieldValues::fieldValueDelta::applyOperation
(
	const Type& value1,
	const Type& value2
) const
{
	Type result = Zero;

	switch (operation_)
	{
	case operationType::add:
	{
		result = value1 + value2;
		break;
	}
	case operationType::subtract:
	{
		result = value1 - value2;
		break;
	}
	case operationType::min:
	{
		result = min(value1, value2);
		break;
	}
	case operationType::max:
	{
		result = max(value1, value2);
		break;
	}
	case operationType::average:
	{
		result = 0.5 * (value1 + value2);
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unable to process operation "
			<< operationTypeNames_[operation_]
			<< abort(FatalError);
	}
	}

	return result;
}


template<class Type>
void tnbLib::functionObjects::fieldValues::fieldValueDelta::processFields
(
	bool& found
)
{
	typedef GeometricField<Type, fvPatchField, volMesh> vf;
	typedef GeometricField<Type, fvsPatchField, surfaceMesh> sf;

	const wordList& fields1 = region1Ptr_->fields();

	const dictionary& results1 = region1Ptr_->resultDict();
	const dictionary& results2 = region2Ptr_->resultDict();

	Type r1(Zero);
	Type r2(Zero);

	forAll(fields1, i)
	{
		const word& fieldName = fields1[i];

		if
			(
				(obr_.foundObject<vf>(fieldName) || obr_.foundObject<sf>(fieldName))
				&& results2.found(fieldName)
				)
		{
			results1.lookup(fieldName) >> r1;
			results2.lookup(fieldName) >> r2;

			Type result = applyOperation(r1, r2);

			TnbLog << "    " << operationTypeNames_[operation_]
				<< "(" << fieldName << ") = " << result
				<< endl;

			if (Pstream::master())
			{
				file() << tab << result;
			}

			found = true;
		}
	}
}


// ************************************************************************* //