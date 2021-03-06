// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef BELOSGL_PROJECTION_H
#define BELOSGL_PROJECTION_H

#include <glm/ext.hpp>
#include <vector>

namespace GLTools {

    class Projection {

    public:
        /**
         * @return The projection matrix
         */
        virtual glm::mat4 getMatrix() const = 0;

    };

    class PerspectiveProjection : public Projection {

    public:
        /**
         * Create a projection matrix
         * @param width The width of the screen
         * @param height The height of the screen
         * @param mNear Near parameter
         * @param mFar Far parameter
         */
        PerspectiveProjection(float angle = 70.0f, unsigned int width = 1, unsigned int height = 1, float mNear = 0.1f, float mFar = 1000.0f);

        /**
         * @return The projection matrix
         */
        glm::mat4 getMatrix() const override;

    private:
        glm::mat4 mProjectionMatrix;

    };

    class OrthographicProjection : public Projection {

    public:
        OrthographicProjection(float sceneRadius = 1);

        /**
         * @return The projection matrix
         */
        glm::mat4 getMatrix() const override;

    private:
        glm::mat4 mProjectionMatrix;

    };

}


#endif //BELOSGL_PROJECTION_H
