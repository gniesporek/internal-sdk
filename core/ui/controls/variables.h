#pragma once

class Variables {

public:
	class Assistance {
	public:
		static inline bool Enable = false;
		static inline bool RenderTarget = false;
		static inline bool SilentAim = false;
		static inline bool AutoShoot = false;
	};

	class Visuals {
	public:
		static inline bool Enable = false;
		static inline bool BoundingBox = false;
		static inline bool Name = false;
		static inline bool Health = false;
		static inline bool WeaponText = false;
		static inline bool Skeleton = false;
	};
};
