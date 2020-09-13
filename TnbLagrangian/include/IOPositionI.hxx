#pragma once
#include <polyMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::IOPosition<CloudType>::IOPosition(const CloudType& c)
	:
	regIOobject
	(
		IOobject
		(
			"positions",
			c.time().timeName(),
			c,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	),
	cloud_(c)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::IOPosition<CloudType>::write(const bool write) const
{
	return regIOobject::write(cloud_.size());
}


template<class CloudType>
bool tnbLib::IOPosition<CloudType>::writeData(Ostream& os) const
{
	os << cloud_.size() << nl << token::BEGIN_LIST << nl;

	forAllConstIter(typename CloudType, cloud_, iter)
	{
		iter().writePosition(os);
		os << nl;
	}

	os << token::END_LIST << endl;

	return os.good();
}


template<class CloudType>
void tnbLib::IOPosition<CloudType>::readData(Istream& is, CloudType& c)
{
	const polyMesh& mesh = c.pMesh();

	token firstToken(is);

	if (firstToken.isLabel())
	{
		label s = firstToken.labelToken();

		// Read beginning of contents
		is.readBeginList
		(
			"IOPosition<CloudType>::readData(Istream&, CloudType&)"
		);

		for (label i = 0; i < s; i++)
		{
			// Read position only
			c.append(new typename CloudType::particleType(mesh, is, false));
		}

		// Read end of contents
		is.readEndList("IOPosition<CloudType>::readData(Istream&, CloudType&)");
	}
	else if (firstToken.isPunctuation())
	{
		if (firstToken.pToken() != token::BEGIN_LIST)
		{
			FatalIOErrorInFunction
			(
				is
			) << "incorrect first token, '(', found "
				<< firstToken.info() << exit(FatalIOError);
		}

		token lastToken(is);
		while
			(
				!(
					lastToken.isPunctuation()
					&& lastToken.pToken() == token::END_LIST
					)
				)
		{
			is.putBack(lastToken);

			// Read position only
			c.append(new typename CloudType::particleType(mesh, is, false));
			is >> lastToken;
		}
	}
	else
	{
		FatalIOErrorInFunction
		(
			is
		) << "incorrect first token, expected <int> or '(', found "
			<< firstToken.info() << exit(FatalIOError);
	}

	// Check state of IOstream
	is.check
	(
		"void IOPosition<CloudType>::readData(Istream&, CloudType&)"
	);
}


// ************************************************************************* //