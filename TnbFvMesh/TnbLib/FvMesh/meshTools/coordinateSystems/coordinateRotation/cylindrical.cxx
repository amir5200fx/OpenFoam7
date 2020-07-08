#include <cylindrical.hxx>

#include <axesRotation.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <polyMesh.hxx>
#include <tensorField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cylindrical, 0);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		cylindrical,
		dictionary
	);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		cylindrical,
		objectRegistry
	);
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::tensor tnbLib::cylindrical::R(const vector& dir) const
{
	const vector e3 = e3_ / mag(e3_);
	const vector r = dir - (dir & e3)*e3;

	if (mag(r) < small)
	{
		// If the cell centre is on the axis choose any radial direction
		return axesRotation(e3, perpendicular(e3)).R();
	}
	else
	{
		return axesRotation(e3, dir).R();
	}
}


void tnbLib::cylindrical::init
(
	const objectRegistry& obr,
	const List<label>& cells
)
{
	const polyMesh& mesh = refCast<const polyMesh>(obr);

	Rptr_.reset(new tensorField(cells.size()));

	updateCells(mesh, cells);
}


void tnbLib::cylindrical::init(const objectRegistry& obr)
{
	const polyMesh& mesh = refCast<const polyMesh>(obr);

	Rptr_.reset(new tensorField(mesh.nCells()));

	const vectorField& cc = mesh.cellCentres();

	tensorField& R = Rptr_();
	forAll(cc, celli)
	{
		vector dir = cc[celli] - origin_;
		dir /= mag(dir) + vSmall;

		R[celli] = this->R(dir);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cylindrical::cylindrical
(
	const dictionary& dict,
	const objectRegistry& obr
)
	:
	Rptr_(),
	origin_(point::zero),
	e3_(Zero)
{
	// If origin is specified in the coordinateSystem
	if (dict.parent().found("origin"))
	{
		dict.parent().lookup("origin") >> origin_;
	}

	// rotation axis
	dict.lookup("e3") >> e3_;

	init(obr);
}


tnbLib::cylindrical::cylindrical
(
	const objectRegistry& obr,
	const vector& axis,
	const point& origin
)
	:
	Rptr_(),
	origin_(origin),
	e3_(axis)
{
	init(obr);
}


tnbLib::cylindrical::cylindrical
(
	const objectRegistry& obr,
	const vector& axis,
	const point& origin,
	const List<label>& cells
)
	:
	Rptr_(),
	origin_(origin),
	e3_(axis)
{
	init(obr, cells);
}


tnbLib::cylindrical::cylindrical(const dictionary& dict)
	:
	Rptr_(),
	origin_(),
	e3_()
{
	FatalErrorInFunction
		<< " cylindrical can not be constructed from dictionary "
		<< " use the construtctor : "
		"("
		"    const dictionary&, const objectRegistry&"
		")"
		<< exit(FatalIOError);
}


tnbLib::cylindrical::cylindrical(const tensorField& R)
	:
	Rptr_(),
	origin_(Zero),
	e3_(Zero)
{
	Rptr_() = R;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::cylindrical::clear()
{
	if (!Rptr_.empty())
	{
		Rptr_.clear();
	}
}


void tnbLib::cylindrical::updateCells
(
	const polyMesh& mesh,
	const labelList& cells
)
{
	const vectorField& cc = mesh.cellCentres();
	tensorField& R = Rptr_();

	forAll(cells, i)
	{
		label celli = cells[i];
		vector dir = cc[celli] - origin_;
		dir /= mag(dir) + vSmall;

		R[i] = this->R(dir);
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::cylindrical::transform
(
	const vectorField& vf
) const
{
	if (Rptr_->size() != vf.size())
	{
		FatalErrorInFunction
			<< "vectorField st has different size to tensorField "
			<< abort(FatalError);
	}

	return (Rptr_() & vf);
}


tnbLib::vector tnbLib::cylindrical::transform(const vector& v) const
{
	NotImplemented;
	return Zero;
}


tnbLib::vector tnbLib::cylindrical::transform
(
	const vector& v,
	const label cmptI
) const
{
	return (Rptr_()[cmptI] & v);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::cylindrical::invTransform
(
	const vectorField& vf
) const
{
	return (Rptr_().T() & vf);
}


tnbLib::vector tnbLib::cylindrical::invTransform(const vector& v) const
{
	NotImplemented;
	return Zero;
}


tnbLib::vector tnbLib::cylindrical::invTransform
(
	const vector& v,
	const label cmptI
) const
{
	return (Rptr_()[cmptI].T() & v);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::cylindrical::transformTensor
(
	const tensorField& tf
) const
{
	if (Rptr_->size() != tf.size())
	{
		FatalErrorInFunction
			<< "tensorField st has different size to tensorField Tr"
			<< abort(FatalError);
	}
	return (Rptr_() & tf & Rptr_().T());
}


tnbLib::tensor tnbLib::cylindrical::transformTensor
(
	const tensor& t
) const
{
	NotImplemented;

	return Zero;
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::cylindrical::transformTensor
(
	const tensorField& tf,
	const labelList& cellMap
) const
{
	if (cellMap.size() != tf.size())
	{
		FatalErrorInFunction
			<< "tensorField tf has different size to tensorField Tr"
			<< abort(FatalError);
	}

	const tensorField& R = Rptr_();
	const tensorField Rtr(R.T());
	tmp<tensorField> tt(new tensorField(cellMap.size()));
	tensorField& t = tt.ref();
	forAll(cellMap, i)
	{
		t[i] = R[i] & tf[i] & Rtr[i];
	}

	return tt;
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::cylindrical::transformVector
(
	const vectorField& vf
) const
{
	if (Rptr_->size() != vf.size())
	{
		FatalErrorInFunction
			<< "tensorField vf has different size to tensorField Tr"
			<< abort(FatalError);
	}

	tmp<symmTensorField> tfld(new symmTensorField(Rptr_->size()));
	symmTensorField& fld = tfld.ref();

	const tensorField& R = Rptr_();
	forAll(fld, i)
	{
		fld[i] = transformPrincipal(R[i], vf[i]);
	}
	return tfld;
}


tnbLib::symmTensor tnbLib::cylindrical::transformVector
(
	const vector& v
) const
{
	NotImplemented;
	return Zero;
}


void tnbLib::cylindrical::write(Ostream& os) const
{
	writeEntry(os, "e3", e3());
}


// ************************************************************************* //