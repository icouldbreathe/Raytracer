#include "DielectricMaterial.h"

DielectricMaterial::DielectricMaterial(double indexOfRefraction)
    : m_ior(indexOfRefraction)
{
}

bool DielectricMaterial::scatter(const Ray &incidentRay,
                                 const HitRecord &record, Color &attenuation,
                                 Ray &scatteredRay) const
{
    attenuation            = Color(1.0, 1.0, 1.0);
    double refractionRatio = record.bFrontFace ? (1.0 / m_ior) : m_ior;

    Vec3 unitDirection = unitVector(incidentRay.direction());
    double cosTheta    = fmin(dot(-unitDirection, record.normal), 1.0);
    double sinTheta    = sqrt(1.0 - cosTheta * cosTheta);

    bool bCannotRefract = refractionRatio * sinTheta > 1.0;
    Vec3 direction;

    if (bCannotRefract ||
        reflectance(cosTheta, refractionRatio) > randomDouble())
    {
        direction = reflect(unitDirection, record.normal);
    }
    else
    {
        direction = refract(unitDirection, record.normal, refractionRatio);
    }

    scatteredRay = Ray(record.hitPoint, direction);
    return true;
}

double DielectricMaterial::reflectance(double cosine, double ref_idx)
{
    // Schlick's approximation for reflectance
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0      = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}