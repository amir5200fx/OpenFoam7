#include <fvMesh.hxx>

#include <Time.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <slicedVolFields.hxx>
#include <slicedSurfaceFields.hxx>
#include <SubField.hxx>
#include <cyclicFvPatchFields.hxx>
#include <cyclicAMIFvPatchFields.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fvMesh::makeSf() const
{
	if (debug)
	{
		InfoInFunction << "Assembling face areas" << endl;
	}

	// It is an error to attempt to recalculate
	// if the pointer is already set
	if (SfPtr_)
	{
		FatalErrorInFunction
			<< "face areas already exist"
			<< abort(FatalError);
	}

	IOobject ioObj
	(
		"S",
		pointsInstance(),
		meshSubDir,
		*this,
		IOobject::NO_READ,
		IOobject::NO_WRITE,
		false
	);

	SfPtr_ = new slicedSurfaceVectorField
	(
		ioObj,
		*this,
		dimArea,
		faceAreas()
	);
}


void tnbLib::fvMesh::makeMagSf() const
{
	if (debug)
	{
		InfoInFunction << "Assembling mag face areas" << endl;
	}

	// It is an error to attempt to recalculate
	// if the pointer is already set
	if (magSfPtr_)
	{
		FatalErrorInFunction
			<< "mag face areas already exist"
			<< abort(FatalError);
	}

	// Note: Added stabilisation for faces with exactly zero area.
	// These should be caught on mesh checking but at least this stops
	// the code from producing Nans.

	IOobject ioObj
	(
		"magSf",
		pointsInstance(),
		meshSubDir,
		*this,
		IOobject::NO_READ,
		IOobject::NO_WRITE,
		false
	);

	magSfPtr_ = new surfaceScalarField
	(
		ioObj,
		mag(Sf()) + dimensionedScalar(dimArea, vSmall)
	);
}


void tnbLib::fvMesh::makeC() const
{
	if (debug)
	{
		InfoInFunction << "Assembling cell centres" << endl;
	}

	// It is an error to attempt to recalculate
	// if the pointer is already set
	if (CPtr_)
	{
		FatalErrorInFunction
			<< "cell centres already exist"
			<< abort(FatalError);
	}

	// Construct as slices. Only preserve processor (not e.g. cyclic)
	IOobject ioObj
	(
		"C",
		pointsInstance(),
		meshSubDir,
		*this,
		IOobject::NO_READ,
		IOobject::NO_WRITE,
		false
	);

	CPtr_ = new slicedVolVectorField
	(
		ioObj,
		*this,
		dimLength,
		cellCentres(),
		faceCentres(),
		true,               // preserveCouples
		true                // preserveProcOnly
	);
}


