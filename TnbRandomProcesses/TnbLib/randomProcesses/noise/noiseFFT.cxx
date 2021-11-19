#include <noiseFFT.hxx>

#include <IFstream.hxx>
#include <DynamicField.hxx>
#include <fft.hxx>
#include <SubField.hxx>
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::noiseFFT::p0 = 2e-5;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::noiseFFT::noiseFFT
(
	const scalar deltat,
	const scalarField& pressure
)
	:
	scalarField(pressure),
	deltat_(deltat)
{}


tnbLib::noiseFFT::noiseFFT(const fileName& pFileName, const label skip)
	:
	scalarField(),
	deltat_(0.0)
{
	// Construct pressure data file
	IFstream pFile(pFileName);

	// Check pFile stream is OK
	if (!pFile.good())
	{
		FatalErrorInFunction
			<< "Cannot read file " << pFileName
			<< exit(FatalError);
	}

	if (skip)
	{
		scalar dummyt, dummyp;

		for (label i = 0; i < skip; i++)
		{
			pFile >> dummyt;

			if (!pFile.good() || pFile.eof())
			{
				FatalErrorInFunction
					<< "Number of points in file " << pFileName
					<< " is less than the number to be skipped = " << skip
					<< exit(FatalError);
			}

			pFile >> dummyp;
		}
	}

	scalar t = 0, T = 0;
	DynamicList<scalar> pData(100000);
	label i = 0;

	while (!(pFile >> t).eof())
	{
		T = t;
		pFile >> pData(i++);
	}

	deltat_ = T / pData.size();

	this->transfer(pData);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::graph tnbLib::noiseFFT::pt() const
{
	scalarField t(size());
	forAll(t, i)
	{
		t[i] = i * deltat_;
	}

	return graph
	(
		"p(t)",
		"t [s]",
		"p(t) [Pa]",
		t,
		*this
	);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::noiseFFT::window
(
	const label N,
	const label ni
) const
{
	label windowOffset = N;

	if ((N + ni * windowOffset) > size())
	{
		FatalErrorInFunction
			<< "Requested window is outside set of data" << endl
			<< "number of data = " << size() << endl
			<< "size of window = " << N << endl
			<< "window  = " << ni
			<< exit(FatalError);
	}

	tmp<scalarField> tpw(new scalarField(N));
	scalarField& pw = tpw.ref();

	label offset = ni * windowOffset;

	forAll(pw, i)
	{
		pw[i] = operator[](i + offset);
	}

	return tpw;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::noiseFFT::Hanning(const label N) const
{
	scalarField t(N);
	forAll(t, i)
	{
		t[i] = i * deltat_;
	}

	scalar T = N * deltat_;

	return 2 * (0.5 - 0.5*cos(constant::mathematical::twoPi*t / T));
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::noiseFFT::Pf
(
	const tmp<scalarField>& tpn
) const
{
	tmp<scalarField> tPn2
	(
		mag
		(
			fft::reverseTransform
			(
				ReComplexField(tpn),
				labelList(1, tpn().size())
			)
		)
	);

	tpn.clear();

	tmp<scalarField> tPn
	(
		new scalarField
		(
			scalarField::subField(tPn2(), tPn2().size() / 2)
		)
	);
	scalarField& Pn = tPn.ref();

	Pn *= 2.0 / sqrt(scalar(tPn2().size()));
	Pn[0] /= 2.0;

	return tPn;
}


tnbLib::graph tnbLib::noiseFFT::meanPf
(
	const label N,
	const label nw
) const
{
	if (N > size())
	{
		FatalErrorInFunction
			<< "Requested window is outside set of data" << nl
			<< "number of data = " << size() << nl
			<< "size of window = " << N << nl
			<< "window  = " << nw
			<< exit(FatalError);
	}

	scalarField MeanPf(N / 2, 0.0);

	scalarField Hwf(Hanning(N));

	for (label wi = 0; wi < nw; ++wi)
	{
		MeanPf += Pf(Hwf*window(N, wi));
	}

	MeanPf /= nw;

	scalarField f(MeanPf.size());
	scalar deltaf = 1.0 / (N*deltat_);

	forAll(f, i)
	{
		f[i] = i * deltaf;
	}

	return graph
	(
		"P(f)",
		"f [Hz]",
		"P(f) [Pa]",
		f,
		MeanPf
	);
}


tnbLib::graph tnbLib::noiseFFT::RMSmeanPf
(
	const label N,
	const label nw
) const
{
	if (N > size())
	{
		FatalErrorInFunction
			<< "Requested window is outside set of data" << endl
			<< "number of data = " << size() << endl
			<< "size of window = " << N << endl
			<< "window  = " << nw
			<< exit(FatalError);
	}

	scalarField RMSMeanPf(N / 2, 0.0);

	scalarField Hwf(Hanning(N));

	for (label wi = 0; wi < nw; ++wi)
	{
		RMSMeanPf += sqr(Pf(Hwf*window(N, wi)));
	}

	RMSMeanPf = sqrt(RMSMeanPf / nw);

	scalarField f(RMSMeanPf.size());
	scalar deltaf = 1.0 / (N*deltat_);

	forAll(f, i)
	{
		f[i] = i * deltaf;
	}

	return graph
	(
		"P(f)",
		"f [Hz]",
		"P(f) [Pa]",
		f,
		RMSMeanPf
	);
}


tnbLib::graph tnbLib::noiseFFT::Lf(const graph& gPf) const
{
	return graph
	(
		"L(f)",
		"f [Hz]",
		"L(f) [dB]",
		gPf.x(),
		20 * log10(gPf.y() / p0)
	);
}


tnbLib::graph tnbLib::noiseFFT::Ldelta
(
	const graph& gLf,
	const scalar f1,
	const scalar fU
) const
{
	const scalarField& f = gLf.x();
	const scalarField& Lf = gLf.y();

	scalarField ldelta(Lf.size(), 0.0);
	scalarField fm(ldelta.size());

	scalar fratio = cbrt(2.0);
	scalar deltaf = 1.0 / (2 * Lf.size()*deltat_);

	scalar fl = f1 / sqrt(fratio);
	scalar fu = fratio * fl;

	label istart = label(fl / deltaf);
	label j = 0;

	for (label i = istart; i < Lf.size(); i++)
	{
		scalar fmi = sqrt(fu*fl);

		if (fmi > fU + 1) break;

		if (f[i] >= fu)
		{
			fm[j] = fmi;
			ldelta[j] = 10 * log10(ldelta[j]);

			j++;

			fl = fu;
			fu *= fratio;
		}

		ldelta[j] += pow(10, Lf[i] / 10.0);
	}

	fm.setSize(j);
	ldelta.setSize(j);

	return graph
	(
		"Ldelta",
		"fm [Hz]",
		"Ldelta [dB]",
		fm,
		ldelta
	);
}


tnbLib::graph tnbLib::noiseFFT::Pdelta
(
	const graph& gPf,
	const scalar f1,
	const scalar fU
) const
{
	const scalarField& f = gPf.x();
	const scalarField& Pf = gPf.y();

	scalarField pdelta(Pf.size(), 0.0);
	scalarField fm(pdelta.size());

	scalar fratio = cbrt(2.0);
	scalar deltaf = 1.0 / (2 * Pf.size()*deltat_);

	scalar fl = f1 / sqrt(fratio);
	scalar fu = fratio * fl;

	label istart = label(fl / deltaf + 1.0 - small);
	label j = 0;

	for (label i = istart; i < Pf.size(); i++)
	{
		scalar fmi = sqrt(fu*fl);

		if (fmi > fU + 1) break;

		if (f[i] >= fu)
		{
			fm[j] = fmi;
			pdelta[j] = sqrt((2.0 / 3.0)*pdelta[j]);

			j++;

			fl = fu;
			fu *= fratio;
		}

		pdelta[j] += sqr(Pf[i]);
	}

	fm.setSize(j);
	pdelta.setSize(j);

	return graph
	(
		"Pdelta",
		"fm [Hz]",
		"Pdelta [dB]",
		fm,
		pdelta
	);
}


tnbLib::scalar tnbLib::noiseFFT::Lsum(const graph& gLf) const
{
	const scalarField& Lf = gLf.y();

	scalar lsum = 0.0;

	forAll(Lf, i)
	{
		lsum += pow(10, Lf[i] / 10.0);
	}

	lsum = 10 * log10(lsum);

	return lsum;
}


tnbLib::scalar tnbLib::noiseFFT::dbToPa(const scalar db) const
{
	return p0 * pow(10.0, db / 20.0);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::noiseFFT::dbToPa
(
	const tmp<scalarField>& db
) const
{
	return p0 * pow(10.0, db / 20.0);
}


// ************************************************************************* //