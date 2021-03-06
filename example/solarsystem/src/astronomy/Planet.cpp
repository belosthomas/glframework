//
// Created by thomas on 13/11/18.
//

#include "Planet.h"

#include <iostream>

Astronomy::Planet::Planet(const std::string &name, Astronomy::description_t description) : mName(name), mDescription(description) {
    mSystem = std::make_shared<Astronomy::System>();
    mMajor = description.aphelion;
    mMinor = description.perihelion;
}

std::string Astronomy::Planet::getName() {
    return mName;
}

float Astronomy::Planet::getDiameter() {
    return static_cast<float>(mDescription.diameter);
}

glm::vec2 Astronomy::Planet::getCenterDistance() {
    return glm::vec2(mMinor, mMajor);
}

bool Astronomy::Planet::hasSystem() {
    return true;
}

std::shared_ptr<Astronomy::System> Astronomy::Planet::getSystem() {
    return mSystem;
}

Astronomy::description_t Astronomy::Planet::getDescription() {
    return mDescription;
}

Astronomy::TimePath Astronomy::Planet::getTimePath(Astronomy::PathScale scale) {
    Astronomy::TimePath path;

    if (mDescription.rotationPeriod == 0) {
        path.rotation = Maths::make_CVariable(0.0f);
    } else {
        path.rotation = path.time * 100000.0f / mDescription.rotationPeriod;
    }

    if (mDescription.orbitalPeriod == 0) {
        path.x = Maths::make_CVariable(0.0f);
        path.y = Maths::make_CVariable(0.0f);
        path.z = Maths::make_CVariable(0.0f);
        return path;
    }

    Maths::Variable orbitalTime = path.time * 100000.0f / mDescription.orbitalPeriod;

    float h_radius = (mMajor + mMinor) / 2;
    float l_radius = h_radius * (1.0f - mDescription.orbitalEccentricity);
    // float l_radius = sqrt(h_radius * (1 - (mDescription.orbitalEccentricity * mDescription.orbitalEccentricity)));
    float shift =  (mMajor + mMinor) / 2 - mMinor;

    switch (scale.type) {
        case NORMAL:
            path.x = Maths::cosav(orbitalTime) * l_radius / NORMAL_SIZE_SCALE;
            path.z = (Maths::sinav(orbitalTime) * h_radius + shift) / NORMAL_SIZE_SCALE;
            path.y = (Maths::make_CVariable(0.0f));
            path.radius = Maths::make_CVariable(static_cast<float>(mDescription.diameter / (2.0f * NORMAL_SIZE_SCALE)));
            break;
        case LOG:
            path.x = Maths::cosav(orbitalTime) * sqrt(l_radius) / 1000.0f;
            path.z = Maths::sinav(orbitalTime) * sqrt(h_radius) / 1000.0f  + sqrt(shift) / 1000.0f;
            path.y = Maths::make_CVariable(0.0f);
            path.radius = Maths::make_CVariable(logf(static_cast<float>(mDescription.diameter / 2.0f) / LOG_RADIUS_SCALE));
            break;
        case LOGMUL:
            path.x = Maths::cosav(orbitalTime) * log(l_radius) * scale.param;
            path.z = Maths::sinav(orbitalTime) * log(h_radius) * scale.param + log(shift) / 4.0f;
            path.y = Maths::make_CVariable(0.0f);
            path.radius = Maths::make_CVariable(logf(static_cast<float>(mDescription.diameter / 2.0f) / LOG_RADIUS_SCALE)) * scale.param2;
            break;
        case INDEX:
            path.x = Maths::cosav(orbitalTime) * scale.param;
            path.z = Maths::sinav(orbitalTime) * scale.param;
            path.y = Maths::make_CVariable(0.0f);
            path.radius = Maths::make_CVariable(1.0f) * scale.param2;
            break;
    }

    return path;
}

Astronomy::AnglePath Astronomy::Planet::getAnglePath(Astronomy::PathScale scale) {
    Astronomy::AnglePath path;

    path.rotation = Maths::make_CVariable(0.0f);

    if (mDescription.orbitalPeriod == 0) {
        path.x = Maths::make_CVariable(0.0f);
        path.y = Maths::make_CVariable(0.0f);
        path.z = Maths::make_CVariable(0.0f);
        return path;
    }

    float h_radius = (mMajor + mMinor) / 2;
    float l_radius = h_radius * (1.0f - mDescription.orbitalEccentricity);
    // float l_radius = sqrt(h_radius * (1 - (mDescription.orbitalEccentricity * mDescription.orbitalEccentricity)));
    float shift =  (mMajor + mMinor) / 2 - mMinor;

    switch (scale.type) {
        case NORMAL:
            path.x = Maths::cosav(path.angle * M_PI * 2) * l_radius / NORMAL_SIZE_SCALE;
            path.z = (Maths::sinav(path.angle * M_PI * 2) * h_radius + shift) / NORMAL_SIZE_SCALE;
            path.y = Maths::make_CVariable(0.0f);
            path.radius = Maths::make_CVariable(static_cast<float>(mDescription.diameter / (2.0f * NORMAL_SIZE_SCALE)));
            break;
        case LOG:
            path.x = Maths::cosav(path.angle * M_PI * 2) * sqrt(l_radius) / 1000.0f;
            path.z = Maths::sinav(path.angle * M_PI * 2) * sqrt(h_radius) / 1000.0f + sqrt(shift) / 1000.0f;
            path.y = Maths::make_CVariable(0.0f);
            path.radius = Maths::make_CVariable(logf(static_cast<float>(mDescription.diameter / 2.0f) / LOG_RADIUS_SCALE));
            break;
        case LOGMUL:
            path.x = Maths::cosav(path.angle * M_PI * 2) * log(l_radius) * scale.param;
            path.z = Maths::sinav(path.angle * M_PI * 2) * log(h_radius) * scale.param + log(shift) / 4.0f;
            path.y = Maths::make_CVariable(0.0f);
            path.radius = Maths::make_CVariable(logf(static_cast<float>(mDescription.diameter / 2.0f) / LOG_RADIUS_SCALE)) * scale.param2;
            break;
        case INDEX:
            path.x = Maths::cosav(path.angle * M_PI * 2) * scale.param;
            path.z = Maths::sinav(path.angle * M_PI * 2) * scale.param;
            path.y = Maths::make_CVariable(0.0f);
            path.radius = Maths::make_CVariable(1.0f) * scale.param2;
            break;
    }

    return path;
}
