#include <memory>

//
// Created by thomas on 11/14/18.
//

#include "ParametricDrawable.h"

GLTools::ParametricDrawable::ParametricDrawable(GLTools::AbstractVariable &x, GLTools::AbstractVariable &y,
                                                GLTools::AbstractVariable &z, GLTools::AbstractVariable &normX,
                                                GLTools::AbstractVariable &normY, GLTools::AbstractVariable &normZ,
                                                GLTools::SettableVariable &p1, GLTools::SettableVariable &p2,
                                                unsigned long resolution1, unsigned long resolution2) {

    std::vector<glm::vec3> vertexs, normals, textcoords;
    vertexs.resize(resolution1 * resolution2);
    normals.resize(resolution1 * resolution2);
    textcoords.resize(resolution1 * resolution2);

    for (int i = 0; i < resolution1; i++) {
        for (int j = 0; j < resolution2; j++) {

            p1.set(1.0f * (float)i / (float)(resolution1 - 1));
            p2.set(1.0f * (float)j / (float)(resolution2 - 1));

            vertexs[i + j * resolution1] = glm::vec3(x.get(), y.get(), z.get());
            normals[i + j * resolution1] = glm::vec3(normX.get(), normY.get(), normZ.get());
            textcoords[i + j * resolution1] = glm::vec3(x.get(), y.get(), z.get());

        }
    }

    mVertexBuffer = std::make_shared<ArrayBuffer>(vertexs);
    mNormalBuffer = std::make_shared<ArrayBuffer>(normals);
    mTextcoordBuffer = std::make_shared<ArrayBuffer>(textcoords);

    mVertexArrayObject.add(VERTEX_ID, mVertexBuffer);
    mVertexArrayObject.add(NORMAL_ID, mNormalBuffer);
    mVertexArrayObject.add(TEXTCOORD_ID, mTextcoordBuffer);

}


void GLTools::ParametricDrawable::render(const GLTools::Camera &camera) const {



}
