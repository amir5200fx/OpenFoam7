#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class T>
tnbLib::List<T> tnbLib::transform
(
	const tensor& rotTensor,
	const UList<T>& field
)
{
	List<T> newField(field.size());

	forAll(field, i)
	{
		newField[i] = transform(rotTensor, field[i]);
	}

	return newField;
}


template<class T>
void tnbLib::transformList(const tensor& rotTensor, UList<T>& field)
{
	forAll(field, i)
	{
		field[i] = transform(rotTensor, field[i]);
	}
}


template<class T>
void tnbLib::transformList(const tensorField& rotTensor, UList<T>& field)
{
	if (rotTensor.size() == 1)
	{
		forAll(field, i)
		{
			field[i] = transform(rotTensor[0], field[i]);
		}
	}
	else if (rotTensor.size() == field.size())
	{
		forAll(field, i)
		{
			field[i] = transform(rotTensor[i], field[i]);
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Sizes of field and transformation not equal. field:"
			<< field.size() << " transformation:" << rotTensor.size()
			<< abort(FatalError);
	}
}


template<class T>
void tnbLib::transformList(const tensor& rotTensor, Map<T>& field)
{
	forAllIter(typename Map<T>, field, iter)
	{
		iter() = transform(rotTensor[0], iter());
	}
}


template<class T>
void tnbLib::transformList(const tensorField& rotTensor, Map<T>& field)
{
	if (rotTensor.size() == 1)
	{
		forAllIter(typename Map<T>, field, iter)
		{
			iter() = transform(rotTensor[0], iter());
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Multiple transformation tensors not supported. field:"
			<< field.size() << " transformation:" << rotTensor.size()
			<< abort(FatalError);
	}
}


template<class T>
void tnbLib::transformList(const tensor& rotTensor, EdgeMap<T>& field)
{
	forAllIter(typename EdgeMap<T>, field, iter)
	{
		iter() = transform(rotTensor[0], iter());
	}
}


template<class T>
void tnbLib::transformList(const tensorField& rotTensor, EdgeMap<T>& field)
{
	if (rotTensor.size() == 1)
	{
		forAllIter(typename EdgeMap<T>, field, iter)
		{
			iter() = transform(rotTensor[0], iter());
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Multiple transformation tensors not supported. field:"
			<< field.size() << " transformation:" << rotTensor.size()
			<< abort(FatalError);
	}
}


// ************************************************************************* //