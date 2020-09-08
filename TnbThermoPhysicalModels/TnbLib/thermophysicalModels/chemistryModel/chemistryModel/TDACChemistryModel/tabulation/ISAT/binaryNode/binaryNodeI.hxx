#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
tnbLib::binaryNode<CompType, ThermoType>::binaryNode()
	:
	leafLeft_(nullptr),
	leafRight_(nullptr),
	nodeLeft_(nullptr),
	nodeRight_(nullptr),
	parent_(nullptr),
	nAdditionalEqns_(0)
{}


template<class CompType, class ThermoType>
tnbLib::binaryNode<CompType, ThermoType>::binaryNode
(
	chemPointISAT<CompType, ThermoType>* elementLeft,
	chemPointISAT<CompType, ThermoType>* elementRight,
	binaryNode<CompType, ThermoType>* parent
)
	:
	leafLeft_(elementLeft),
	leafRight_(elementRight),
	nodeLeft_(nullptr),
	nodeRight_(nullptr),
	parent_(parent),
	v_(elementLeft->completeSpaceSize(), 0)
{
	if (elementLeft->variableTimeStep())
	{
		nAdditionalEqns_ = 3;
	}
	else
	{
		nAdditionalEqns_ = 2;
	}

	calcV(elementLeft, elementRight, v_);
	a_ = calcA(elementLeft, elementRight);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
void tnbLib::binaryNode<CompType, ThermoType>::calcV
(
	chemPointISAT<CompType, ThermoType>*& elementLeft,
	chemPointISAT<CompType, ThermoType>*& elementRight,
	scalarField& v
)
{
	// LT is the transpose of the L matrix
	scalarSquareMatrix& LT = elementLeft->LT();
	bool mechReductionActive = elementLeft->chemistry().mechRed()->active();

	// Difference of composition in the full species domain
	scalarField phiDif(elementRight->phi() - elementLeft->phi());
	const scalarField& scaleFactor(elementLeft->scaleFactor());
	scalar epsTol = elementLeft->tolerance();

	// v = LT.T()*LT*phiDif
	for (label i = 0; i < elementLeft->completeSpaceSize(); i++)
	{
		label si = i;
		bool outOfIndexI = true;
		if (mechReductionActive)
		{
			if (i < elementLeft->completeSpaceSize() - nAdditionalEqns_)
			{
				si = elementLeft->completeToSimplifiedIndex()[i];
				outOfIndexI = (si == -1);
			}
			else // temperature and pressure
			{
				outOfIndexI = false;
				const label dif =
					i - (elementLeft->completeSpaceSize() - nAdditionalEqns_);
				si = elementLeft->nActiveSpecies() + dif;
			}
		}
		if (!mechReductionActive || (mechReductionActive && !(outOfIndexI)))
		{
			v[i] = 0;
			for (label j = 0; j < elementLeft->completeSpaceSize(); j++)
			{
				label sj = j;
				bool outOfIndexJ = true;
				if (mechReductionActive)
				{
					if (j < elementLeft->completeSpaceSize() - nAdditionalEqns_)
					{
						sj = elementLeft->completeToSimplifiedIndex()[j];
						outOfIndexJ = (sj == -1);
					}
					else
					{
						outOfIndexJ = false;
						const label dif =
							j
							- (
								elementLeft->completeSpaceSize()
								- nAdditionalEqns_
								);
						sj = elementLeft->nActiveSpecies() + dif;
					}
				}
				if
					(
						!mechReductionActive
						|| (mechReductionActive && !(outOfIndexJ))
						)
				{
					// Since L is a lower triangular matrix k=0->min(i, j)
					for (label k = 0; k <= min(si, sj); k++)
					{
						v[i] += LT(k, si)*LT(k, sj)*phiDif[j];
					}
				}
			}
		}
		else
		{
			// When it is an inactive species the diagonal element of LT is
			// 1/(scaleFactor*epsTol)
			v[i] = phiDif[i] / sqr(scaleFactor[i] * epsTol);
		}
	}
}


template<class CompType, class ThermoType>
tnbLib::scalar tnbLib::binaryNode<CompType, ThermoType>::calcA
(
	chemPointISAT<CompType, ThermoType>* elementLeft,
	chemPointISAT<CompType, ThermoType>* elementRight
)
{
	scalarField phih((elementLeft->phi() + elementRight->phi()) / 2);
	scalar a = 0;
	forAll(phih, i)
	{
		a += v_[i] * phih[i];
	}

	return a;
}


// ************************************************************************* //