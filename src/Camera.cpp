#include <Camera.hpp>

Camera::Camera() :
    aspect(1.0f),
    fovy(45.0f/180.0f*M_PI),
    znear(0.1f),
    zfar(1000.0f),
    rotations(0.0, 0.0),
    translations(-4.0f, -0.7f, -27.0f),
    rfactor(0.005f),
    tfactor(0.05f),
    sfactor(0.005f),
    state(Camera::NOTHING)
{
}

Camera::~Camera()
{
	
}

void Camera::mouseReleased() {
    state = Camera::NOTHING;
}

void Camera::modifierReleased() {
    if (state != Camera::NOTHING) {
        state = Camera::ROTATE;
    }
}

void Camera::mouseClicked(int x, int y, bool shift, bool ctrl, bool alt)
{
    mousePrev << x, y;
    if(shift) {
        state = Camera::TRANSLATE;
    } else if(ctrl) {
        state = Camera::SCALE;
    } else {
        state = Camera::ROTATE;
    }
}

void Camera::mouseMoved(int x, int y)
{
    Eigen::Vector2f mouseCurr(x, y);
    Eigen::Vector2f dv = mouseCurr - mousePrev;
    switch(state) {
    case Camera::ROTATE:
        rotations += rfactor * dv;
        break;
    case Camera::TRANSLATE:
        translations(0) += tfactor * dv(0);
        translations(1) -= tfactor * dv(1);
        break;
    case Camera::SCALE:
        translations(2) *= (1.0f - sfactor * dv(1));
        break;
    }
    mousePrev = mouseCurr;
}

void Camera::applyProjectionMatrix(MatrixStack *P) const
{
    P->perspective(fovy, aspect, znear, zfar);
}

void Camera::applyViewMatrix(MatrixStack *MV) const
{
    MV->rotate(rotations(1), Eigen::Vector3f(1.0f, 0.0f, 0.0f));
    MV->rotate(rotations(0), Eigen::Vector3f(0.0f, 1.0f, 0.0f));
    MV->translate(translations);
}

void Camera::move(char c, const std::vector<Entity> &entities, const std::vector<Entity> &walls) {
    Eigen::Quaternionf q1;
    Eigen::Vector3f axis1(0.0f, 1.0f, 0.0f);
    q1 = Eigen::AngleAxisf(rotations(0), axis1); 
    Eigen::Matrix4f R1 = Eigen::Matrix4f::Identity();
    R1.block<3,3>(0,0) = q1.toRotationMatrix();
    Eigen::Vector3f last_valid_location = translations;
    
    if (c == 's') { //w
    	Eigen::Vector3f point(0.0f, 0.0f, 1.0f);
    	point = R1.block<3,3>(0,0) * point;
    	
        translations(0) += (point(0) * tfactor);       
        translations(2) -= (point(2) * tfactor);       
    }
    if (c == 'd') { //w
    	Eigen::Vector3f point(-1.0f, 0.0f, 0.0f);
    	point = R1.block<3,3>(0,0) * point;
    	
        translations(0) += (point(0) * tfactor);     
        translations(2) -= (point(2) * tfactor);         
    }
    if (c == 'w') {
    	Eigen::Vector3f point(0.0f, 0.0f, -1.0f);
    	point = R1.block<3,3>(0,0) * point;
    	
        translations(0) += (point(0) * tfactor);       
        translations(2) -= (point(2) * tfactor); 
    }
    if (c == 'a') {
    	Eigen::Vector3f point(1.0f, 0.0f, 0.0f);
    	point = R1.block<3,3>(0,0) * point;      
    	
        translations(0) += (point(0) * tfactor);     
        translations(2) -= (point(2) * tfactor);  
    }

    for (auto it = entities.begin(); it != entities.end(); it++) {
        if (this->collides(*it)) {
            translations = last_valid_location;
            return;
        }
    }

    for (auto it = walls.begin(); it != walls.end(); it++) {
        if (this->collides(*it)) {
            translations = last_valid_location;
            return;
        }
    }
}

static float sq(float x) {
    return x*x;
}

bool Camera::collides(const Entity &e) {
//    return false;
    float cam_rad = collisionRadius();

    if (e.useBoundingBox()) {
        //      return true;
        BoundingBox bb = e.getBoundingBox();
        bb.box.min += e.getPosition();
        bb.box.max += e.getPosition();
        Eigen::Vector3f our_pos = -translations;
        if (bb.contains(our_pos)) {
            return true;
        }

        Eigen::Vector3f displacement = (bb.box.center() - our_pos);
        float distance = displacement.norm();
        Eigen::Vector3f direction = displacement.normalized();
        /*
        if (sq(our_pos(0) - bb.box.min(0)) > sq(cam_rad)) {
            return true;
        }

        if (sq(our_pos(1) - bb.box.min(1)) > sq(cam_rad)) {
            return true;
        }

        if (sq(our_pos(2) - bb.box.min(2)) > sq(cam_rad)) {
            return true;
        }


        if (sq(our_pos(0) - bb.box.max(0)) > sq(cam_rad)) {
            return true;
        }

        if (sq(our_pos(1) - bb.box.max(1)) > sq(cam_rad)) {
            return true;
        }

        if (sq(our_pos(2) - bb.box.max(2)) > sq(cam_rad)) {
            return true;
        }
        */
        
        if (bb.contains(direction * cam_rad + our_pos)) {
            return true;
        }

        return false;
        
    }
    else {
        Eigen::Vector3f their_pos = e.getCenterWorld();
        Eigen::Vector3f our_pos = translations;
        their_pos(1) = 0;
        our_pos(1) = 0;
        Eigen::Vector3f delta = -their_pos - our_pos;
        return std::abs(delta.norm()) < cam_rad + e.getRadius();
    }
    
    
    /*
    std::cout << "object pos" << std::endl;
    std::cout << their_pos << std::endl;
    std::cout << "cam pos" << std::endl;
    std::cout << our_pos << std::endl;
    std::cout << " dist = " << std::abs(delta.norm()) << std::endl;
    */

    
}
