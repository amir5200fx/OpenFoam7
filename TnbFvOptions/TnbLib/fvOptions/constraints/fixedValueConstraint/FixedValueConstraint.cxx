#include <FixedValueConstraint.hxx>

#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <DimensionedField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fv::FixedValueConstraint<Type>::FixedValueConstraint
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh)
{
	read(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::fv::FixedValueConstraint<Type>::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		const dictionary& fieldValuesDict = coeffs_.subDict("fieldValues");

		fieldNames_.setSize(fieldValuesDict.size());
		fieldValues_.setSize(fieldNames_.size());

		label i = 0;
		forAllConstIter(dictionary, fieldValuesDict, iter)
		{
			fieldNames_[i] = iter().keyword();
			fieldValuesDict.lookup(iter().keyword()) >> fieldValues_[i];
			i++;
		}

		applied_.setSize(fieldNames_.size(), false);

		return true;
	}
	else
	{
		return false;
	}
}


template<class Type>
void tnbLib::fv::FixedValueConstraint<Type>::constrain
(
	fvMatrix<Type>& eqn,
	const label fieldi
)
{
	DebugInfo
		<< "FixedValueConstraint<"
		<< pTraits<Type>::typeName
		<< ">::constrain for source " << name_ << endl;

	eqn.setValues(cells_, List<Type>(cells_.size(), fieldValues_[fieldi]));
}


// ************************************************************************* //