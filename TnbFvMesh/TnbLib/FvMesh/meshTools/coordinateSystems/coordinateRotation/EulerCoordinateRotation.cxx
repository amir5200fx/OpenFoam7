#include <EulerCoordinateRotation.hxx>

#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(EulerCoordinateRotation, 0);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		EulerCoordinateRotation,
		dictionary
	);
	addToRunTimeSelectionTable
	(
		coordinateRotation,
		EulerCoordinateRotation,
		objectRegistry
	);
}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::vector tnbLib::EulerCoordinateRotation::transform(const vector& st) const
{
	return (R_ & st);
}


tnbLib::vector tnbLib::EulerCoordinateRotation::invTransform
(
	const vector& st
) const
{
	return (Rtr_ & st);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::EulerCoordinateRotation::transform
(
	const vectorField& st
) const
{
	NotImplemented;
	return tmp<vectorField>(nullptr);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::EulerCoordinateRotation::invTransform
(
	const vectorField& st
) const
{
	NotImplemented;
	return tmp<vectorField>(nullptr);
}


const tnbLib::tensorField& tnbLib::EulerCoordinateRotation::Tr() const
{
	NotImplemented;
	return NullObjectRef<tensorField>();
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::EulerCoordinateRotation::transformTensor
(
	const tensorField& st
) const
{
	NotImplemented;
	return tmp<tensorField>(nullptr);
}


tnbLib::tensor tnbLib::EulerCoordinateRotation::transformTensor
(
	const tensor& st
) const
{
	return (R_ & st & Rtr_);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::EulerCoordinateRotation::transformTensor
(
	const tensorField& st,
	const labelList& cellMap
) const
{
	NotImplemented;
	return tmp<tensorField>(nullptr);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::EulerCoordinateRotation::
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


tnbLib::symmTensor tnbLib::EulerCoordinateRotation::transformVector
(
	const vector& st
) const
{
	return transformPrincipal(R_, st);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::EulerCoordinateRotation::calcTransform
(
	const scalar phiAngle,
	const scalar thetaAngle,
	const scalar psiAngle,
	const bool inDegrees
)
{
	scalar phi = phiAngle;
	scalar theta = thetaAngle;
	scalar psi = psiAngle;

	if (inDegrees)
	{
		phi *= constant::mathematical::pi / 180.0;
		theta *= constant::mathematical::pi / 180.0;
		psi *= constant::mathematical::pi / 180.0;
	}

	R_ =
		(
			tensor
			(
				cos(phi)*cos(psi) - sin(phi)*sin(psi)*cos(theta),
				-sin(phi)*cos(psi)*cos(theta) - cos(phi)*sin(psi),
				sin(phi)*sin(theta),

				cos(phi)*sin(psi)*cos(theta) + sin(phi)*cos(psi),
				cos(phi)*cos(psi)*cos(theta) - sin(phi)*sin(psi),
				-cos(phi)*sin(theta),

				sin(psi)*sin(theta),
				cos(psi)*sin(theta),
				cos(theta)
			)
			);

	Rtr_ = R_.T();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::EulerCoordinateRotation::EulerCoordinateRotation()
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{}


tnbLib::EulerCoordinateRotation::EulerCoordinateRotation
(
	const vector& phiThetaPsi,
	const bool inDegrees
)
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{
	calcTransform
	(
		phiThetaPsi.component(vector::X),
		phiThetaPsi.component(vector::Y),
		phiThetaPsi.component(vector::Z),
		inDegrees
	);
}


tnbLib::EulerCoordinateRotation::EulerCoordinateRotation
(
	const scalar phiAngle,
	const scalar thetaAngle,
	const scalar psiAngle,
	const bool inDegrees
)
	:
	R_(sphericalTensor::I),
	Rtr_(R_)
{
	calcTransform(phiAngle, thetaAngle, psiAngle, inDegrees);
}


tnbLib::EulerCoordinateRotation::EulerCoordinateRotation
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


tnbLib::EulerCoordinateRotation::EulerCoordinateRotation
(
	const dictionary& dict,
	const objectRegistry&
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


void tnbLib::EulerCoordinateRotation::write(Ostream& os) const
{
	writeEntry(os, "e1", e1());
	writeEntry(os, "e2", e2());
	writeEntry(os, "e3", e3());
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //