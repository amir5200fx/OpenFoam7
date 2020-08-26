#include <VoidFraction.hxx>

// * * * * * * * * * * * * * Protectd Member Functions * * * * * * * * * * * //

template<class CloudType>
void tnbLib::VoidFraction<CloudType>::write()
{
	if (thetaPtr_.valid())
	{
		thetaPtr_->write();
	}
	else
	{
		FatalErrorInFunction
			<< "thetaPtr not valid" << abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::VoidFraction<CloudType>::VoidFraction
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	CloudFunctionObject<CloudType>(dict, owner, modelName, typeName),
	thetaPtr_(nullptr)
{}


template<class CloudType>
tnbLib::VoidFraction<CloudType>::VoidFraction
(
	const VoidFraction<CloudType>& vf
)
	:
	CloudFunctionObject<CloudType>(vf),
	thetaPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::VoidFraction<CloudType>::~VoidFraction()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::VoidFraction<CloudType>::preEvolve()
{
	if (thetaPtr_.valid())
	{
		thetaPtr_->primitiveFieldRef() = 0.0;
	}
	else
	{
		const fvMesh& mesh = this->owner().mesh();

		thetaPtr_.reset
		(
			new volScalarField
			(
				IOobject
				(
					this->owner().name() + "Theta",
					mesh.time().timeName(),
					mesh,
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				mesh,
				dimensionedScalar(dimless, 0)
			)
		);
	}
}


template<class CloudType>
void tnbLib::VoidFraction<CloudType>::postEvolve()
{
	volScalarField& theta = thetaPtr_();

	const fvMesh& mesh = this->owner().mesh();

	theta.primitiveFieldRef() /= mesh.time().deltaTValue()*mesh.V();

	CloudFunctionObject<CloudType>::postEvolve();
}


template<class CloudType>
void tnbLib::VoidFraction<CloudType>::postMove
(
	parcelType& p,
	const scalar dt,
	const point&,
	bool&
)
{
	volScalarField& theta = thetaPtr_();

	theta[p.cell()] += dt * p.nParticle()*p.volume();
}


// ************************************************************************* //