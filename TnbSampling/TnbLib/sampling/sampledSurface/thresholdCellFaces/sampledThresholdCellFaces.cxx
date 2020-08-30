#include <sampledThresholdCellFaces.hxx>

#include <thresholdCellFaces.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{
		defineTypeNameAndDebug(thresholdCellFaces, 0);
		addToRunTimeSelectionTable(sampledSurface, thresholdCellFaces, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::sampledSurfaces::thresholdCellFaces::updateGeometry() const
{
	const fvMesh& fvm = static_cast<const fvMesh&>(mesh());

	// no update needed
	if (fvm.time().timeIndex() == prevTimeIndex_)
	{
		return false;
	}

	prevTimeIndex_ = fvm.time().timeIndex();

	// Optionally read volScalarField
	autoPtr<volScalarField> readFieldPtr_;

	// 1. see if field in database
	// 2. see if field can be read
	const volScalarField* cellFldPtr = nullptr;
	if (fvm.foundObject<volScalarField>(fieldName_))
	{
		if (debug)
		{
			InfoInFunction << "Lookup " << fieldName_ << endl;
		}

		cellFldPtr = &fvm.lookupObject<volScalarField>(fieldName_);
	}
	else
	{
		// Bit of a hack. Read field and store.

		if (debug)
		{
			InfoInFunction
				<< "Reading " << fieldName_
				<< " from time " << fvm.time().timeName()
				<< endl;
		}

		readFieldPtr_.reset
		(
			new volScalarField
			(
				IOobject
				(
					fieldName_,
					fvm.time().timeName(),
					fvm,
					IOobject::MUST_READ,
					IOobject::NO_WRITE,
					false
				),
				fvm
			)
		);

		cellFldPtr = readFieldPtr_.operator->();
	}
	const volScalarField& cellFld = *cellFldPtr;


	tnbLib::thresholdCellFaces surf
	(
		fvm,
		cellFld.primitiveField(),
		lowerThreshold_,
		upperThreshold_,
		triangulate_
	);

	const_cast<thresholdCellFaces&>
		(
			*this
			).MeshedSurface<face>::transfer(surf);
	meshCells_.transfer(surf.meshCells());

	// clear derived data
	sampledSurface::clearGeom();

	if (debug)
	{
		Pout << "thresholdCellFaces::updateGeometry() : constructed"
			<< nl
			<< "    field         : " << fieldName_ << nl
			<< "    lowerLimit    : " << lowerThreshold_ << nl
			<< "    upperLimit    : " << upperThreshold_ << nl
			<< "    point         : " << points().size() << nl
			<< "    faces         : " << faces().size() << nl
			<< "    cut cells     : " << meshCells_.size() << endl;
	}

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::thresholdCellFaces::thresholdCellFaces
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	sampledSurface(name, mesh, dict),
	fieldName_(dict.lookup("field")),
	lowerThreshold_(dict.lookupOrDefault<scalar>("lowerLimit", -vGreat)),
	upperThreshold_(dict.lookupOrDefault<scalar>("upperLimit", vGreat)),
	zoneKey_(keyType::null),
	triangulate_(dict.lookupOrDefault("triangulate", false)),
	prevTimeIndex_(-1),
	meshCells_(0)
{
	if (!dict.found("lowerLimit") && !dict.found("upperLimit"))
	{
		FatalErrorInFunction
			<< "require at least one of 'lowerLimit' or 'upperLimit'" << endl
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::thresholdCellFaces::~thresholdCellFaces()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::sampledSurfaces::thresholdCellFaces::needsUpdate() const
{
	const fvMesh& fvm = static_cast<const fvMesh&>(mesh());

	return fvm.time().timeIndex() != prevTimeIndex_;
}


bool tnbLib::sampledSurfaces::thresholdCellFaces::expire()
{
	// already marked as expired
	if (prevTimeIndex_ == -1)
	{
		return false;
	}

	// force update
	prevTimeIndex_ = -1;
	return true;
}


bool tnbLib::sampledSurfaces::thresholdCellFaces::update()
{
	return updateGeometry();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::thresholdCellFaces::sample
(
	const volScalarField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::thresholdCellFaces::sample
(
	const volVectorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::thresholdCellFaces::sample
(
	const volSphericalTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::thresholdCellFaces::sample
(
	const volSymmTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::thresholdCellFaces::sample
(
	const volTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::thresholdCellFaces::interpolate
(
	const interpolation<scalar>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::thresholdCellFaces::interpolate
(
	const interpolation<vector>& interpolator
) const
{
	return interpolateField(interpolator);
}

tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::thresholdCellFaces::interpolate
(
	const interpolation<sphericalTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::thresholdCellFaces::interpolate
(
	const interpolation<symmTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::thresholdCellFaces::interpolate
(
	const interpolation<tensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


void tnbLib::sampledSurfaces::thresholdCellFaces::print(Ostream& os) const
{
	os << "thresholdCellFaces: " << name() << " :"
		<< "  field:" << fieldName_
		<< "  lowerLimit:" << lowerThreshold_
		<< "  upperLimit:" << upperThreshold_;
	//<< "  faces:" << faces().size()   // possibly no geom yet
	//<< "  points:" << points().size();
}


// ************************************************************************* //