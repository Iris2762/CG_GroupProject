#include "physics.h"

Physictype::Physictype(std::shared_ptr<Model> modelptrs,float mass, glm::vec3 acceleration, glm::vec3 velocity , bool crush , float radius, float crush_index ):_mass(mass),_acceleration(acceleration), _velocity(velocity),_crush(crush),_radius(radius),_crush_index(crush_index),modelptr(modelptrs){

};

void Physictype::setMass(const float mass) {
	this->_mass = mass;
}

void Physictype::setCrushIndex(const float crush_index) {
	this->_crush_index = crush_index;
}

void Physictype::setRadius(const float radius) {
	this->_radius = radius;
}


void Physictype::setCrush(const bool crush) {
	this->_crush = crush;
}

void Physictype::setAcceleration(const glm::vec3 acceleration) {
	this->_acceleration = acceleration;
}

void Physictype::setVelocity(const glm::vec3 velocity) {
	this->_velocity = velocity;
}
float Physictype::getMass() const {
	return this->_mass;
}

float Physictype::getCrushIndex() const {
	return this->_crush_index;
}

float Physictype::getRadius() const {
	return this->_radius;
}

bool Physictype::getCrush() const {
	return this->_crush;
}


glm::vec3 Physictype::getAcceleration() const {
	return this->_acceleration;
}

glm::vec3 Physictype::getVelocity() const {
	return this->_velocity;
}


void Gravity::get_in_gravity(PhysictypePtr new_one)
{
	GravityCollection.push_back(new_one);
}

void Gravity::get_in_gravity(std::vector<PhysictypePtr> new_one)
{
	GravityCollection.insert(GravityCollection.end(),new_one.begin(),new_one.end());
}

void Gravity::set_constance(float constance) {
	GRAVITY_CONST = constance;
}
void Gravity::set_step_time(float step_time) {
	STEP_TIME = step_time;
}
float Gravity::get_constance() {
	return GRAVITY_CONST;
}
float Gravity::get_step_time() {
	return STEP_TIME;
}
void Gravity::update_acc() {
	for (int i = 0; i < GravityCollection.size(); i++) {
		// secure that objects have mass
		if ((*GravityCollection[i]).getMass() != 0) {
			glm::vec3 acc = glm::vec3(0);
			float acc_mod = 0;
			glm::vec3 position1 = glm::vec3(0);
			glm::vec3 position2 = glm::vec3(0);
			float distance;
			for (int j = 0; j < GravityCollection.size(); j++) {
				if (i != j) {
					position1 = (*GravityCollection[i]).modelptr->getPosition();
					position2 = (*GravityCollection[j]).modelptr->getPosition();
					distance = sqrt(pow(position1[0] - position2[0], 2) + pow(position1[1] - position2[1], 2) + pow(position1[2] - position2[2], 2));
					acc_mod = (*GravityCollection[j]).getMass() * GRAVITY_CONST / pow(distance, 2);
					acc += acc_mod * (position2 - position1) / distance;
				}
			}
			(*GravityCollection[i]).setAcceleration(acc);
		}
	}

}

void Gravity::update_velocity() {
	glm::vec3 velocity_temp = glm::vec3(0);
	glm::vec3 acceleration_temp = glm::vec3(0);
	for (int i = 0; i < GravityCollection.size(); i++) {
		velocity_temp = (*GravityCollection[i]).getVelocity();
		acceleration_temp = (*GravityCollection[i]).getAcceleration();
		(*GravityCollection[i]).setVelocity(velocity_temp + acceleration_temp * STEP_TIME);
	}
}

void Gravity::update_position() {
	glm::vec3 velocity_temp = glm::vec3(0);
	glm::vec3 position_temp = glm::vec3(0);
	for (int i = 0; i < GravityCollection.size(); i++) {
		position_temp = (*GravityCollection[i]).modelptr->getPosition();
		velocity_temp = (*GravityCollection[i]).getVelocity();
		(*GravityCollection[i]).modelptr->setPosition(position_temp + velocity_temp * STEP_TIME);
	}
}

void CrushCheck::get_in_crushcheck(PhysictypePtr new_one)
{
	CrushCheckCollection.push_back(new_one);
}

void CrushCheck::get_in_crushcheck(std::vector<PhysictypePtr> new_one)
{
	CrushCheckCollection.insert(CrushCheckCollection.end(), new_one.begin(), new_one.end());
}

void momentum(std::shared_ptr<Physictype> first, std::shared_ptr<Physictype> second, glm::vec3 pos1, glm::vec3 pos2, glm::vec3 v1, glm::vec3 v2) {

}

void CrushCheck::update_crush() {
	PhysictypePtr first, second;
	glm::vec3 pos1, pos2,dif;
	glm::vec3 v1, v2,v_vert1,v_vert2,v_proj1,v_proj2;
	float distance,theta,index1,index2;
	for (int i = 0; i < CrushCheckCollection.size(); i++) {
		for (int j = 0; j < CrushCheckCollection.size(); j++) {
			if (i != j) {
				first = CrushCheckCollection[i];
				second = CrushCheckCollection[j];
				pos1 = first.get()->modelptr->getPosition();
				pos2 = second.get()->modelptr->getPosition();
				dif = pos2 - pos1;
				distance = glm::distance(pos1, pos2);
				first->setCrush(false);
				if (distance < first->getRadius() + second->getRadius()) {
					first->setCrush(true);
					v1 = first->getVelocity();
					v2 = second->getVelocity();
					pos1 -= v1 * STEP_TIME;
					pos2 -= v2 * STEP_TIME;
					dif = pos2 - pos1;
					first.get()->modelptr->setPosition(pos1);
					second.get()->modelptr->setPosition(pos2);
					index1 = first->getCrushIndex();
					index2 = second->getCrushIndex();
					//速度的动量计算
					dif = glm::normalize(dif);
					v_proj1 = glm::dot(v1, dif) * dif;
					v_vert1 = v1 - v_proj1;
					v_proj1 = v_proj1 * (-index1);
					first->setVelocity(v_vert1+v_proj1);
					v_proj2 = glm::dot(v2, -dif) * -dif;
					v_vert2 = v2 - v_proj2;
					v_proj2 = v_proj2 * (-index2);
					second->setVelocity(v_vert2+v_proj2);
				}
			}
		}
	}
}