void tnbLib::fvMesh::makeCf() const
{
	if (debug)
	{
		InfoInFunction << "Assembling face centres" << endl;
	}

	// It is an error to attempt to recalculate
	// if the pointer is already set
	if (CfPtr_)
	{
		FatalErrorInFunction
			<< "face centres already exist"
			<< abort(FatalError);
	}

	IOobject ioObj
	(
		"Cf",
		pointsInstance(),
		meshSubDir,
		*this,
		IOobject::NO_READ,
		IOobject::NO_WRITE,
		false
	);

	CfPtr_ = new slicedSurfaceVectorField
	(
		ioObj,
		*this,
		dimLength,
		faceCentres()
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::volScalarField::Internal& tnbLib::fvMesh::V() const
{
	if (!VPtr_)
	{
		if (debug)
		{
			InfoInFunction
				<< "Constructing from primitiveMesh::cellVolumes()" << endl;
		}

		IOobject ioObj
		(
			"V",
			time().timeName(),
			*this,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		);

		VPtr_ = new slicedVolScalarField::Internal
		(
			ioObj,
			*this,
			dimVolume,
			cellVolumes()
		);
	}

	return *static_cast<slicedVolScalarField::Internal*>(VPtr_);
}


const tnbLib::volScalarField::Internal& tnbLib::fvMesh::V0() const
{
	if (!V0Ptr_)
	{
		FatalErrorInFunction
			<< "V0 is not available"
			<< abort(FatalError);
	}

	return *V0Ptr_;
}


tnbLib::volScalarField::Internal& tnbLib::fvMesh::setV0()
{
	if (!V0Ptr_)
	{
		FatalErrorInFunction
			<< "V0 is not available"
			<< abort(FatalError);
	}

	return *V0Ptr_;
}


const tnbLib::volScalarField::Internal& tnbLib::fvMesh::V00() const
{
	if (!V00Ptr_)
	{
		if (debug)
		{
			InfoInFunction << "Constructing from V0" << endl;
		}

		IOobject ioObj
		(
			"V00",
			time().timeName(),
			*this,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		);

		V00Ptr_ = new DimensionedField<scalar, volMesh>
			(
				ioObj,
				V0()
				);
	}

	return *V00Ptr_;
}


tnbLib::tmp<tnbLib::volScalarField::Internal>
tnbLib::fvMesh::Vsc() const
{
	if (moving() && time().subCycling())
	{
		const TimeState& ts = time();
		const TimeState& ts0 = time().prevTimeState();

		scalar tFrac =
			(
				ts.value() - (ts0.value() - ts0.deltaTValue())
				) / ts0.deltaTValue();

		if (tFrac < (1 - small))
		{
			return V0() + tFrac * (V() - V0());
		}
		else
		{
			return V();
		}
	}
	else
	{
		return V();
	}
}


tnbLib::tmp<tnbLib::volScalarField::Internal>
tnbLib::fvMesh::Vsc0() const
{
	if (moving() && time().subCycling())
	{
		const TimeState& ts = time();
		const TimeState& ts0 = time().prevTimeState();

		scalar t0Frac =
			(
			(ts.value() - ts.deltaTValue())
				- (ts0.value() - ts0.deltaTValue())
				) / ts0.deltaTValue();

		if (t0Frac > small)
		{
			return V0() + t0Frac * (V() - V0());
		}
		else
		{
			return V0();
		}
	}
	else
	{
		return V0();
	}
}


const tnbLib::surfaceVectorField& tnbLib::fvMesh::Sf() const
{
	if (!SfPtr_)
	{
		makeSf();
	}

	return *SfPtr_;
}


const tnbLib::surfaceScalarField& tnbLib::fvMesh::magSf() const
{
	if (!magSfPtr_)
	{
		makeMagSf();
	}

	return *magSfPtr_;
}


const tnbLib::volVectorField& tnbLib::fvMesh::C() const
{
	if (!CPtr_)
	{
		makeC();
	}

	return *CPtr_;
}


const tnbLib::surfaceVectorField& tnbLib::fvMesh::Cf() const
{
	if (!CfPtr_)
	{
		makeCf();
	}

	return *CfPtr_;
}


tnbLib::tmp<tnbLib::surfaceVectorField> tnbLib::fvMesh::delta() const
{
	if (debug)
	{
		InfoInFunction << "Calculating face deltas" << endl;
	}

	tmp<surfaceVectorField> tdelta
	(
		surfaceVectorField::New
		(
			"delta",
			*this,
			dimLength
		)
	);
	surfaceVectorField& delta = tdelta.ref();

	const volVectorField& C = this->C();
	const labelUList& owner = this->owner();
	const labelUList& neighbour = this->neighbour();

	forAll(owner, facei)
	{
		delta[facei] = C[neighbour[facei]] - C[owner[facei]];
	}

	surfaceVectorField::Boundary& deltabf =
		delta.boundaryFieldRef();

	forAll(deltabf, patchi)
	{
		deltabf[patchi] = boundary()[patchi].delta();
	}

	return tdelta;
}


const tnbLib::surfaceScalarField& tnbLib::fvMesh::phi() const
{
	if (!phiPtr_)
	{
		FatalErrorInFunction
			<< "mesh flux field does not exist, is the mesh actually moving?"
			<< abort(FatalError);
	}

	// Set zero current time
	// mesh motion fluxes if the time has been incremented
	if (!time().subCycling() && phiPtr_->timeIndex() != time().timeIndex())
	{
		(*phiPtr_) = dimensionedScalar(dimVolume / dimTime, 0);
	}

	return *phiPtr_;
}


tnbLib::surfaceScalarField& tnbLib::fvMesh::setPhi()
{
	if (!phiPtr_)
	{
		FatalErrorInFunction
			<< "mesh flux field does not exist, is the mesh actually moving?"
			<< abort(FatalError);
	}

	return *phiPtr_;
}


// ************************************************************************* //