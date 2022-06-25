#pragma once

#include "Material.h"

class LambertianDiffuseMaterial : public Material
{
  public:
    LambertianDiffuseMaterial(const Color &color) : m_albedo(color)
    {
    }

    virtual bool scatter(const Ray &incomingRay, const HitRecord &record,
                         Color &attenuation, Ray &scatteredRay) const override
    {
        auto scatterDirection = record.normal + randomUnitVector();
        scatteredRay = Ray(record.hitPoint, scatterDirection);
        attenuation = m_albedo;
        return true;
    }

  public:
    Color m_albedo;
};