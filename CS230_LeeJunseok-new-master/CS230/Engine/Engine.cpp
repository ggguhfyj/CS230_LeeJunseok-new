/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
*/

#include "Engine.h"

Engine::Engine() :
	last_tick(std::chrono::system_clock::now()),
#ifdef _DEBUG
	logger(CS230::Logger::Severity::Debug, true, last_tick)
#else
	logger(CS230::Logger::Severity::Event, false, last_tick)
#endif
{

}


void Engine::Stop() {
	//Stop all services
	logger.LogEvent("Engine Stopped");
}

void Engine::Update() {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration_cast<std::chrono::duration<double>>(now - last_tick).count();


	if (dt >= 1.0 / TargetFPS) {
		logger.LogVerbose("Engine Update");
		last_tick = now;

		frame_count++;
		if (frame_count >= FPSTargetFrames) {
			double actual_time = std::chrono::duration_cast<std::chrono::duration<double>>(now - last_test).count();
			logger.LogDebug("FPS: " + std::to_string(frame_count / actual_time));
			frame_count = 0;
			last_test = now;
		}
		Engine::gamestatemanager.Update(dt);
		Engine::input.Update();
		Engine::window.Update();
	}

}

