#pragma once
#ifndef _noiseFFT_Header
#define _noiseFFT_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::noiseFFT

Description
	FFT of the pressure field

SourceFiles
	noiseFFT.C

\*---------------------------------------------------------------------------*/

#include <RandomProcesses_Module.hxx>
#include <scalarField.hxx>
#include <graph.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class noiseFFT Declaration
	\*---------------------------------------------------------------------------*/

	class noiseFFT
		:
		public scalarField
	{
		// Private Data

			//- Time spacing of the raw data
		scalar deltat_;


	public:

		//- Reference pressure
		static FoamRandomProcesses_EXPORT scalar p0;


		// Constructors

			//- Construct from pressure field
		FoamRandomProcesses_EXPORT noiseFFT
		(
			const scalar deltat,
			const scalarField& pressure
		);

		//- Construct from Istream
		FoamRandomProcesses_EXPORT noiseFFT(Istream&);

		//- Construct from pressure field file name
		FoamRandomProcesses_EXPORT noiseFFT(const fileName& pFileName, const label skip = 0);


		// Member Functions

			//- Return the graph of p(t)
		FoamRandomProcesses_EXPORT graph pt() const;

		//- Return the nth window
		FoamRandomProcesses_EXPORT tmp<scalarField> window(const label N, const label n) const;

		//- Return the Hanning window function
		FoamRandomProcesses_EXPORT tmp<scalarField> Hanning(const label N) const;

		//- Return the fft of the given pressure data
		FoamRandomProcesses_EXPORT tmp<scalarField> Pf(const tmp<scalarField>& pn) const;

		//- Return the multi-window mean fft of the complete pressure data
		FoamRandomProcesses_EXPORT graph meanPf(const label N, const label nw) const;

		//- Return the multi-window RMS mean fft of the complete pressure data
		FoamRandomProcesses_EXPORT graph RMSmeanPf(const label N, const label nw) const;

		//- Return the narrow-band PFL (pressure-fluctuation level) spectrum
		FoamRandomProcesses_EXPORT graph Lf(const graph& gPf) const;

		//- Return the one-third-octave-band PFL spectrum
		//  starting at octave with mean frequency f1
		FoamRandomProcesses_EXPORT graph Ldelta(const graph& gLf, const scalar f1, const scalar fU) const;

		//- Return the one-third-octave-band pressure spectrum
		//  starting at octave with mean frequency f1
		FoamRandomProcesses_EXPORT graph Pdelta(const graph& gLf, const scalar f1, const scalar fU) const;

		//- Return the total PFL as the sum of Lf over all frequencies
		FoamRandomProcesses_EXPORT scalar Lsum(const graph& gLf) const;

		//- Convert the db into Pa
		FoamRandomProcesses_EXPORT scalar dbToPa(const scalar db) const;

		//- Convert the db-field into Pa
		FoamRandomProcesses_EXPORT tmp<scalarField> dbToPa(const tmp<scalarField>& db) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noiseFFT_Header
