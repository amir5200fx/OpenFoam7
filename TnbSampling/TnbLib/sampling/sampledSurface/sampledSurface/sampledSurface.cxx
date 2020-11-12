#include <sampledSurface.hxx>

#include <addToRunTimeSelectionTable.hxx>

#include <demandDrivenData.hxx>  // added by amir
#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sampledSurface, 0);
	defineRunTimeSelectionTable(sampledSurface, word);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSurface::makeSf() const
{
	// It is an error to recalculate if the pointer is already set
	if (SfPtr_)
	{
		FatalErrorInFunction
			<< "face area vectors already exist"
			<< abort(FatalError);
	}

	const faceList& theFaces = faces();
	SfPtr_ = new vectorField(theFaces.size());

	vectorField& values = *SfPtr_;
	forAll(theFaces, facei)
	{
		values[facei] = theFaces[facei].area(points());
	}
}


void tnbLib::sampledSurface::makeMagSf() const
{
	// It is an error to recalculate if the pointer is already set
	if (magSfPtr_)
	{
		FatalErrorInFunction
			<< "mag face areas already exist"
			<< abort(FatalError);
	}

	const faceList& theFaces = faces();
	magSfPtr_ = new scalarField(theFaces.size());

	scalarField& values = *magSfPtr_;
	forAll(theFaces, facei)
	{
		values[facei] = theFaces[facei].mag(points());
	}
}


void tnbLib::sampledSurface::makeCf() const
{
	// It is an error to recalculate if the pointer is already set
	if (CfPtr_)
	{
		FatalErrorInFunction
			<< "face centres already exist"
			<< abort(FatalError);
	}

	const faceList& theFaces = faces();
	CfPtr_ = new vectorField(theFaces.size());

	vectorField& values = *CfPtr_;
	forAll(theFaces, facei)
	{
		values[facei] = theFaces[facei].centre(points());
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSurface::clearGeom() const
{
	deleteDemandDrivenData(SfPtr_);
	deleteDemandDrivenData(magSfPtr_);
	deleteDemandDrivenData(CfPtr_);
	area_ = -1;
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::sampledSurface> tnbLib::sampledSurface::New
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
{
	const word sampleType(dict.lookup("type"));

	if (debug)
	{
		Info << "Selecting sampledType " << sampleType << endl;
	}

	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(sampleType);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown sample type "
			<< sampleType << nl << nl
			<< "Valid sample types : " << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<sampledSurface>(cstrIter()(name, mesh, dict));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurface::sampledSurface
(
	const word& name,
	const polyMesh& mesh,
	const bool interpolate
)
	:
	name_(name),
	mesh_(mesh),
	interpolate_(interpolate),
	SfPtr_(nullptr),
	magSfPtr_(nullptr),
	CfPtr_(nullptr),
	area_(-1)
{}


tnbLib::sampledSurface::sampledSurface
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	name_(name),
	mesh_(mesh),
	interpolate_(dict.lookupOrDefault("interpolate", false)),
	SfPtr_(nullptr),
	magSfPtr_(nullptr),
	CfPtr_(nullptr),
	area_(-1)
{
	dict.readIfPresent("name", name_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurface::~sampledSurface()
{
	clearGeom();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::vectorField& tnbLib::sampledSurface::Sf() const
{
	if (!SfPtr_)
	{
		makeSf();
	}

	return *SfPtr_;
}


const tnbLib::scalarField& tnbLib::sampledSurface::magSf() const
{
	if (!magSfPtr_)
	{
		makeMagSf();
	}

	return *magSfPtr_;
}


const tnbLib::vectorField& tnbLib::sampledSurface::Cf() const
{
	if (!CfPtr_)
	{
		makeCf();
	}

	return *CfPtr_;
}


tnbLib::scalar tnbLib::sampledSurface::area() const
{
	if (area_ < 0)
	{
		area_ = sum(magSf());
		reduce(area_, sumOp<scalar>());
	}

	return area_;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::sampledSurface::sample
(
	const surfaceScalarField& sField
) const
{
	NotImplemented;
	return tmp<scalarField>(nullptr);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::sampledSurface::sample
(
	const surfaceVectorField& sField
) const
{
	NotImplemented;
	return tmp<vectorField>(nullptr);
}


tnbLib::tmp<tnbLib::sphericalTensorField> tnbLib::sampledSurface::sample
(
	const surfaceSphericalTensorField& sField
) const
{
	NotImplemented;
	return tmp<sphericalTensorField>(nullptr);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::sampledSurface::sample
(
	const surfaceSymmTensorField& sField
) const
{
	NotImplemented;
	return tmp<symmTensorField>(nullptr);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::sampledSurface::sample
(
	const surfaceTensorField& sField
) const
{
	NotImplemented;
	return tmp<tensorField>(nullptr);
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::sampledSurface::project(const Field<scalar>& field) const
{
	tmp<Field<scalar>> tRes(new Field<scalar>(faces().size()));
	Field<scalar>& res = tRes.ref();

	forAll(faces(), facei)
	{
		res[facei] = field[facei];
	}

	return tRes;
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::sampledSurface::project(const Field<vector>& field) const
{
	tmp<Field<scalar>> tRes(new Field<scalar>(faces().size()));
	project(tRes.ref(), field);
	return tRes;
}


tnbLib::tmp<tnbLib::Field<tnbLib::vector>>
tnbLib::sampledSurface::project(const Field<sphericalTensor>& field) const
{
	tmp<Field<vector>> tRes(new Field<vector>(faces().size()));
	project(tRes.ref(), field);
	return tRes;
}


tnbLib::tmp<tnbLib::Field<tnbLib::vector>>
tnbLib::sampledSurface::project(const Field<symmTensor>& field) const
{
	tmp<Field<vector>> tRes(new Field<vector>(faces().size()));
	project(tRes.ref(), field);
	return tRes;
}


tnbLib::tmp<tnbLib::Field<tnbLib::vector>>
tnbLib::sampledSurface::project(const Field<tensor>& field) const
{
	tmp<Field<vector>> tRes(new Field<vector>(faces().size()));
	project(tRes.ref(), field);
	return tRes;
}


void tnbLib::sampledSurface::print(Ostream& os) const
{
	os << type();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamSampling_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream &os, const sampledSurface& s)
{
	s.print(os);
	os.check("Ostream& operator<<(Ostream&, const sampledSurface&");
	return os;
}


// ************************************************************************* //