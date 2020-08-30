#pragma once
#ifndef _makeThermoParcelSurfaceFilmModels_Header
#define _makeThermoParcelSurfaceFilmModels_Header

#include <NoSurfaceFilm.hxx>
#include <ThermoSurfaceFilm.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeParcelSurfaceFilmModels(CloudType)                                 \
                                                                               \
    makeSurfaceFilmModel(CloudType);                                           \
                                                                               \
    makeSurfaceFilmModelType(NoSurfaceFilm, CloudType);                        \
    makeSurfaceFilmModelType(ThermoSurfaceFilm, CloudType);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_makeThermoParcelSurfaceFilmModels_Header
