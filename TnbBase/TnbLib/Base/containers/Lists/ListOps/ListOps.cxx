#include <ListOps.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::labelList tnbLib::emptyLabelList = tnbLib::labelList(0);


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::invert
(
	const label len,
	const labelUList& map
)
{
	labelList inverse(len, -1);

	forAll(map, i)
	{
		label newPos = map[i];

		if (newPos >= 0)
		{
			if (inverse[newPos] >= 0)
			{
				FatalErrorInFunction
					<< "Map is not one-to-one. At index " << i
					<< " element " << newPos << " has already occurred before"
					<< nl << "Please use invertOneToMany instead"
					<< abort(FatalError);
			}

			inverse[newPos] = i;
		}
	}
	return inverse;
}


tnbLib::labelListList tnbLib::invertOneToMany
(
	const label len,
	const labelUList& map
)
{
	labelList nElems(len, 0);

	forAll(map, i)
	{
		if (map[i] >= 0)
		{
			nElems[map[i]]++;
		}
	}

	labelListList inverse(len);

	forAll(nElems, i)
	{
		inverse[i].setSize(nElems[i]);
		nElems[i] = 0;
	}

	forAll(map, i)
	{
		label newI = map[i];

		if (newI >= 0)
		{
			inverse[newI][nElems[newI]++] = i;
		}
	}

	return inverse;
}


tnbLib::labelList tnbLib::identity(const label len)
{
	labelList map(len);

	forAll(map, i)
	{
		map[i] = i;
	}
	return map;
}


// ************************************************************************* //