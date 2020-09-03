#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class ProcPatch>
tnbLib::lduSchedule tnbLib::lduPrimitiveMesh::nonBlockingSchedule
(
	const lduInterfacePtrsList& interfaces
)
{
	lduSchedule schedule(2 * interfaces.size());
	label slotI = 0;

	forAll(interfaces, i)
	{
		if (interfaces.set(i) && !isA<ProcPatch>(interfaces[i]))
		{
			schedule[slotI].patch = i;
			schedule[slotI].init = true;
			slotI++;
			schedule[slotI].patch = i;
			schedule[slotI].init = false;
			slotI++;
		}
	}

	forAll(interfaces, i)
	{
		if (interfaces.set(i) && isA<ProcPatch>(interfaces[i]))
		{
			schedule[slotI].patch = i;
			schedule[slotI].init = true;
			slotI++;
		}
	}

	forAll(interfaces, i)
	{
		if (interfaces.set(i) && isA<ProcPatch>(interfaces[i]))
		{
			schedule[slotI].patch = i;
			schedule[slotI].init = false;
			slotI++;
		}
	}

	return schedule;
}


// ************************************************************************* //