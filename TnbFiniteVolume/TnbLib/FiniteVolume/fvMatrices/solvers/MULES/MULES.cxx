#include <MULES.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::MULES::limitSum(UPtrList<scalarField>& phiPsiCorrs)
{
	forAll(phiPsiCorrs[0], facei)
	{
		scalar sumPos = 0;
		scalar sumNeg = 0;

		for (int phasei = 0; phasei < phiPsiCorrs.size(); phasei++)
		{
			if (phiPsiCorrs[phasei][facei] > 0)
			{
				sumPos += phiPsiCorrs[phasei][facei];
			}
			else
			{
				sumNeg += phiPsiCorrs[phasei][facei];
			}
		}

		scalar sum = sumPos + sumNeg;

		if (sum > 0 && sumPos > vSmall)
		{
			scalar lambda = -sumNeg / sumPos;

			for (int phasei = 0; phasei < phiPsiCorrs.size(); phasei++)
			{
				if (phiPsiCorrs[phasei][facei] > 0)
				{
					phiPsiCorrs[phasei][facei] *= lambda;
				}
			}
		}
		else if (sum < 0 && sumNeg < -vSmall)
		{
			scalar lambda = -sumPos / sumNeg;

			for (int phasei = 0; phasei < phiPsiCorrs.size(); phasei++)
			{
				if (phiPsiCorrs[phasei][facei] < 0)
				{
					phiPsiCorrs[phasei][facei] *= lambda;
				}
			}
		}
	}
}


void tnbLib::MULES::limitSum
(
	const UPtrList<const scalarField>& alphas,
	UPtrList<scalarField>& phiPsiCorrs,
	const labelHashSet& fixed
)
{
	labelHashSet notFixed(identity(phiPsiCorrs.size()));
	notFixed -= fixed;

	forAll(phiPsiCorrs[0], facei)
	{
		scalar alphaNotFixed = 0, corrNotFixed = 0;
		forAllConstIter(labelHashSet, notFixed, iter)
		{
			alphaNotFixed += alphas[iter.key()][facei];
			corrNotFixed += phiPsiCorrs[iter.key()][facei];
		}

		scalar corrFixed = 0;
		forAllConstIter(labelHashSet, fixed, iter)
		{
			corrFixed += phiPsiCorrs[iter.key()][facei];
		}

		const scalar sumCorr = corrNotFixed + corrFixed;

		const scalar lambda = -sumCorr / alphaNotFixed;

		forAllConstIter(labelHashSet, notFixed, iter)
		{
			phiPsiCorrs[iter.key()][facei] += lambda * alphas[iter.key()][facei];
		}
	}
}


// ************************************************************************* //