#pragma once
// * * * * * * * * * * * * * Protectd Member Functions * * * * * * * * * * * //

template<class CloudType>
tnbLib::label tnbLib::ParticleErosion<CloudType>::applyToPatch
(
	const label globalPatchi
) const
{
	forAll(patchIDs_, i)
	{
		if (patchIDs_[i] == globalPatchi)
		{
			return i;
		}
	}

	return -1;
}


template<class CloudType>
void tnbLib::ParticleErosion<CloudType>::write()
{
	if (QPtr_.valid())
	{
		QPtr_->write();
	}
	else
	{
		FatalErrorInFunction
			<< "QPtr not valid" << abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParticleErosion<CloudType>::ParticleErosion
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	CloudFunctionObject<CloudType>(dict, owner, modelName, typeName),
	QPtr_(nullptr),
	patchIDs_(),
	p_(readScalar(this->coeffDict().lookup("p"))),
	psi_(this->coeffDict().template lookupOrDefault<scalar>("psi", 2.0)),
	K_(this->coeffDict().template lookupOrDefault<scalar>("K", 2.0))
{
	const wordList allPatchNames = owner.mesh().boundaryMesh().names();
	wordList patchName(this->coeffDict().lookup("patches"));

	labelHashSet uniquePatchIDs;
	forAllReverse(patchName, i)
	{
		labelList patchIDs = findStrings(patchName[i], allPatchNames);

		if (patchIDs.empty())
		{
			WarningInFunction
				<< "Cannot find any patch names matching " << patchName[i]
				<< endl;
		}

		uniquePatchIDs.insert(patchIDs);
	}

	patchIDs_ = uniquePatchIDs.toc();

	// Trigger creation of the Q field
	preEvolve();
}


template<class CloudType>
tnbLib::ParticleErosion<CloudType>::ParticleErosion
(
	const ParticleErosion<CloudType>& pe
)
	:
	CloudFunctionObject<CloudType>(pe),
	QPtr_(nullptr),
	patchIDs_(pe.patchIDs_),
	p_(pe.p_),
	psi_(pe.psi_),
	K_(pe.K_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParticleErosion<CloudType>::~ParticleErosion()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ParticleErosion<CloudType>::preEvolve()
{
	if (QPtr_.valid())
	{
		QPtr_->primitiveFieldRef() = 0.0;
	}
	else
	{
		const fvMesh& mesh = this->owner().mesh();

		QPtr_.reset
		(
			new volScalarField
			(
				IOobject
				(
					this->owner().name() + ":Q",
					mesh.time().timeName(),
					mesh,
					IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				),
				mesh,
				dimensionedScalar(dimVolume, 0)
			)
		);
	}
}


template<class CloudType>
void tnbLib::ParticleErosion<CloudType>::postPatch
(
	const parcelType& p,
	const polyPatch& pp,
	bool&
)
{
	const label patchi = pp.index();
	const label localPatchi = applyToPatch(patchi);

	if (localPatchi != -1)
	{
		// Get patch data
		vector nw, Up;
		this->owner().patchData(p, pp, nw, Up);

		// Particle velocity relative to patch
		const vector& U = p.U() - Up;

		// Quick rejection if the particle is travelling away from the patch
		if ((nw & U) < 0)
		{
			return;
		}

		const scalar magU = mag(U);
		const vector UHat = U / magU;

		// Impact angle
		const scalar alpha = mathematical::pi / 2 - acos(nw & UHat);

		// Get the face value to accumulate into
		const label patchFacei = pp.whichFace(p.face());
		scalar& Q = QPtr_->boundaryFieldRef()[patchi][patchFacei];

		// Finnie's model
		const scalar coeff = p.nParticle()*p.mass()*sqr(magU) / (p_*psi_*K_);
		if (tan(alpha) < K_ / 6)
		{
			Q += coeff * (sin(2 * alpha) - 6 / K_ * sqr(sin(alpha)));
		}
		else
		{
			Q += coeff * (K_*sqr(cos(alpha)) / 6);
		}
	}
}


// ************************************************************************* //