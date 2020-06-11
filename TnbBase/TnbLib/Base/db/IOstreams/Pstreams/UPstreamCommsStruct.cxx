#include <UPstream.hxx>

#include <boolList.hxx>
#include <token.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::UPstream::commsStruct::commsStruct()
	:
	above_(-1),
	below_(0),
	allBelow_(0),
	allNotBelow_(0)
{}


tnbLib::UPstream::commsStruct::commsStruct
(
	const label above,
	const labelList& below,
	const labelList& allBelow,
	const labelList& allNotBelow
)
	:
	above_(above),
	below_(below),
	allBelow_(allBelow),
	allNotBelow_(allNotBelow)
{}


tnbLib::UPstream::commsStruct::commsStruct
(
	const label nProcs,
	const label myProcID,
	const label above,
	const labelList& below,
	const labelList& allBelow
)
	:
	above_(above),
	below_(below),
	allBelow_(allBelow),
	allNotBelow_(nProcs - allBelow.size() - 1)
{
	boolList inBelow(nProcs, false);

	forAll(allBelow, belowI)
	{
		inBelow[allBelow[belowI]] = true;
	}

	label notI = 0;
	forAll(inBelow, proci)
	{
		if ((proci != myProcID) && !inBelow[proci])
		{
			allNotBelow_[notI++] = proci;
		}
	}
	if (notI != allNotBelow_.size())
	{
		FatalErrorInFunction << "problem!" << tnbLib::abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

bool tnbLib::UPstream::commsStruct::operator==(const commsStruct& comm) const
{
	return
		(
		(above_ == comm.above())
			&& (below_ == comm.below())
			&& (allBelow_ == allBelow())
			&& (allNotBelow_ == allNotBelow())
			);
}


bool tnbLib::UPstream::commsStruct::operator!=(const commsStruct& comm) const
{
	return !operator==(comm);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const UPstream::commsStruct& comm)
{
	os << comm.above_ << token::SPACE
		<< comm.below_ << token::SPACE
		<< comm.allBelow_ << token::SPACE
		<< comm.allNotBelow_;

	os.check
	(
		"Ostream& operator<<(Ostream&, const commsStruct&)"
	);

	return os;
}


// ************************************************************************* //