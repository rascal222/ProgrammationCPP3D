//
// Created by beugnon on 16/03/15.
//

#ifndef _PROGRAMMATION3D_TRANSFORM_HPP_
#define _PROGRAMMATION3D_TRANSFORM_HPP_

#include "../math/Vector3.hpp"
#include "../math/Quaternion.hpp"
#include <memory>
#include <list>

class Transform;

class Transform {
private:
    std::weak_ptr<Transform> parent;
    Vector3 position;
    Quaternion rotation;
    std::list<std::shared_ptr<Transform>> children;

public:
    static const std::shared_ptr<Transform> ROOT;

    Transform() : parent(ROOT) {
    };

    Transform(Vector3 &position) : parent(ROOT), position(position) {
    }

    Transform(Transform &parent) {
        parent = std::make_shared(parent);
    }
};

#endif //_PROGRAMMATION3D_TRANSFORM_HPP_
