#ifndef __CORE_VIEWPORT_H_
#define __CORE_VIEWPORT_H_

namespace CORE
{
#define MODE_ORTHOGRAPHIC 0;
#define MODE_PERSPECTIVE 1;

	class ViewPort
	{
	public:
		ViewPort();
		ViewPort(VERTEX &position, float width, float height, float focalLength = 0);
		ViewPort(VERTEX &position, VECTOR &direction, float width, float height, float focalLength = 0);
		~ViewPort();
		
		void translate(float x, float y, float z);
		void translate(VECTOR &v);
		void rotate(float x, float y, float z);
		void rotate(VECTOR &v);
		void setAt(float x, float y, float z);

		VALUE getX(float x);
		VALUE getY(float y);
		VERTEX getPosition(float x, float y);
		RAY getRay(float x, float y);
		void getComponentPos(float &x, float &y, VERTEX &pos);

	private:
		void generatePort();
		void setFocalLength(float x);
		
		VERTEX p1, p2, p3, p4;
		VERTEX focalPoint;
		VECTOR px, py, normal;
		VECTOR translation, rotation;
		VERTEX frame[4];
		int mode;
	};
}

#endif