#pragma once

class Variables {

public:
	class Assistance {
	public:
		static inline bool Enable = false;
		static inline int Radius = 180;
		static inline bool RenderTarget = false;
	};

	class Visuals {
	public:
		static inline bool Enable = false;
		static inline bool BoundingBox = false;
		static inline bool Name = false;
		static inline bool Health = false;
	};
};
