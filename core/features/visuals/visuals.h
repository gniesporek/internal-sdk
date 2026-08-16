#pragma once

class Visuals {
public:
	static void Overlay(std::vector<Cache::Entities> entities);
private:
	static void Box(BoundingBox bbox);
	static void Name(CCSPlayerController* pController, BoundingBox bbox);
	static void HealthBar(C_CSPlayerPawn* pPlayerPawn, BoundingBox bbox);

	static inline BoundingBox bbox;
	static inline std::unordered_map<C_CSPlayerPawn*, float> previousHealth;
};