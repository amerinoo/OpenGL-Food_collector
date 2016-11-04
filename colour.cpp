/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "colour.h"

Color::Color(const GLfloat red, const GLfloat green, const GLfloat blue)
    : red(red), green(green), blue(blue){ }

const Color Colours::wall     = Color(0.0, 0.0, 1.0);
const Color Colours::corridor = Color(0.0, 0.0, 0.0);
const Color Colours::food     = Color(0.0, 1.0, 1.0);
const Color Colours::player   = Color(1.0, 1.0, 0.0);
const Color Colours::enemy    = Color(1.0, 0.0, 0.0);
