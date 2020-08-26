#include <ParticleStressModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ParticleStressModel, 0);
	defineRunTimeSelectionTable(ParticleStressModel, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ParticleStressModel::ParticleStressModel
(
	const dictionary& dict
)
	:
	alphaPacked_(readScalar(dict.lookup("alphaPacked")))
{
}


tnbLib::ParticleStressModel::ParticleStressModel
(
	const ParticleStressModel& cm
)
	:
	alphaPacked_(cm.alphaPacked_)
{
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::ParticleStressModel> tnbLib::ParticleStressModel::New
(
	const dictionary& dict
)
{
	word modelType(dict.lookup("type"));

	Info << "Selecting particle stress model " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown particle stress model type " << modelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid particle stress model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<ParticleStressModel>(cstrIter()(dict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ParticleStressModel::~ParticleStressModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::ParticleStressModel::alphaPacked() const
{
	return alphaPacked_;
}


tnbLib::tmp<tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>>
tnbLib::ParticleStressModel::tau
(
	const FieldField<Field, scalar>& alpha,
	const FieldField<Field, scalar>& rho,
	const FieldField<Field, scalar>& uRms
) const
{
	tmp<FieldField<Field, scalar>> value
	(
		new FieldField<Field, scalar>(alpha.size())
	);

	forAll(alpha, i)
	{
		value->set(i, tau(alpha[i], rho[i], uRms[i]));
	}

	return value;
}


// ************************************************************************* //