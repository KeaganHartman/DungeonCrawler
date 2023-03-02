#pragma once


struct ColorVertex
{
	float xyzw[4];
	float rgba[4];
};

class Object
{
public:
	Object(ColorVertex verts[]);
	/*~Object();
	Object(const Object& other);
	Object operator=(Object& other);*/
private:
	ColorVertex* m_pVerts;

};

