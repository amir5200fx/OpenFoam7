#include <Switch.hxx>

#include <dictionary.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* tnbLib::Switch::names[nSwitchType] =
{
	"false",
	"true",
	"off",
	"on",
	"no",
	"yes",
	"n",
	"y",
	"f",
	"t",
	"none",
	"any",
	"invalid"
};


// * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * * //

tnbLib::Switch::switchType tnbLib::Switch::asEnum
(
	const std::string& str,
	const bool allowInvalid
)
{
	for (switchType sw = switchType::False; sw < switchType::invalid; ++sw)
	{
		if (str == names[toInt(sw)])
		{
			// Handle aliases
			switch (sw)
			{
			case switchType::n:
			case switchType::none:
			{
				return switchType::no;
				break;
			}

			case switchType::y:
			case switchType::any:
			{
				return switchType::yes;
				break;
			}

			case switchType::f:
			{
				return switchType::False;
				break;
			}

			case switchType::t:
			{
				return switchType::True;
				break;
			}

			default:
			{
				return switchType(sw);
				break;
			}
			}
		}
	}

	if (!allowInvalid)
	{
		FatalErrorInFunction
			<< "unknown switch word " << str << nl
			<< abort(FatalError);
	}

	return switchType::invalid;
}


tnbLib::Switch tnbLib::Switch::lookupOrAddToDict
(
	const word& name,
	dictionary& dict,
	const Switch& defaultValue
)
{
	return dict.lookupOrAddDefault<Switch>(name, defaultValue);
}


// * * * * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * * //

bool tnbLib::Switch::valid() const
{
	return switch_ <= switchType::none;
}


const char* tnbLib::Switch::asText() const
{
	return names[toInt(switch_)];
}


bool tnbLib::Switch::readIfPresent(const word& name, const dictionary& dict)
{
	return dict.readIfPresent<Switch>(name, *this);
}


// ************************************************************************* //