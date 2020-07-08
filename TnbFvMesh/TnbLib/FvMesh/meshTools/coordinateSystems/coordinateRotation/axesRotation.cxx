#include <axesRotation.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(axesRotation, 0);
	addToRunTimeSelectionTable(coordinateRotation, axesRotation, dictionary);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		axesRotation,
		objectRegistry
	);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::axesRotation::calcTransform
(
	const vector& axis1,
	const vector& axis2,
	const axisOrder& order
)
{
	vector a = axis1 / mag(axis1);
	vector b = axis2;

	b = b - (b & a)*a;

	if (mag(b) < small)
	{
		FatalErrorInFunction
			<< "axis1, axis2 appear co-linear: "
			<< axis1 << ", " << axis2 << endl
			<< abort(FatalError);
	}

	b = b / mag(b);
	vector c = a ^ b;

	tensor Rtr;
	switch (order)
	{
	case e1e2:
	{
		Rtr = tensor(a, b, c);
		break;
	}
	case e2e3:
	{
		Rtr = tensor(c, a, b);
		break;
	}
	case e3e1:
	{
		Rtr = tensor(b, c, a);
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unhandled axes specifictation" << endl
			<< abort(FatalError);

		Rtr = Zero;
		break;
	}
	}

	// Global->local transformation
	Rtr_ = Rtr;

	// Local->global transformation
	R_ = Rtr.T();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::axesRotation::axesRotation()
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{}


tnbLib::axesRotation::axesRotation
(
	const vector& axis,
	const vector& dir
)
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{
	calcTransform(axis, dir, e3e1);
}


tnbLib::axesRotation::axesRotation
(
	const dictionary& dict
)
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{
	operator=(dict);
}


tnbLib::axesRotation::axesRotation
(
	const dictionary& dict,
	const objectRegistry& obr
)
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{
	operator=(dict);
}


tnbLib::axesRotation::axesRotation(const tensor& R)
	:
	R_(R),
	Rtr_(R_.T())
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::tensorField& tnbLib::axesRotation::Tr() const
{
	NotImplemented;
	return NullObjectRef<tensorField>();
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::axesRotation::transform
(
	const vectorField& st
) const
{
	return (R_ & st);
}


tnbLib::vector tnbLib::axesRotation::transform(const vector& st) const
{
	return (R_ & st);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::axesRotation::invTransform
(
	const vectorField& st
) const
{
	return (Rtr_ & st);
}


tnbLib::vector tnbLib::axesRotation::invTransform(const vector& st) const
{
	return (Rtr_ & st);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::axesRotation::transformTensor
(
	const tensorField& st
) const
{
	NotImplemented;
	return tmp<tensorField>(nullptr);
}


tnbLib::tensor tnbLib::axesRotation::transformTensor
(
	const tensor& st
) const
{
	return (R_ & st & Rtr_);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::axesRotation::transformTensor
(
	const tensorField& st,
	const labelList& cellMap
) const
{
	NotImplemented;
	return tmp<tensorField>(nullptr);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::axesRotation::transformVector
(
	const vectorField& st
) const
{
	tmp<symmTensorField> tfld(new symmTensorField(st.size()));
	symmTensorField& fld = tfld.ref();

	forAll(fld, i)
	{
		fld[i] = transformPrincipal(R_, st[i]);
	}
	return tfld;
}


tnbLib::symmTensor tnbLib::axesRotation::transformVector
(
	const vector& st
) const
{
	return transformPrincipal(R_, st);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::axesRotation::operator=(const dictionary& dict)
{
	if (debug)
	{
		Pout << "axesRotation::operator=(const dictionary&) : "
			<< "assign from " << dict << endl;
	}

	vector axis1, axis2;
	axisOrder order(e3e1);

	if (dict.readIfPresent("e1", axis1) && dict.readIfPresent("e2", axis2))
	{
		order = e1e2;
	}
	else if (dict.readIfPresent("e2", axis1) && dict.readIfPresent("e3", axis2))
	{
		order = e2e3;
	}
	else if (dict.readIfPresent("e3", axis1) && dict.readIfPresent("e1", axis2))
	{
		order = e3e1;
	}
	else if (dict.found("axis") || dict.found("direction"))
	{
		// Both "axis" and "direction" are required
		// If one is missing the appropriate error message will be generated
		order = e3e1;
		dict.lookup("axis") >> axis1;
		dict.lookup("direction") >> axis2;
	}
	else
	{
		FatalErrorInFunction
			<< "not entry of the type (e1, e2) or (e2, e3) or (e3, e1) "
			<< "found "
			<< exit(FatalError);
	}

	calcTransform(axis1, axis2, order);
}


void tnbLib::axesRotation::write(Ostream& os) const
{
	writeEntry(os, "e1", e1());
	writeEntry(os, "e2", e2());
	writeEntry(os, "e3", e3());
}


// ************************************************************************* //