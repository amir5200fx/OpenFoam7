#pragma once
#include <fvMatrices.hxx>
#include <volFields.hxx>
#include <DimensionedField.hxx>

tnbLib::tmp<tnbLib::DimensionedField<tnbLib::vector, tnbLib::volMesh>>
tnbLib::coalCloudList::UTrans() const
{
	tmp<volVectorField::Internal> tfld
	(
		volVectorField::Internal::New
		(
			"UTransEff",
			mesh_,
			dimensionedVector(dimMass*dimVelocity, Zero)
		)
	);

	volVectorField::Internal& fld = tfld.ref();

	forAll(*this, i)
	{
		fld += operator[](i).UTrans();
	}

	return tfld;
}


tnbLib::tmp<tnbLib::fvVectorMatrix> tnbLib::coalCloudList::SU
(
	volVectorField& U
) const
{
	tmp<fvVectorMatrix> tfvm(new fvVectorMatrix(U, dimForce));
	fvVectorMatrix& fvm = tfvm.ref();

	forAll(*this, i)
	{
		fvm += operator[](i).SU(U);
	}

	return tfvm;
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::coalCloudList::hsTrans() const
{
	tmp<volScalarField::Internal> tfld
	(
		volScalarField::Internal::New
		(
			"hsTransEff",
			mesh_,
			dimensionedScalar(dimEnergy, 0)
		)
	);

	volScalarField::Internal& fld = tfld.ref();

	forAll(*this, i)
	{
		fld += operator[](i).hsTrans();
	}

	return tfld;
}


tnbLib::tmp<tnbLib::fvScalarMatrix> tnbLib::coalCloudList::Sh
(
	volScalarField& hs
) const
{
	tmp<fvScalarMatrix> tfvm(new fvScalarMatrix(hs, dimEnergy / dimTime));
	fvScalarMatrix& fvm = tfvm.ref();

	forAll(*this, i)
	{
		fvm += operator[](i).Sh(hs);
	}

	return tfvm;
}


tnbLib::tmp<tnbLib::fvScalarMatrix> tnbLib::coalCloudList::SYi
(
	const label ii,
	volScalarField& Yi
) const
{
	tmp<fvScalarMatrix> tfvm(new fvScalarMatrix(Yi, dimMass / dimTime));
	fvScalarMatrix& fvm = tfvm.ref();

	forAll(*this, i)
	{
		fvm += operator[](i).SYi(ii, Yi);
	}

	return tfvm;
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::coalCloudList::rhoTrans() const
{
	tmp<volScalarField::Internal> tfld
	(
		volScalarField::Internal::New
		(
			"rhoTransEff",
			mesh_,
			dimensionedScalar(dimMass, 0)
		)
	);

	volScalarField::Internal& fld = tfld.ref();

	forAll(*this, i)
	{
		forAll(operator[](i).rhoTrans(), j)
		{
			fld += operator[](i).rhoTrans()[j];
		}
	}

	return tfld;
}




tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::coalCloudList::Srho() const
{
	tmp<volScalarField::Internal> tfld
	(
		volScalarField::Internal::New
		(
			"rhoTransEff",
			mesh_,
			dimensionedScalar(dimDensity / dimTime, 0)
		)
	);

	volScalarField::Internal& fld = tfld.ref();

	forAll(*this, i)
	{
		fld += operator[](i).Srho();
	}

	return tfld;
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::coalCloudList::Srho
(
	const label i
) const
{
	tmp<volScalarField::Internal> tfld
	(
		volScalarField::Internal::New
		(
			"rhoTransEff",
			mesh_,
			dimensionedScalar(dimDensity / dimTime, 0)
		)
	);

	volScalarField::Internal& fld = tfld.ref();

	forAll(*this, j)
	{
		fld += operator[](j).Srho(i);
	}

	return tfld;
}


tnbLib::tmp<tnbLib::fvScalarMatrix> tnbLib::coalCloudList::Srho
(
	volScalarField& rho
) const
{
	tmp<fvScalarMatrix> tfvm(new fvScalarMatrix(rho, dimMass / dimTime));
	fvScalarMatrix& fvm = tfvm.ref();

	forAll(*this, i)
	{
		fvm += operator[](i).Srho(rho);
	}

	return tfvm;
}


// ************************************************************************* //