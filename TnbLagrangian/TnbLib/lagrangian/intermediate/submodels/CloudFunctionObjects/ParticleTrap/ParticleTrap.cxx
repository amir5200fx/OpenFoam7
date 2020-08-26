#include <ParticleTrap.hxx>

#include <fvcGrad.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParticleTrap<CloudType>::ParticleTrap
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	CloudFunctionObject<CloudType>(dict, owner, modelName, typeName),
	alphaName_
	(
		this->coeffDict().template lookupOrDefault<word>("alpha", "alpha")
	),
	alphaPtr_(nullptr),
	gradAlphaPtr_(nullptr),
	threshold_(readScalar(this->coeffDict().lookup("threshold")))
{}


template<class CloudType>
tnbLib::ParticleTrap<CloudType>::ParticleTrap
(
	const ParticleTrap<CloudType>& pt
)
	:
	CloudFunctionObject<CloudType>(pt),
	alphaName_(pt.alphaName_),
	alphaPtr_(pt.alphaPtr_),
	gradAlphaPtr_(nullptr),
	threshold_(pt.threshold_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParticleTrap<CloudType>::~ParticleTrap()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ParticleTrap<CloudType>::preEvolve()
{
	if (alphaPtr_ == nullptr)
	{
		const fvMesh& mesh = this->owner().mesh();
		const volScalarField& alpha =
			mesh.lookupObject<volScalarField>(alphaName_);

		alphaPtr_ = &alpha;
	}

	if (gradAlphaPtr_.valid())
	{
		gradAlphaPtr_() == fvc::grad(*alphaPtr_);
	}
	else
	{
		gradAlphaPtr_.reset(new volVectorField(fvc::grad(*alphaPtr_)));
	}
}


template<class CloudType>
void tnbLib::ParticleTrap<CloudType>::postEvolve()
{
	gradAlphaPtr_.clear();
}


template<class CloudType>
void tnbLib::ParticleTrap<CloudType>::postMove
(
	parcelType& p,
	const scalar,
	const point&,
	bool&
)
{
	if (alphaPtr_->primitiveField()[p.cell()] < threshold_)
	{
		const vector& gradAlpha = gradAlphaPtr_()[p.cell()];
		vector nHat = gradAlpha / mag(gradAlpha);
		scalar nHatU = nHat & p.U();

		if (nHatU < 0)
		{
			p.U() -= 2 * nHat*nHatU;
		}
	}
}


// ************************************************************************* //