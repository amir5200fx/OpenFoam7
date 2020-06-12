#include <scalarRanges.hxx>

#include <DynamicList.hxx>
#include <ListOps.hxx>

#include <Istream.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::scalarRanges::scalarRanges()
	:
	List<scalarRange>(0)
{}


tnbLib::scalarRanges::scalarRanges(Istream& is)
	:
	List<scalarRange>(0)
{
	DynamicList<scalarRange> lst;

	while (is.good())
	{
		scalarRange sr(is);
		if (sr.valid())
		{
			lst.append(sr);
		}
	}

	transfer(lst);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::scalarRanges::selected(const scalar value) const
{
	forAll(*this, i)
	{
		if (operator[](i).selected(value))
		{
			return true;
		}
	}

	return false;
}


tnbLib::List<bool> tnbLib::scalarRanges::selected
(
	const List<scalar>& values
) const
{
	List<bool> lst(values.size(), false);

	// check ranges
	forAll(values, i)
	{
		if (selected(values[i]))
		{
			lst[i] = true;
		}
	}

	// check specific values
	forAll(*this, rangeI)
	{
		if (operator[](rangeI).isExact())
		{
			scalar target = operator[](rangeI).value();

			int nearestIndex = -1;
			scalar nearestDiff = tnbLib::great;

			forAll(values, timeIndex)
			{
				scalar diff = fabs(values[timeIndex] - target);
				if (diff < nearestDiff)
				{
					nearestDiff = diff;
					nearestIndex = timeIndex;
				}
			}

			if (nearestIndex >= 0)
			{
				lst[nearestIndex] = true;
			}
		}
	}

	return lst;
}


tnbLib::List<tnbLib::scalar> tnbLib::scalarRanges::select
(
	const List<scalar>& values
) const
{
	return subset(selected(values), values);
}


void tnbLib::scalarRanges::inplaceSelect
(
	List<scalar>& values
) const
{
	inplaceSubset(selected(values), values);
}


// ************************************************************************* //