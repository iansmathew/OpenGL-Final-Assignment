#pragma once

/*--- ALL INCLUDE FILES HERE ---*/
#include <iostream>
#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "SOIL.h"


/*--- ALL DEFINES HERE ---*/

//Window properites
#define WINDOW_INIT_WIDTH 800.0f;
#define WINDOW_INIT_HEIGHT 800.0f;

//Camera defines
const  glm::vec3 CAMERA_START_POS = glm::vec3(0.0f, 0.0f, 3.0f);
#define CAMERA_ASPECT_RATIO