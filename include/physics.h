#ifndef  PHYSICS_H
#define  PHYSICS_H

#include "model/model.h"
#include <memory>
#include<vector>
#include<math.h>


class Physictype 
{
public:
	Physictype(std::shared_ptr<Model> modelptrs, float mass = 1, glm::vec3 acceleration = glm::vec3(0., 0., 0.), glm::vec3 velocity = glm::vec3(0., 0., 0.), bool crush = false, float radius = 1.0, float crush_index = 0.5);

	void setCrush(const bool);
	void setRadius(const float);
	void setMass(const float);
	void setCrushIndex(const float);
	void setAcceleration(const glm::vec3);
	void setVelocity(const glm::vec3);

	float getRadius() const;
	float getMass() const;
	float getCrushIndex() const;
	bool getCrush() const;
	glm::vec3 getAcceleration() const;
	glm::vec3 getVelocity() const;
	std::shared_ptr<Model> modelptr;
private:
	float _mass ;
	glm::vec3 _acceleration;
	glm::vec3 _velocity;
	bool _crush;
	float _radius;
	float _crush_index ;
};

class Gravity
{
public:
	using PhysictypePtr = std::shared_ptr<Physictype>;

	void get_in_gravity(PhysictypePtr new_one);
	void get_in_gravity(std::vector<PhysictypePtr> new_one);
	void update_acc();
	void update_velocity();
	void update_position();

	void set_constance(float constance);
	void set_step_time(float step_time);
	float get_constance();
	float get_step_time();
private:
	std::vector<PhysictypePtr> GravityCollection;
	float GRAVITY_CONST = 8;
	float STEP_TIME = 0.01;
};

class CrushCheck
{
public:
	using PhysictypePtr = std::shared_ptr<Physictype>;
	void get_in_crushcheck(PhysictypePtr new_one);
	void get_in_crushcheck(std::vector<PhysictypePtr>  new_one);
	void update_crush();
	
private:
	std::vector<PhysictypePtr> CrushCheckCollection;
	void update_position(PhysictypePtr, PhysictypePtr, glm::vec3, glm::vec3);
	void update_acc();
	void update_velocity();
	float STEP_TIME = 0.01;
};

//class CrushCheck
//{
//public:
//	using PhysictypePtr = std::shared_ptr<Physictype>;
//	void get_in_crushcheck(PhysictypePtr new_one);
//	void update_crush();
//
//private:
//	std::vector<PhysictypePtr> CrushCheckCollection;
//
//	void update_position(PhysictypePtr, PhysictypePtr, glm::vec3, glm::vec3);
//	void update_acc();
//	void update_velocity();
//	float STEP_TIME = 0.01;
//};




#endif