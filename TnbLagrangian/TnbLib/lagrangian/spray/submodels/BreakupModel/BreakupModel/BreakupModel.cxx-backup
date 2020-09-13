#include <BreakupModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::BreakupModel<CloudType>::BreakupModel
(
	CloudType& owner
)
	:
	CloudSubModelBase<CloudType>(owner),
	solveOscillationEq_(false),
	y0_(0.0),
	yDot0_(0.0),
	TABComega_(0.0),
	TABCmu_(0.0),
	TABtwoWeCrit_(0.0)
{}


template<class CloudType>
tnbLib::BreakupModel<CloudType>::BreakupModel
(
	const BreakupModel<CloudType>& bum
)
	:
	CloudSubModelBase<CloudType>(bum),
	solveOscillationEq_(bum.solveOscillationEq_),
	y0_(bum.y0_),
	yDot0_(bum.yDot0_),
	TABComega_(bum.TABComega_),
	TABCmu_(bum.TABCmu_),
	TABtwoWeCrit_(bum.TABtwoWeCrit_)
{}


template<class CloudType>
tnbLib::BreakupModel<CloudType>::BreakupModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type,
	bool solveOscillationEq
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type),
	solveOscillationEq_(solveOscillationEq),
	y0_(this->coeffDict().template lookupOrDefault<scalar>("y0", 0.0)),
	yDot0_(this->coeffDict().template lookupOrDefault<scalar>("yDot0", 0.0)),
	TABComega_(8),
	TABCmu_(5),
	TABtwoWeCrit_(12)
{
	if (solveOscillationEq_ && dict.found("TABCoeffs"))
	{
		const dictionary coeffs(dict.subDict("TABCoeffs"));
		coeffs.lookup("Comega") >> TABComega_;
		coeffs.lookup("Cmu") >> TABCmu_;
		scalar WeCrit(readScalar(coeffs.lookup("WeCrit")));
		TABtwoWeCrit_ = 2 * WeCrit;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::BreakupModel<CloudType>::~BreakupModel()
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <BreakupModelNew.cxx>

// ************************************************************************* //