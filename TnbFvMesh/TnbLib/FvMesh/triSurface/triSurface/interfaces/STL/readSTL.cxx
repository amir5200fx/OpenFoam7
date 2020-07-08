#include <triSurface.hxx>

#include <IFstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	bool triSurface::readSTL(const fileName& STLfileName)
	{
		token firstToken;
		{
			IFstream str(STLfileName);

			if (!str.good())
			{
				return false;
			}
			firstToken = token(str);
		}

		if (firstToken.isWord())
		{
			word firstWord(firstToken.wordToken());

			for (size_t i = 0; i < firstWord.size(); i++)
			{
				firstWord[i] = std::toupper(firstWord[i]);
			}

			if (firstWord == "SOLID" || firstWord(5) == "SOLID")
			{
				return readSTLASCII(STLfileName);
			}
		}

		return readSTLBINARY(STLfileName);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //