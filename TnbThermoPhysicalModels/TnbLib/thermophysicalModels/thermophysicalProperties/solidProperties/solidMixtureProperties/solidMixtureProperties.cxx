#include <solidMixtureProperties.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidMixtureProperties::solidMixtureProperties(const dictionary& dict)
	:
	components_(),
	properties_()
{
	components_ = dict.toc();
	properties_.setSize(components_.size());

	forAll(components_, i)
	{
		if (dict.isDict(components_[i]))
		{
			properties_.set
			(
				i,
				solidProperties::New(dict.subDict(components_[i]))
			);
		}
		else
		{
			properties_.set
			(
				i,
				solidProperties::New(components_[i])
			);
		}
	}
}


tnbLib::solidMixtureProperties::solidMixtureProperties
(
	const solidMixtureProperties& s
)
	:
	components_(s.components_),
	properties_(s.properties_.size())
{
	forAll(properties_, i)
	{
		properties_.set(i, s.properties_(i)->clone());
	}
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::solidMixtureProperties> tnbLib::solidMixtureProperties::New
(
	const dictionary& thermophysicalProperties
)
{
	return autoPtr<solidMixtureProperties>
		(
			new solidMixtureProperties(thermophysicalProperties)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::solidMixtureProperties::rho(const scalarField& Y) const
{
	scalar rrho = 0;

	forAll(properties_, i)
	{
		rrho += Y[i] / properties_[i].rho();
	}

	return 1 / rrho;
}


tnbLib::scalar tnbLib::solidMixtureProperties::Cp(const scalarField& Y) const
{
	scalar Cp = 0;

	forAll(properties_, i)
	{
		Cp += Y[i] * properties_[i].Cp();
	}

	return Cp;
}


// ************************************************************************* //