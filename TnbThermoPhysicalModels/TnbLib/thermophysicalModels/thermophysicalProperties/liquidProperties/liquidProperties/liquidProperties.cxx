#include <liquidProperties.hxx>

#include <HashTable.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(liquidProperties, 0);
	defineRunTimeSelectionTable(liquidProperties, );
	defineRunTimeSelectionTable(liquidProperties, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::liquidProperties::liquidProperties
(
	scalar W,
	scalar Tc,
	scalar Pc,
	scalar Vc,
	scalar Zc,
	scalar Tt,
	scalar Pt,
	scalar Tb,
	scalar dipm,
	scalar omega,
	scalar delta
)
	:
	thermophysicalProperties(W),
	Tc_(Tc),
	Pc_(Pc),
	Vc_(Vc),
	Zc_(Zc),
	Tt_(Tt),
	Pt_(Pt),
	Tb_(Tb),
	dipm_(dipm),
	omega_(omega),
	delta_(delta)
{}


tnbLib::liquidProperties::liquidProperties(const dictionary& dict)
	:
	thermophysicalProperties(dict),
	Tc_(readScalar(dict.lookup("Tc"))),
	Pc_(readScalar(dict.lookup("Pc"))),
	Vc_(readScalar(dict.lookup("Vc"))),
	Zc_(readScalar(dict.lookup("Zc"))),
	Tt_(readScalar(dict.lookup("Tt"))),
	Pt_(readScalar(dict.lookup("Pt"))),
	Tb_(readScalar(dict.lookup("Tb"))),
	dipm_(readScalar(dict.lookup("dipm"))),
	omega_(readScalar(dict.lookup("omega"))),
	delta_(readScalar(dict.lookup("delta")))
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::liquidProperties> tnbLib::liquidProperties::New
(
	const word& name
)
{
	if (debug)
	{
		InfoInFunction << "Constructing liquidProperties" << endl;
	}

	ConstructorTable::iterator cstrIter = ConstructorTablePtr_->find(name);

	if (cstrIter == ConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown liquidProperties type "
			<< name << nl << nl
			<< "Valid liquidProperties types are:" << nl
			<< ConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<liquidProperties>(cstrIter()());
}


tnbLib::autoPtr<tnbLib::liquidProperties> tnbLib::liquidProperties::New
(
	const dictionary& dict
)
{
	if (debug)
	{
		InfoInFunction << "Constructing liquidProperties" << endl;
	}

	const word& liquidPropertiesTypeName = dict.dictName();

	if (dict.found("defaultCoeffs"))
	{
		// Backward-compatibility

		if (Switch(dict.lookup("defaultCoeffs")))
		{
			return New(liquidPropertiesTypeName);
		}
		else
		{
			dictionaryConstructorTable::iterator cstrIter =
				dictionaryConstructorTablePtr_->find(liquidPropertiesTypeName);

			if (cstrIter == dictionaryConstructorTablePtr_->end())
			{
				FatalErrorInFunction
					<< "Unknown liquidProperties type "
					<< liquidPropertiesTypeName << nl << nl
					<< "Valid liquidProperties types are:" << nl
					<< dictionaryConstructorTablePtr_->sortedToc()
					<< exit(FatalError);
			}

			return autoPtr<liquidProperties>
				(
					cstrIter()
					(
						dict.optionalSubDict(liquidPropertiesTypeName + "Coeffs")
						)
					);
		}
	}
	else
	{
		dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(liquidPropertiesTypeName);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown liquidProperties type "
				<< liquidPropertiesTypeName << nl << nl
				<< "Valid liquidProperties types are:" << nl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<liquidProperties>(cstrIter()(dict));
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::liquidProperties::S(scalar p, scalar T) const
{
	NotImplemented;
	return 0;
}


tnbLib::scalar tnbLib::liquidProperties::pvInvert(scalar p) const
{
	// Check for critical and solid phase conditions
	if (p >= Pc_)
	{
		return Tc_;
	}
	else if (p < Pt_)
	{
		if (debug)
		{
			WarningInFunction
				<< "Pressure below triple point pressure: "
				<< "p = " << p << " < Pt = " << Pt_ << nl << endl;
		}
		return -1;
	}

	// Set initial upper and lower bounds
	scalar Thi = Tc_;
	scalar Tlo = Tt_;

	// Initialise T as boiling temperature under normal conditions
	scalar T = Tb_;

	while ((Thi - Tlo) > 1.0e-4)
	{
		if ((pv(p, T) - p) <= 0)
		{
			Tlo = T;
		}
		else
		{
			Thi = T;
		}

		T = (Thi + Tlo)*0.5;
	}

	return T;
}


void tnbLib::liquidProperties::readIfPresent(const dictionary &dict)
{
	thermophysicalProperties::readIfPresent(dict);
	dict.readIfPresent("Tc", Tc_);
	dict.readIfPresent("Pc", Pc_);
	dict.readIfPresent("Vc", Vc_);
	dict.readIfPresent("Zc", Zc_);
	dict.readIfPresent("Tt", Tt_);
	dict.readIfPresent("Pt", Pt_);
	dict.readIfPresent("Tb", Tb_);
	dict.readIfPresent("dipm", dipm_);
	dict.readIfPresent("omega", omega_);
	dict.readIfPresent("delta", delta_);
}


void tnbLib::liquidProperties::writeData(Ostream& os) const
{
	thermophysicalProperties::writeData(os);
	os << token::SPACE
		<< Tc_ << token::SPACE
		<< Pc_ << token::SPACE
		<< Vc_ << token::SPACE
		<< Zc_ << token::SPACE
		<< Tt_ << token::SPACE
		<< Pt_ << token::SPACE
		<< Tb_ << token::SPACE
		<< dipm_ << token::SPACE
		<< omega_ << token::SPACE
		<< delta_;
}


void tnbLib::liquidProperties::write(Ostream& os) const
{
	thermophysicalProperties::write(os);

	dictionary dict("liquidProperties");
	dict.add("Tc", Tc_);
	dict.add("Pc", Pc_);
	dict.add("Vc", Vc_);
	dict.add("Zc", Zc_);
	dict.add("Tt", Tt_);
	dict.add("Pt", Pt_);
	dict.add("Tb", Tb_);
	dict.add("dipm", dipm_);
	dict.add("omega", omega_);
	dict.add("delta", delta_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const liquidProperties& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //