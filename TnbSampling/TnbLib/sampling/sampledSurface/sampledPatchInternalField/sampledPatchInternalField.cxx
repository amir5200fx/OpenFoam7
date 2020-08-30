#include <sampledPatchInternalField.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{

		defineTypeNameAndDebug(patchInternalField, 0);
		addToRunTimeSelectionTable(sampledSurface, patchInternalField, word);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::patchInternalField::patchInternalField
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	patch(name, mesh, dict),
	mappers_(patchIDs().size())
{
	mappedPatchBase::offsetMode mode = mappedPatchBase::NORMAL;
	if (dict.found("offsetMode"))
	{
		mode = mappedPatchBase::offsetModeNames_.read
		(
			dict.lookup("offsetMode")
		);
	}

	switch (mode)
	{
	case mappedPatchBase::NORMAL:
	{
		const scalar distance = readScalar(dict.lookup("distance"));
		forAll(patchIDs(), i)
		{
			mappers_.set
			(
				i,
				new mappedPatchBase
				(
					mesh.boundaryMesh()[patchIDs()[i]],
					mesh.name(),                        // sampleRegion
					mappedPatchBase::NEARESTCELL,       // sampleMode
					word::null,                         // samplePatch
					-distance                  // sample inside my domain
				)
			);
		}
	}
	break;

	case mappedPatchBase::UNIFORM:
	{
		const point offset(dict.lookup("offset"));
		forAll(patchIDs(), i)
		{
			mappers_.set
			(
				i,
				new mappedPatchBase
				(
					mesh.boundaryMesh()[patchIDs()[i]],
					mesh.name(),                        // sampleRegion
					mappedPatchBase::NEARESTCELL,       // sampleMode
					word::null,                         // samplePatch
					offset                  // sample inside my domain
				)
			);
		}
	}
	break;

	case mappedPatchBase::NONUNIFORM:
	{
		const pointField offsets(dict.lookup("offsets"));
		forAll(patchIDs(), i)
		{
			mappers_.set
			(
				i,
				new mappedPatchBase
				(
					mesh.boundaryMesh()[patchIDs()[i]],
					mesh.name(),                        // sampleRegion
					mappedPatchBase::NEARESTCELL,       // sampleMode
					word::null,                         // samplePatch
					offsets                  // sample inside my domain
				)
			);
		}
	}
	break;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::patchInternalField::~patchInternalField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::patchInternalField::sample
(
	const volScalarField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::patchInternalField::sample
(
	const volVectorField& vField
) const
{
	return sampleField(vField);
}

tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::patchInternalField::sample
(
	const volSphericalTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::patchInternalField::sample
(
	const volSymmTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::patchInternalField::sample
(
	const volTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::patchInternalField::interpolate
(
	const interpolation<scalar>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::patchInternalField::interpolate
(
	const interpolation<vector>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::patchInternalField::interpolate
(
	const interpolation<sphericalTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::patchInternalField::interpolate
(
	const interpolation<symmTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::patchInternalField::interpolate
(
	const interpolation<tensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


void tnbLib::sampledSurfaces::patchInternalField::print(Ostream& os) const
{
	os << "patchInternalField: " << name() << " :"
		<< "  patches:" << patchNames()
		<< "  faces:" << faces().size()
		<< "  points:" << points().size();
}


// ************************************************************************* //