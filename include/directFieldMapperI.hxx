#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::directFieldMapper::map
(
	Field<Type>& f,
	const Field<Type>& mapF
) const
{
	if (notNull(addressing()) && addressing().size())
	{
		f.map(mapF, addressing());
	}
	else
	{
		f.setSize(0);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::directFieldMapper::map
(
	const Field<Type>& mapF
) const
{
	tmp<Field<Type>> tf(new Field<Type>(addressing().size()));
	map(tf.ref(), mapF);
	return tf;
}


// ************************************************************************* //