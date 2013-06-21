#pragma once

class ShapeConsumer : public GLUshapeConsumer
{
public:
	ShapeConsumer(void *data, unsigned num_verts, uintptr_t base_offset)
	{
		GLUvec4 *vert_data = (GLUvec4 *)data;

		this->position = &vert_data[0 * num_verts];
		this->position_offset = (uintptr_t) ((char *)this->position - (char *)data) + base_offset;

		this->normal = &vert_data[1 * num_verts];
		this->normal_offset = (uintptr_t) ((char *)this->normal - (char *)data) + base_offset;

		this->tangent = &vert_data[2 * num_verts];
		this->tangent_offset = (uintptr_t) ((char *)this->tangent - (char *)data) + base_offset;

		this->uv = &vert_data[3 * num_verts];
		this->uv_offset = (uintptr_t) ((char *)this->uv - (char *)data) + base_offset;

		this->vertex_count = num_verts;

		this->elt = (GLushort *) &vert_data[4 * num_verts];
		this->elt_offset = (uintptr_t) ((char *)this->elt - (char *)data) + base_offset;
	}
	
	void begin_primitive(GLenum mode, unsigned count)
	{
		this->mode = mode;
		this->elt_count = count;
	}
	void index_batch(const unsigned* idx, unsigned count)
	{
		for (unsigned i = 0; i < count; i++) 
			this->elt[i] = GLushort(idx[i]);

		this->elt += count;
	}
	
	GLushort* elt;
	uintptr_t elt_offset;
	unsigned elt_count;

	uintptr_t position_offset;
	uintptr_t normal_offset;
	uintptr_t tangent_offset;
	uintptr_t uv_offset;

	GLenum mode;
};