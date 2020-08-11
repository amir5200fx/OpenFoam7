#include <specieCoeffs.hxx>

#include <DynamicList.hxx>
#include <OStringStream.hxx>

#include <Istream.hxx>  // added by amir
#include <token.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::specieCoeffs::specieCoeffs
(
	const speciesTable& species,
	Istream& is
)
{
	token t(is);
	if (t.isNumber())
	{
		stoichCoeff = t.number();
		is >> t;
	}
	else
	{
		stoichCoeff = 1;
	}

	exponent = stoichCoeff;

	if (t.isWord())
	{
		word specieName = t.wordToken();

		size_t i = specieName.find('^');

		if (i != word::npos)
		{
			string exponentStr = specieName
			(
				i + 1,
				specieName.size() - i - 1
			);
			exponent = atof(exponentStr.c_str());
			specieName = specieName(0, i);
		}

		if (species.contains(specieName))
		{
			index = species[specieName];
		}
		else
		{
			// In order to support the convoluted way in which
			// the solidChemistry currently handles gaseous species
			// an error cannot be generated here.
			// We will re-introduce this check after solidChemistry is
			// re-written in a rational manner.
			// FatalIOErrorInFunction(is)
			//     << "Specie " << specieName
			//     << " not found in table " << species
			//     << exit(FatalIOError);

			index = -1;
		}
	}
	else
	{
		FatalIOErrorInFunction(is)
			<< "Expected a word but found " << t.info()
			<< exit(FatalIOError);
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::specieCoeffs::setLRhs
(
	Istream& is,
	const speciesTable& species,
	List<specieCoeffs>& lhs,
	List<specieCoeffs>& rhs
)
{
	DynamicList<specieCoeffs> dlrhs;

	while (is.good())
	{
		dlrhs.append(specieCoeffs(species, is));

		if (dlrhs.last().index != -1)
		{
			token t(is);
			if (t.isPunctuation())
			{
				if (t == token::ADD)
				{
				}
				else if (t == token::ASSIGN)
				{
					lhs = dlrhs.shrink();
					dlrhs.clear();
				}
				else
				{
					rhs = dlrhs.shrink();
					is.putBack(t);
					return;
				}
			}
			else
			{
				rhs = dlrhs.shrink();
				is.putBack(t);
				return;
			}
		}
		else
		{
			dlrhs.remove();
			if (is.good())
			{
				token t(is);
				if (t.isPunctuation())
				{
					if (t == token::ADD)
					{
					}
					else if (t == token::ASSIGN)
					{
						lhs = dlrhs.shrink();
						dlrhs.clear();
					}
					else
					{
						rhs = dlrhs.shrink();
						is.putBack(t);
						return;
					}
				}
			}
			else
			{
				if (!dlrhs.empty())
				{
					rhs = dlrhs.shrink();
				}
				return;
			}
		}
	}

	FatalIOErrorInFunction(is)
		<< "Cannot continue reading reaction data from stream"
		<< exit(FatalIOError);
}


void tnbLib::specieCoeffs::reactionStr
(
	OStringStream& reaction,
	const speciesTable& species,
	const List<specieCoeffs>& scs
)
{
	for (label i = 0; i < scs.size(); ++i)
	{
		if (i > 0)
		{
			reaction << " + ";
		}
		if (mag(scs[i].stoichCoeff - 1) > small)
		{
			reaction << scs[i].stoichCoeff;
		}
		reaction << species[scs[i].index];
		if (mag(scs[i].exponent - scs[i].stoichCoeff) > small)
		{
			reaction << "^" << scs[i].exponent;
		}
	}
}


tnbLib::string tnbLib::specieCoeffs::reactionStr
(
	OStringStream& reaction,
	const speciesTable& species,
	const List<specieCoeffs>& lhs,
	const List<specieCoeffs>& rhs
)
{
	reactionStr(reaction, species, lhs);
	reaction << " = ";
	reactionStr(reaction, species, rhs);
	return reaction.str();
}


// ************************************************************************* //