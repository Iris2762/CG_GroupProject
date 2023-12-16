#include "helper.h"
#include "world.h"
#include "physics.h"
#include "model/ball.h"
#include "model/cube.h"
#include "model/fairy.h"
#include "camera.h"
#include "key.h"
#include <memory>
#include <windows.h>
#include<iostream>
#include<vector>
using namespace std;

#define STEP_TIME 0.1
#define VIEW_RADIUS 1000

int main()
{	
	typedef  std::shared_ptr<Model> ModelPtr;
	typedef  std::shared_ptr<Physictype> PhysictypePtr;
	GLFWwindow* window = createBasicWindow("Playground");
	


	auto camera = std::	shared_ptr<Camera>(new Camera);
	
//初始化模型类
	auto ball1 = ModelPtr(new Ball("../texture/big.jpg", 10));//10->3
	auto ball2 = ModelPtr(new Ball("../texture/small1.jpg", 1));
	auto ball3 = ModelPtr(new Ball("../texture/small2.jpg", 1));
//初始化物理类
	//将模型绑定到对应的物理类上
	auto ball1_phy= PhysictypePtr(new Physictype(ball1));
	ball1_phy->setRadius(3.0);
	ball1_phy->setMass(15.);
	auto ball2_phy = PhysictypePtr(new Physictype(ball2));
	auto ball3_phy = PhysictypePtr(new Physictype(ball3));
//物理系统
	auto crushcheck = std::shared_ptr<CrushCheck>(new CrushCheck());
	auto gravity = std::shared_ptr<Gravity>(new Gravity());
//设置初始位置
	ball1->setPosition(glm::vec3(0, 0, 0));
	ball2->setPosition(glm::vec3(15, 0, 0));
	ball3->setPosition(glm::vec3(-13, 7, 0));
//设置初始速度
	ball1_phy->setVelocity(glm::vec3(5, 0, 0));
	ball1_phy->setVelocity(glm::vec3(2, 2, 0));
//控制受到重力作用和加入碰撞检测的对象
	gravity.get()->get_in_gravity(std::vector<PhysictypePtr>({ball1_phy,ball2_phy,ball3_phy }));
	crushcheck.get()->get_in_crushcheck(std::vector<PhysictypePtr>({ ball1_phy,ball2_phy,ball3_phy }));


	//天空盒
	//vector<string> texmap;
	//// 添加六个相同的字符串
	//for (int i = 0; i < 6; ++i) {
	//	texmap.push_back("../texture/big.jpg");
	//}
	auto skybox =ModelPtr(new Cube("../texture/bg/bg2.jpg", 1));//10->3
	//skybox->setPosition(glm::vec3(0, 0, 0));
	//加入渲染类
	World world;
	//cube_center,cube_back,cube_front,cube_up,cube_down,cube_left,cube_right,
	world.addModel(std::vector<std::shared_ptr<Model>>({ball1,ball2,ball3,skybox }));
	world.setCamera(camera);
	glEnable(GL_DEPTH_TEST);
//初始化鼠标位置
	double x_begin, y_begin;
	glfwGetCursorPos(window, &x_begin, &y_begin);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//初始化相机位置
	camera->setPosition(glm::vec3(15 , 15, 15.0f));
	camera->aimAt(glm::vec3(0, 0, 0));
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 0.737f, 0.737f, 1.0f);
		//渲染天空盒
		//skybox->render(camera->getView(), camera->getProj());

		
		processInputs( window,camera, &x_begin, &y_begin,STEP_TIME, VIEW_RADIUS);
		////测试物体旋转效果
		//float t = glfwGetTime();
		//glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f) * t, glm::vec3(0.0f, 1.0f, 0.0f));
		//skybox->setRotation(model);

	
		gravity.get()->update_acc();
		gravity.get()->update_position();
		gravity.get()->update_velocity();
		crushcheck->update_crush();
		world.render();
		



		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(5);
	}
	return 0;
}