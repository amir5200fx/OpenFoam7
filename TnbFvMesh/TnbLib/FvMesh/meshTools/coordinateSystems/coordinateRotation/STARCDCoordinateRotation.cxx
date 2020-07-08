#include <STARCDCoordinateRotation.hxx>

#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(STARCDCoordinateRotation, 0);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		STARCDCoordinateRotation,
		dictionary
	);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		STARCDCoordinateRotation,
		objectRegistry
	);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::vector tnbLib::STARCDCoordinateRotation::transform(const vector& st) const
{
	return (R_ & st);
}


tnbLib::vector tnbLib::STARCDCoordinateRotation::invTransform
(
	const vector& st
) const
{
	return (Rtr_ & st);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::STARCDCoordinateRotation::transform
(
	const vectorField& st
) const
{
	NotImplemented;
	return tmp<vectorField>(nullptr);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::STARCDCoordinateRotation::invTransform
(
	const vectorField& st
) const
{
	NotImplemented;
	return tmp<vectorField>(nullptr);
}


const tnbLib::tensorField& tnbLib::STARCDCoordinateRotation::Tr() const
{
	NotImplemented;
	return NullObjectRef<tensorField>();
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::STARCDCoordinateRotation::transformTensor
(
	const tensorField& st
) const
{
	NotImplemented;
	return tmp<tensorField>(nullptr);
}


tnbLib::tensor tnbLib::STARCDCoordinateRotation::transformTensor
(
	const tensor& st
) const
{
	return (R_ & st & Rtr_);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::STARCDCoordinateRotation::transformTensor
(
	const tensorField& st,
	const labelList& cellMap
) const
{
	NotImplemented;
	return tmp<tensorField>(nullptr);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::STARCDCoordinateRotation::
transformVector
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


tnbLib::symmTensor tnbLib::STARCDCoordinateRotation::transformVector
(
	const vector& st
) const
{
	return transformPrincipal(R_, st);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::STARCDCoordinateRotation::calcTransform
(
	const scalar rotZ,
	const scalar rotX,
	const scalar rotY,
	const bool inDegrees
)
{
	scalar x = rotX;
	scalar y = rotY;
	scalar z = rotZ;

	if (inDegrees)
	{
		x *= constant::mathematical::pi / 180.0;
		y *= constant::mathematical::pi / 180.0;
		z *= constant::mathematical::pi / 180.0;
	}

	R_ =
		(
			tensor
			(
				cos(y)*cos(z) - sin(x)*sin(y)*sin(z),
				-cos(x)*sin(z),
				sin(x)*cos(y)*sin(z) + sin(y)*cos(z),

				cos(y)*sin(z) + sin(x)*sin(y)*cos(z),
				cos(x)*cos(z),
				sin(y)*sin(z) - sin(x)*cos(y)*cos(z),

				-cos(x)*sin(y),
				sin(x),
				cos(x)*cos(y)
			)
			);

	Rtr_ = R_.T();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation()
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{}


tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation
(
	const vector& rotZrotXrotY,
	const bool inDegrees
)
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{
	calcTransform
	(
		rotZrotXrotY.component(vector::X),
		rotZrotXrotY.component(vector::Y),
		rotZrotXrotY.component(vector::Z),
		inDegrees
	);
}


tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation
(
	const scalar rotZ,
	const scalar rotX,
	const scalar rotY,
	const bool inDegrees
)
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{
	calcTransform(rotZ, rotX, rotY, inDegrees);
}


tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation
(
	const dictionary& dict
)
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{
	vector rotation(dict.lookup("rotation"));

	calcTransform
	(
		rotation.component(vector::X),
		rotation.component(vector::Y),
		rotation.component(vector::Z),
		dict.lookupOrDefault("degrees", true)
	);
}


tnbLib::STARCDCoordinateRotation::STARCDCoordinateRotation
(
	const dictionary& dict,
	const objectRegistry&
)
{
	vector rotation(dict.lookup("rotation"));

	calcTransform
	(
		rotation.component(vector::X),
		rotation.component(vector::Y),
		rotation.component(vector::Z),
		dict.lookupOrDefault("degrees", true)
	);
}


void tnbLib::STARCDCoordinateRotation::write(Ostream& os) const
{
	writeEntry(os, "e1", e1());
	writeEntry(os, "e2", e2());
	writeEntry(os, "e3", e3());
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //