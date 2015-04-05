#pragma once

namespace s1 {

	typedef union
	{
		float data[2];
		struct
		{
			float x;
			float y;
		};
	} vec2;

	typedef union
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
	} vec3;

	typedef union
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
	} vec4;

	typedef union
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
	} ivec2;

	typedef union
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
	} ivec3;

	typedef union
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
	} ivec4;

}