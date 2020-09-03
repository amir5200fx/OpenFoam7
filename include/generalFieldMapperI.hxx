#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::generalFieldMapper::map
(
	Field<Type>& f,
	const Field<Type>& mapF
) const
{
	if (direct())
	{
		if (notNull(directAddressing()) && directAddressing().size())
		{
			f.map(mapF, directAddressing());
		}
		else
		{
			f.setSize(0);
		}
	}
	else
	{
		if (notNull(addressing()) && addressing().size())
		{
			f.map(mapF, addressing(), weights());
		}
		else
		{
			f.setSize(0);
		}
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::generalFieldMapper::map
(
	const Field<Type>& mapF
) const
{
	tmp<Field<Type>> tf
	(
		new Field<Type>
		(
			direct() ? directAddressing().size() : addressing().size()
			)
	);
	map(tf.ref(), mapF);
	return tf;
}


// ************************************************************************* //