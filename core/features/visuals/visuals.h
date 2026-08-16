#pragma once

class Visuals {
public:
	static void Overlay(std::vector<Cache::Entities> entities);
private:
	static void Box(BoundingBox bbox);


	static inline BoundingBox bbox;
};