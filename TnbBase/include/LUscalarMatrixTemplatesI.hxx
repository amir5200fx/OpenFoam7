#pragma once
#include <SubField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::LUscalarMatrix::solve
(
	Field<Type>& x,
	const Field<Type>& source
) const
{
	// If x and source are different initialize x = source
	if (&x != &source)
	{
		x = source;
	}

	if (Pstream::parRun())
	{
		Field<Type> X(m());

		if (Pstream::master(comm_))
		{
			typename Field<Type>::subField
			(
				X,
				x.size()
			) = x;

			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave(comm_);
					slave++
					)
			{
				IPstream::read
				(
					Pstream::commsTypes::scheduled,
					slave,
					reinterpret_cast<char*>
					(
						&(X[procOffsets_[slave]])
						),
						(procOffsets_[slave + 1] - procOffsets_[slave]) * sizeof(Type),
					Pstream::msgType(),
					comm_
				);
			}
		}
		else
		{
			OPstream::write
			(
				Pstream::commsTypes::scheduled,
				Pstream::masterNo(),
				reinterpret_cast<const char*>(x.begin()),
				x.byteSize(),
				Pstream::msgType(),
				comm_
			);
		}

		if (Pstream::master(comm_))
		{
			LUBacksubstitute(*this, pivotIndices_, X);

			x = typename Field<Type>::subField
			(
				X,
				x.size()
			);

			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave(comm_);
					slave++
					)
			{
				OPstream::write
				(
					Pstream::commsTypes::scheduled,
					slave,
					reinterpret_cast<const char*>
					(
						&(X[procOffsets_[slave]])
						),
						(procOffsets_[slave + 1] - procOffsets_[slave]) * sizeof(Type),
					Pstream::msgType(),
					comm_
				);
			}
		}
		else
		{
			IPstream::read
			(
				Pstream::commsTypes::scheduled,
				Pstream::masterNo(),
				reinterpret_cast<char*>(x.begin()),
				x.byteSize(),
				Pstream::msgType(),
				comm_
			);
		}
	}
	else
	{
		LUBacksubstitute(*this, pivotIndices_, x);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::LUscalarMatrix::solve
(
	const Field<Type>& source
) const
{
	tmp<Field<Type>> tx(new Field<Type>(m()));
	Field<Type>& x = tx.ref();

	solve(x, source);

	return tx;
}


// ************************************************************************* //