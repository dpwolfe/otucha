#pragma once

namespace rffalcon {

	union vec2
	{
		float data[2];
		struct
		{
			float x;
			float y;
		};
		bool operator==(const vec2 &rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
		bool operator!=(const vec2 &rhs) const
		{
			return *this != rhs;
		}
	};

	union vec3
	{
		float data[3];
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float r;
			float g;
			float b;
		};
		struct
		{
			float red;
			float green;
			float blue;
		};
		bool operator==(const vec3 &rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}
		bool operator!=(const vec3 &rhs) const
		{
			return *this != rhs;
		}
	};

	union vec4
	{
		float data[4];
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct
		{
			float x_;
			float y_;
			float width;
			float height;
		};
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
		struct
		{
			float red;
			float green;
			float blue;
			float alpha;
		};
		bool operator==(const vec4 &rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}
		bool operator!=(const vec4 &rhs) const
		{
			return *this != rhs;
		}
	};

	union ivec2
	{
		int data[2];
		struct
		{
			int x;
			int y;
		};
		struct
		{
			int r;
			int g;
		};
		struct
		{
			int red;
			int green;
		};
		bool operator==(const ivec2 &rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
		bool operator!=(const ivec2 &rhs) const
		{
			return *this != rhs;
		}
	};

	union ivec3
	{
		int data[3];
		struct
		{
			int x;
			int y;
			int z;
		};
		struct
		{
			int x_;
			int yNext;
			int width;
		};
		struct
		{
			int r;
			int g;
			int b;
		};
		struct
		{
			int red;
			int green;
			int blue;
		};
		bool operator==(const ivec3 &rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}
		bool operator!=(const ivec3 &rhs) const
		{
			return *this != rhs;
		}
	};

	union ivec4
	{
		int data[4];
		struct
		{
			int x;
			int y;
			int z;
			int w;
		};
		struct
		{
			int x_;
			int y_;
			int width;
			int height;
		};
		struct
		{
			int r;
			int g;
			int b;
			int a;
		};
		struct
		{
			int red;
			int green;
			int blue;
			int alpha;
		};
		struct
		{
			float vstart;
			float vcount;
			float istart;
			float icount;
		};
		bool operator==(const ivec4 &rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}
		bool operator!=(const ivec4 &rhs) const
		{
			return *this != rhs;
		}
	};

}