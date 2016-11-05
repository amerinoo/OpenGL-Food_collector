/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "color.h"

Color::Color(const GLfloat red, const GLfloat green, const GLfloat blue)
    : red(red), green(green), blue(blue){ }

const Color Colors::cell     = Color(1.0, 1.0, 1.0);
const Color Colors::wall     = Color(0.0, 0.0, 1.0);
const Color Colors::corridor = Color(0.0, 0.0, 0.0);
const Color Colors::food     = Color(0.0, 1.0, 1.0);
const Color Colors::agent    = Color(1.0, 1.0, 1.0);
const Color Colors::player   = Color(1.0, 1.0, 0.0);
const Color Colors::enemy    = Color(1.0, 0.0, 0.0);
const Color Colors::unknown  = Color(1.0, 1.0, 1.0);
