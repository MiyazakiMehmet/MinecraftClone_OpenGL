#include <iostream>
#include <math.h>

typedef struct {
	float x, y;
} vector2;

//By using "Hashing", it generates random angle according to the grid coordinates. This way, we don't need to precompute gradients and store them in a table.
vector2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

//It calculates how far our point is from the grid point, and then computes the dot product of the distance vector and the gradient vector to calculate angle between them.
float dotGridGradient(int ix, int iy, float x, float y) {
	//Get gradient from integer coordinates
	vector2 gradient = randomGradient(ix, iy);

    //Compute the Distance Vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    //Compute the dot-product
    //If dx closer to gradient, it will have higher value, and if it's farther, it will have lower value.
    //This is what creates the "noise" effect. And by multiplying the distance vector with the gradient, we determine whether the noise value will be positive or negative, and how strong it will be. If the distance vector is in the same direction as the gradient,
    //it will contribute positively to the noise value, and if it's in the opposite direction, it will contribute negatively.
	return (dx * gradient.x + dy * gradient.y); 
}

float interpolate(float a0, float a1, float w) {
	//Cubic Interpolation (smoothstep)
    //Instead of using linear interpolation, we use cubic interpolation to smooth the transitions between grid points. 
    //This helps to create a more natural and visually appealing noise pattern.
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float perlin(float x, float y) {
	
	//Determine grid cell coordinates
	int x0 = (int)x;
	int y0 = (int)y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	//Compute interpolation weights
	float sx = x - (float)x0;
	float sy = y - (float)y0;

    //Compute and Interpolate bottom two corners
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

	//Compute and Interpolate top two corners
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

	//Final Interpolation: Interpolate the two results along y to get the final noise value.
    float value = interpolate(ix0, ix1, sy);

    return value;
}

// Perlin with octaves (fractal noise/brownian motion). Returns value approximately in same range as perlin (roughly -1..1).
float perlinOctaves(float x, float y, int octaves = 4, float persistence = 0.5f, float lacunarity = 2.0f, float baseFreq = 1.0f) {
    float total = 0.0f;
    float amplitude = 1.0f;
    float frequency = baseFreq;
    float maxAmplitude = 0.0f;

    for (int i = 0; i < octaves; ++i) {
        total += perlin(x * frequency, y * frequency) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= persistence;
        frequency *= lacunarity;
    }

    if (maxAmplitude == 0.0f) return 0.0f;
	return total / maxAmplitude; // normalized to approx [-1,1] (Normalizezed to ensure the output remains within a consistent range)
}